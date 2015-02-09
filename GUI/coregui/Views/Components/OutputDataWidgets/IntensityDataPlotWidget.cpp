// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/OutputDataWidgets/IntensityDataPlotWidget.cpp
//! @brief     Implements class IntensityDataPlotWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IntensityDataPlotWidget.h"
#include "ColorMapPlot.h"
#include "NHistogramPlot.h"
#include "NIntensityDataItem.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>


IntensityDataPlotWidget::IntensityDataPlotWidget(QWidget *parent)
    : QWidget(parent)
    , m_splitter(new QSplitter(this))
    , m_splitterTop(new QSplitter(this))
    , m_splitterBottom(new QSplitter(this))
    , m_centralPlot(new ColorMapPlot(this))
    , m_verticalPlot(new NHistogramPlot(this))
    , m_horizontalPlot(new NHistogramPlot(this))
    , m_statusLabel(new QLabel(this))
    , m_leftHistogramArea(150)
    , m_bottomHistogramArea(150)
    , m_item(0)
{
    setObjectName(QStringLiteral("IntensityDataPlotWidget"));

    m_splitterTop->addWidget(m_verticalPlot);
    m_splitterTop->addWidget(m_centralPlot);
    m_splitterTop->setStyleSheet("background-color:white;");

    m_splitterBottom->addWidget(new QWidget());
    m_splitterBottom->addWidget(m_horizontalPlot);
    m_splitterBottom->setStyleSheet("background-color:white;");
    //m_splitterBottom->setHandleWidth(0);

    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_splitterTop);
    m_splitter->addWidget(m_splitterBottom);
    m_splitter->setStyleSheet("background-color:white;");

    //m_statusLabel->setFrameStyle(QFrame::Panel );
    m_statusLabel->setAlignment(Qt::AlignVCenter| Qt::AlignLeft);
    //m_statusLabel->setMaximumHeight(35);
    m_statusLabel->setStyleSheet("background-color:white;");
    m_statusLabel->setMargin(3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_splitter);
    vlayout->addWidget(m_statusLabel);
    this->setLayout(vlayout);
    //setCentralWidget(widget);

    connect(m_splitterTop, SIGNAL(splitterMoved(int,int)), this, SLOT(onSplitterMoved(int,int)));
    connect(m_splitterBottom, SIGNAL(splitterMoved(int,int)), this, SLOT(onSplitterMoved(int,int)));

//    initSplitterSizes(m_leftHistogramArea, m_bottomHistogramArea);

    initLeftRightAreaSize(m_leftHistogramArea, 600-m_leftHistogramArea);
    initBottomTopAreaSize(m_bottomHistogramArea, 500-m_bottomHistogramArea);
}

void IntensityDataPlotWidget::setItem(NIntensityDataItem *item)
{
    qDebug() << "IntensityDataPlotWidget::setItem(NIntensityDataItem *item)";

    m_centralPlot->setItem(item);

    if (m_item == item) return;

    if (m_item) {
        disconnect(m_item, SIGNAL(propertyChanged(QString)),
                this, SLOT(onPropertyChanged(QString)));
    }

    m_item = item;

    if (!m_item) return;

    connect(m_item, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));
}

// provide syncronious move of top and bottom splitters
void IntensityDataPlotWidget::onSplitterMoved(int pos, int index)
{
    Q_UNUSED(index);
    QSplitter *splitter = qobject_cast<QSplitter *>(sender());
    QList<int> sizes = QList<int>() << pos << (this->size().width()-pos);
    if(splitter == m_splitterTop) {
        m_splitterBottom->setSizes(sizes);
    } else if(splitter == m_splitterBottom) {
        m_splitterTop->setSizes(sizes);
    }
}

void IntensityDataPlotWidget::resetView()
{
    m_centralPlot->resetView();
}

void IntensityDataPlotWidget::onPropertyChanged(const QString &property_name)
{
    qDebug() << "IntensityDataPlotWidget::onPropertyChanged(const QString &property_name)" << property_name;
}

//void IntensityDataPlotWidget::initSplitterSizes(int horizontal_size, int vertical_size)
//{
//    int total_width = this->size().width();
//    QList<int> horisontal_sizes = QList<int>() << horizontal_size << (total_width-horizontal_size);
//    m_splitterTop->setSizes(horisontal_sizes);
//    m_splitterBottom->setSizes(horisontal_sizes);

//    qDebug() << horisontal_sizes << total_width;

//    int total_height = this->size().height() - m_statusLabel->size().height();
//    QList<int> vertical_sizes = QList<int>() << (total_height - vertical_size) << vertical_size;
//    m_splitter->setSizes(vertical_sizes);
//    qDebug() << vertical_sizes;
//}

// sets sizes of top and bottom splitters to have correct sizes of vertical histogram (on the left) and color map
void IntensityDataPlotWidget::initLeftRightAreaSize(int left_size, int right_size)
{
    QList<int> sizes = QList<int>() << left_size << right_size;
    m_splitterTop->setSizes(sizes);
    m_splitterBottom->setSizes(sizes);
}

// set size of main splitter to have correct sizes of horizontal histogram (at the bottom) and color map
void IntensityDataPlotWidget::initBottomTopAreaSize(int bottom_size, int top_size)
{
    QList<int> sizes = QList<int>() << top_size << bottom_size;
    m_splitter->setSizes(sizes);
}
