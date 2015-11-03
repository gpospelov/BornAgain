#include <QDebug>
#include <ColorMapPlot.h>
#include <QPointF>
#include "ObsoleteGraphicsProxyWidget.h"
#include "ColorMapPlot.h"
#include "IntensityDataItem.h"
#include "SimulationRegistry.h"
#include "ObsoleteMaskGraphicsScene.h"
#include "ObsoleteMaskGraphicsView.h"
#include "ObsoleteMaskEditor.h"
#include "MaskToolBar.h"
#include "ObsoleteRectangleView.h"
#include "ObsoleteEllipseView.h"
#include "ObsoletePolygonView.h"
#include "MaskModel.h"
#include "SampleBuilderFactory.h"


const qreal widthOfScene = 2000;
const qreal heightOfScene = 2000;


ObsoleteMaskEditor::ObsoleteMaskEditor(QWidget *parent)
    : QWidget(parent)
    , m_scene(new ObsoleteMaskGraphicsScene(this))
    , m_view(new ObsoleteMaskGraphicsView(m_scene, this))
    , m_proxyWidget(new ObsoleteGraphicsProxyWidget)
    , m_listView(new QListView(this))
    , m_toolBar(new MaskToolBar)
    , m_deleteAction(new QAction("Delete", this))
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMouseTracking(true);
    m_view->setMouseTracking(true);
    m_view->setRenderHint(QPainter::HighQualityAntialiasing);
    m_view->setRenderHint(QPainter::TextAntialiasing);
    m_scene->sceneRect().setWidth(widthOfScene);
    m_scene->setSceneRect(0,0,widthOfScene, heightOfScene);
    m_listView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_listView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_listView->addAction(m_deleteAction);
    m_listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    init_connections();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(m_toolBar,0,0,1,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_view, 1,0);
    mainLayout->addWidget(m_listView, 1,1);
    setLayout(mainLayout);

}

void ObsoleteMaskEditor::init_connections()
{
    connect(m_toolBar, SIGNAL(changeToSelectionMode()), this, SLOT(changeToSelectionMode()));
    connect(m_scene, SIGNAL(itemIsDrawn()), this, SLOT(changeToSelectionMode()));
    connect(m_scene, SIGNAL(itemIsDrawn()), m_toolBar, SLOT(selectSelectionMode()));
    connect(m_toolBar, SIGNAL(panMode(bool)), this, SLOT(panMode(bool)));
    connect(m_toolBar, SIGNAL(rectangleButtonPressed()), this, SLOT(rectangleButtonPressed()));
    connect(m_toolBar, SIGNAL(ellipseButtonPressed()), SLOT(ellipseButtonPressed()));
    connect(m_toolBar, SIGNAL(polygonButtonPressed()), this, SLOT(polygonButtonPressed()));
    connect(m_toolBar, SIGNAL(bringToFrontClicked()), this, SLOT(bringToFrontClicked()));
    connect(m_toolBar, SIGNAL(sendToBackClicked()), this, SLOT(sendToBackClicked()));
    connect(m_toolBar, SIGNAL(includeClicked()), this, SLOT(includeClicked()));
    connect(m_toolBar, SIGNAL(excludeClicked()), this , SLOT(excludeClicked()));
    connect(this, SIGNAL(deleteSelectedItems()), m_scene, SLOT(deleteSelectedItems()));
    connect(m_deleteAction, SIGNAL(triggered(bool)), m_scene, SLOT(deleteSelectedItems()));
    connect(m_view, SIGNAL(deleteSelectedItems()), m_scene, SLOT(deleteSelectedItems()));
}

void ObsoleteMaskEditor::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Delete:
        emit deleteSelectedItems();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    };
}

void ObsoleteMaskEditor::rectangleButtonPressed()
{
    m_scene->setDrawing(ObsoleteMaskGraphicsScene::RECTANGLE);
}

void ObsoleteMaskEditor::ellipseButtonPressed()
{
    m_scene->setDrawing(ObsoleteMaskGraphicsScene::ELLIPSE);
}

void ObsoleteMaskEditor::polygonButtonPressed()
{
    m_scene->setDrawing(ObsoleteMaskGraphicsScene::POLYGON);
}

void ObsoleteMaskEditor::panMode(bool active)
{
    if(active) {
        m_view->setDragMode(QGraphicsView::ScrollHandDrag);
        m_view->setInteractive(false);
    }
    else {
        m_view->setDragMode(QGraphicsView::NoDrag);
        m_view->setInteractive(true);
    }
}

void ObsoleteMaskEditor::deleteSelectedItem()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        m_scene->removeItem(selectedItems[i]);
    }

}

void ObsoleteMaskEditor::bringToFrontClicked()
{
    m_scene->onBringToFront();

}

void ObsoleteMaskEditor::sendToBackClicked()
{
    m_scene->onSendToBack();
}

void ObsoleteMaskEditor::includeClicked()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        if(ObsoleteRectangleView::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<ObsoleteRectangleView* >(selectedItems[i])->setInclude();
        }
        else if(ObsoleteEllipseView::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<ObsoleteEllipseView* >(selectedItems[i])->setInclude();
        }
        else if(ObsoletePolygonView::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<ObsoletePolygonView* >(selectedItems[i])->setInclude();
        }
    }
}

void ObsoleteMaskEditor::excludeClicked()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        if(ObsoleteRectangleView::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<ObsoleteRectangleView * >(selectedItems[i])->setExclude();
        }
        else if(ObsoleteEllipseView::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<ObsoleteEllipseView* >(selectedItems[i])->setExclude();
        }
        else if(ObsoletePolygonView::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<ObsoletePolygonView* >(selectedItems[i])->setExclude();
        }
    }
}

void ObsoleteMaskEditor::changeToSelectionMode()
{
    m_scene->setDrawing(ObsoleteMaskGraphicsScene::NONE);
}

void ObsoleteMaskEditor::changeToDrawingMode()
{
    m_view->setDragMode(QGraphicsView::NoDrag);
    m_view->setInteractive(true);
}

void ObsoleteMaskEditor::setModel(MaskModel *maskModel)
{
    m_listView->setModel(maskModel);
    m_scene->setModel(maskModel);
    m_scene->setSelectionModel(m_listView->selectionModel());

//    SimulationRegistry sim_registry;
//    Simulation *sim = sim_registry.createSimulation("BasicGISAS");
//    SampleBuilderFactory sampleFactory;
//    SampleBuilder_t builder = sampleFactory.createBuilder("CylindersAndPrismsBuilder");
//    sim->setSampleBuilder(builder);

//    sim->runSimulation();
//    qDebug() << sim->getIntensityData() << sim->getIntensityData()->totalSum();

//    IntensityDataItem *dataItem = new IntensityDataItem;
//    dataItem->setOutputData(sim->getIntensityData());

//    ColorMapPlot *colorMapPlot = new ColorMapPlot;
//    colorMapPlot->setItem(dataItem);

//    m_proxyWidget->setWidget(colorMapPlot);

    m_proxyWidget->setPos(m_scene->sceneRect().topLeft());
    m_proxyWidget->resize(m_scene->width(), m_scene->height());
    m_scene->addItem(m_proxyWidget);
}

void ObsoleteMaskEditor::onItemIsDrawn()
{
    emit itemIsDrawn();
}



