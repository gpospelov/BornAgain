#include <QDebug>
#include <ColorMapPlot.h>
#include <QPointF>
#include "GraphicsProxyWidget.h"
#include "ColorMapPlot.h"
#include "IntensityDataItem.h"
#include "SimulationRegistry.h"
#include "MaskGraphicsScene.h"
#include "MaskGraphicsView.h"
#include "MaskEditor.h"
#include "MaskToolBar.h"
#include "RectangleView.h"
#include "EllipseView.h"
#include "PolygonView.h"
#include "MaskModel.h"
#include "SampleBuilderFactory.h"


const qreal widthOfScene = 2000;
const qreal heightOfScene = 2000;


MaskEditor::MaskEditor(QWidget *parent)
    : QWidget(parent)
    , m_scene(new MaskGraphicsScene(this))
    , m_view(new MaskGraphicsView(m_scene, this))
    , m_proxyWidget(new GraphicsProxyWidget)
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

    init_connections();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(m_toolBar,0,0,1,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_view, 1,0);
    mainLayout->addWidget(m_listView, 1,1);
    setLayout(mainLayout);

}

void MaskEditor::init_connections()
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
    connect(m_deleteAction, SIGNAL(changed()), m_scene, SLOT(deleteSelectedItems()));
    connect(m_view, SIGNAL(deleteSelectedItems()), m_scene, SLOT(deleteSelectedItems()));
}

void MaskEditor::keyPressEvent(QKeyEvent *event)
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

void MaskEditor::rectangleButtonPressed()
{
    m_scene->setDrawing(MaskGraphicsScene::RECTANGLE);
}

void MaskEditor::ellipseButtonPressed()
{
    m_scene->setDrawing(MaskGraphicsScene::ELLIPSE);
}

void MaskEditor::polygonButtonPressed()
{
    m_scene->setDrawing(MaskGraphicsScene::POLYGON);
}

void MaskEditor::panMode(bool active)
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

void MaskEditor::deleteSelectedItem()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        m_scene->removeItem(selectedItems[i]);
    }

}

void MaskEditor::bringToFrontClicked()
{
    m_scene->onBringToFront();

}

void MaskEditor::sendToBackClicked()
{
    m_scene->onSendToBack();
}

void MaskEditor::includeClicked()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        if(RectangleView::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<RectangleView* >(selectedItems[i])->setInclude();
        }
        else if(EllipseView::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<EllipseView* >(selectedItems[i])->setInclude();
        }
        else if(PolygonView::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<PolygonView* >(selectedItems[i])->setInclude();
        }
    }
}

void MaskEditor::excludeClicked()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        if(RectangleView::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<RectangleView * >(selectedItems[i])->setExclude();
        }
        else if(EllipseView::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<EllipseView* >(selectedItems[i])->setExclude();
        }
        else if(PolygonView::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<PolygonView* >(selectedItems[i])->setExclude();
        }
    }
}

void MaskEditor::changeToSelectionMode()
{
    m_scene->setDrawing(MaskGraphicsScene::NONE);
}

void MaskEditor::changeToDrawingMode()
{
    m_view->setDragMode(QGraphicsView::NoDrag);
    m_view->setInteractive(true);
}

void MaskEditor::setModel(MaskModel *maskModel)
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

void MaskEditor::onItemIsDrawn()
{
    emit itemIsDrawn();
}



