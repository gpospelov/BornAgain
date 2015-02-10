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
    m_splitterBottom->setHandleWidth(0);

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

//    initLeftRightAreaSize(m_leftHistogramArea, 600-m_leftHistogramArea);
//    initTopBottomAreaSize(500-m_bottomHistogramArea, m_bottomHistogramArea);
    initLeftRightAreaSize(0, 600);
    initTopBottomAreaSize(500, 0);
//    showProjections(false);

    connect(m_splitterTop, SIGNAL(splitterMoved(int,int)), this, SLOT(onSplitterMoved(int,int)));
    connect(m_splitterBottom, SIGNAL(splitterMoved(int,int)), this, SLOT(onSplitterMoved(int,int)));
//    connect(m_centralPlot, SIGNAL(statusStringChanged(QString)), this, SLOT(onStatusStringChanged(QString)));
//    connect(m_centralPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));
    connect(m_centralPlot, SIGNAL(validMousMove()), this, SLOT(onMouseMove()));

}

void IntensityDataPlotWidget::setItem(NIntensityDataItem *item)
{
    qDebug() << "IntensityDataPlotWidget::setItem(NIntensityDataItem *item)";

    m_centralPlot->setItem(item);
    m_horizontalPlot->setItem(item);

    if (m_item == item) return;

    if (m_item) {
        disconnect(m_item, SIGNAL(propertyChanged(QString)),
                this, SLOT(onPropertyChanged(QString)));
    }

    m_item = item;

    if (!m_item) return;

    updateItem(m_item);

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

void IntensityDataPlotWidget::onMouseMove()
{
    qDebug() << "IntensityDataPlotWidget::onMouseMove(QMouseEvent *event)";
    m_statusLabel->setText(m_centralPlot->getStatusString());

    if(isBottomAreaVisible()) {
        QVector<double> x, y;
        m_centralPlot->getHorizontalSlice(x, y);
        m_horizontalPlot->plotData(x,y);
    }

}

void IntensityDataPlotWidget::onPropertyChanged(const QString &property_name)
{
    qDebug() << "IntensityDataPlotWidget::onPropertyChanged(const QString &property_name)" << property_name;
    if(property_name == NIntensityDataItem::P_PROJECTIONS_FLAG) {
        showProjections(m_item->getRegisteredProperty(NIntensityDataItem::P_PROJECTIONS_FLAG).toBool());
    }
}

//void IntensityDataPlotWidget::onStatusStringChanged(const QString &status)
//{
//    m_statusLabel->setText(status);
//}

void IntensityDataPlotWidget::showProjections(bool flag)
{
    qDebug() << "IntensityDataPlotWidget::showProjections(bool flag)" << flag;
    // restoring old splitter positions

    qDebug() << "m_leftHistogramArea:" << m_leftHistogramArea << "m_splitterTop->width():" << m_splitterTop->size() << m_splitterTop->sizes();
    qDebug() << "m_bottomHistogramArea:" << m_bottomHistogramArea << "m_splitter->height():" << m_splitter->size() << m_splitter->sizes();
    qDebug() << "XXX" << size();
    if(flag) {
        int width = m_splitterTop->width() - m_leftHistogramArea;
        if(width < 0) width = m_leftHistogramArea*3;
        initLeftRightAreaSize(m_leftHistogramArea, width);

        int height = m_splitter->height() - m_bottomHistogramArea;
        if(height < 0) height = m_bottomHistogramArea*3;
        initTopBottomAreaSize(height, m_bottomHistogramArea);

    } else {
        // saving splitter positions, and then
        // hiding projections by setting corresponding splitter size to zero
        QList<int> horizontal_sizes = m_splitterTop->sizes();
        if(horizontal_sizes[0] > 0) m_leftHistogramArea = horizontal_sizes[0];
        initLeftRightAreaSize(0, horizontal_sizes[0]+horizontal_sizes[1]);
        QList<int> vertical_sizes = m_splitter->sizes();
        if(vertical_sizes[1] > 0) m_bottomHistogramArea = vertical_sizes[1];
        initTopBottomAreaSize(vertical_sizes[0]+vertical_sizes[1], 0);
    }
    qDebug() << "after " << m_leftHistogramArea << m_bottomHistogramArea;

}

void IntensityDataPlotWidget::updateItem(NIntensityDataItem *item)
{
    showProjections(item->getRegisteredProperty(NIntensityDataItem::P_PROJECTIONS_FLAG).toBool());
}

// sets sizes of top and bottom splitters to have correct sizes of vertical histogram (on the left) and color map
void IntensityDataPlotWidget::initLeftRightAreaSize(int left_size, int right_size)
{
    QList<int> sizes = QList<int>() << left_size << right_size;
    m_splitterTop->setSizes(sizes);
    m_splitterBottom->setSizes(sizes);
}

// set size of main splitter to have correct sizes of horizontal histogram (at the bottom) and color map
void IntensityDataPlotWidget::initTopBottomAreaSize(int top_size, int bottom_size)
{
    QList<int> sizes = QList<int>() << top_size << bottom_size;
    m_splitter->setSizes(sizes);
}

bool IntensityDataPlotWidget::isBottomAreaVisible()
{
    QList<int> sizes = m_splitter->sizes();
    return sizes[1] != 0;
}
