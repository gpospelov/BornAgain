// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ObsoleteIntensityDataPlotWidget.cpp
//! @brief     Implements class ObsoleteIntensityDataPlotWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ObsoleteIntensityDataPlotWidget.h"
#include "ColorMapPlot.h"
#include "HorizontalSlicePlot.h"
#include "IntensityDataItem.h"
#include "SavePlotAssistant.h"
#include "VerticalSlicePlot.h"
#include "qcustomplot.h"
#include <QDebug>
#include <QLabel>
#include <QSplitter>
#include <QVBoxLayout>


ObsoleteIntensityDataPlotWidget::ObsoleteIntensityDataPlotWidget(QWidget *parent)
    : QWidget(parent)
    , m_splitter(new QSplitter(this))
    , m_splitterTop(new QSplitter(this))
    , m_splitterBottom(new QSplitter(this))
    , m_propertyPanelAction(0)
    , m_projectionsAction(0)
    , m_resetAction(0)
    , m_saveAction(0)
    , m_centralPlot(new ColorMapPlot(this))
    , m_verticalPlot(new VerticalSlicePlot(this))
    , m_horizontalPlot(new HorizontalSlicePlot(this))
    , m_statusLabel(new QLabel(this))
    , m_leftHistogramArea(150)
    , m_bottomHistogramArea(150)
    , m_item(0)
//    , m_mapper(0)
{
    setObjectName(QStringLiteral("IntensityDataPlotWidget"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_centralPlot->setTrackMoveEventsFlag(true);

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

    m_statusLabel->setAlignment(Qt::AlignVCenter| Qt::AlignLeft);
    m_statusLabel->setStyleSheet("background-color:white;");
    m_statusLabel->setMargin(3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_splitter);
    vlayout->addWidget(m_statusLabel);
    this->setLayout(vlayout);

    initLeftRightAreaSize(0, 600);
    initTopBottomAreaSize(500, 0);

    connect(m_splitterTop, SIGNAL(splitterMoved(int,int)), this, SLOT(onSplitterMoved(int,int)));
    connect(m_splitterBottom, SIGNAL(splitterMoved(int,int)), this, SLOT(onSplitterMoved(int,int)));
    connect(m_centralPlot, SIGNAL(validMousMove()), this, SLOT(onMouseMove()));
    connect(m_centralPlot->getCustomPlot(), SIGNAL(mousePress(QMouseEvent*)), this, SLOT(onMousePress(QMouseEvent*)), Qt::UniqueConnection);

    setupContextMenuActions();
}

ObsoleteIntensityDataPlotWidget::~ObsoleteIntensityDataPlotWidget()
{

}

//! initializes the class with NIntensityDataItem
void ObsoleteIntensityDataPlotWidget::setItem(IntensityDataItem *item)
{
    m_centralPlot->setItem(item);
    m_horizontalPlot->setItem(item);
    m_verticalPlot->setItem(item);

    if (m_item == item) {
        return;

    } else {
        if(m_item)
            m_item->mapper()->unsubscribe(this);

        m_item = item;
        if (!m_item) return;

        updateItem(m_item);

        m_item->mapper()->setOnPropertyChange(
                    [this](const QString &name)
        {
            if(name == IntensityDataItem::P_PROJECTIONS_FLAG) {
                showProjections(m_item->getItemValue(IntensityDataItem::P_PROJECTIONS_FLAG).toBool());
            }
        }, this);

    }

}

//! provide syncronious move of top and bottom splitters
void ObsoleteIntensityDataPlotWidget::onSplitterMoved(int pos, int index)
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

void ObsoleteIntensityDataPlotWidget::resetView()
{
    m_item->resetView();
}

//! reset views to original axes min and max
//void IntensityDataPlotWidget::resetView()
//{
//    m_centralPlot->resetView();
//}

//! updates status string, line cross and projections on mouse move
void ObsoleteIntensityDataPlotWidget::onMouseMove()
{
    m_statusLabel->setText(m_centralPlot->getStatusString());

    bool bottom_is_visible = isBottomAreaVisible();
    if(bottom_is_visible) {
        QVector<double> x, y;
        m_centralPlot->getHorizontalSlice(x, y);
        m_horizontalPlot->plotData(x,y);
    }

    bool left_is_visible = isLeftAreaVisible();
    if(left_is_visible) {
        QVector<double> x, y;
        m_centralPlot->getVerticalSlice(x, y);
        m_verticalPlot->plotData(x,y);
    }

    if(bottom_is_visible || left_is_visible)
        m_centralPlot->drawLinesOverTheMap();
}

//! provides context menu on right mouse button
void ObsoleteIntensityDataPlotWidget::onMousePress(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        //showContextMenu(event->pos());
        showContextMenu(event->globalPos());
    }
}

//! saves plot into proposed directory
void ObsoleteIntensityDataPlotWidget::savePlot(const QString &dirname)
{
    Q_ASSERT(m_item);

    bool projections_flag = m_item->getItemValue(IntensityDataItem::P_PROJECTIONS_FLAG).toBool();
    if(projections_flag)
        m_centralPlot->showLinesOverTheMap(false);

    SavePlotAssistant saveAssistant;
    saveAssistant.savePlot(dirname, m_centralPlot->getCustomPlot(), m_item);

    m_centralPlot->showLinesOverTheMap(projections_flag);
}

//! switches projections On and Off
void ObsoleteIntensityDataPlotWidget::showProjections(bool flag)
{
    if(flag) {
        // restoring old splitter positions
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
}

void ObsoleteIntensityDataPlotWidget::onPropertyPanelAction(bool flag)
{
    Q_ASSERT(m_item);
    m_item->setItemValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG, flag);
}

void ObsoleteIntensityDataPlotWidget::onProjectionsAction(bool flag)
{
    Q_ASSERT(m_item);
    m_item->setItemValue(IntensityDataItem::P_PROJECTIONS_FLAG, flag);
}


void ObsoleteIntensityDataPlotWidget::showContextMenu(const QPoint &point)
{
    Q_ASSERT(m_item);
    QMenu menu;

    m_propertyPanelAction->setChecked(m_item->getItemValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG).toBool());
    m_projectionsAction->setChecked(m_item->getItemValue(IntensityDataItem::P_PROJECTIONS_FLAG).toBool());

    menu.addAction(m_propertyPanelAction);
    menu.addAction(m_projectionsAction);
    menu.addAction(m_resetAction);
    menu.addAction(m_saveAction);

    //menu.exec(mapToGlobal(point));
    menu.exec(point);
}

void ObsoleteIntensityDataPlotWidget::setupContextMenuActions()
{
    m_propertyPanelAction = new QAction("Plot Properties", this);
    m_propertyPanelAction->setCheckable(true);
    connect(m_propertyPanelAction, SIGNAL(triggered(bool)), this, SLOT(onPropertyPanelAction(bool)));

    m_projectionsAction = new QAction("&Projections", this);
    m_projectionsAction->setCheckable(true);
    connect(m_projectionsAction, SIGNAL(triggered(bool)), this, SLOT(onProjectionsAction(bool)));

    m_resetAction = new QAction("Reset View", this);
    connect(m_resetAction, SIGNAL(triggered()), this, SLOT(resetView()));

    m_saveAction = new QAction("Save as", this);
    connect(m_saveAction, SIGNAL(triggered()), this, SIGNAL(savePlotRequest()));

}

void ObsoleteIntensityDataPlotWidget::updateItem(IntensityDataItem *item)
{
    showProjections(item->getItemValue(IntensityDataItem::P_PROJECTIONS_FLAG).toBool());
}

//! sets sizes of top and bottom splitters to have correct sizes of vertical histogram (on the left) and color map
void ObsoleteIntensityDataPlotWidget::initLeftRightAreaSize(int left_size, int right_size)
{
    QList<int> sizes = QList<int>() << left_size << right_size;
    m_splitterTop->setSizes(sizes);
    m_splitterBottom->setSizes(sizes);
}

//! set size of main splitter to have correct sizes of horizontal histogram (at the bottom) and color map
void ObsoleteIntensityDataPlotWidget::initTopBottomAreaSize(int top_size, int bottom_size)
{
    QList<int> sizes = QList<int>() << top_size << bottom_size;
    m_splitter->setSizes(sizes);
}

//! returns true if bottom splitter is not collapsed
bool ObsoleteIntensityDataPlotWidget::isBottomAreaVisible()
{
    QList<int> sizes = m_splitter->sizes();
    return sizes[1] != 0;
}

//! returns true if left splitter is not collapsed
bool ObsoleteIntensityDataPlotWidget::isLeftAreaVisible()
{
    QList<int> sizes = m_splitterTop->sizes();
    return sizes[0] != 0;
}

