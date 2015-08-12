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





// See other FIXME in GraphicsScene.h GraphicsScene.cpp, GraphicsView.cpp, RectangleView.h, RectangleView.cpp

// All
// Cleanup the code. Remove old versions of Ellipse, Polygon, Rectangle [FIXED]

// *.h
// In all headers remove all includes placed before #ifndef, includes should be inside #ifndef [FIXED]

// *.h
// In all headers remove unnecessary includes, use class forward declaration, where possible [FIXED]

// Renaming
// Rename GraphicsScene to MaskGraphicsScene [FIXED]
// Rename GraphicsView to MaskGraphicsView [FIXED]

// MaskToolBar (MaskEditor)
// 1) Create MaskToolBar widget which will contain vertically aligned QToolButtons of 25x25 size
//    SELECT
//    PAN
//    ------ separator
//    RECTANGLE
//    ELLIPSE
//    POLYGON
//    ------
//    BLUE (include button) <-- these two buttons should be in the group, so only one is active
//    RED  (exclude button) <--
//    ------
//    SEND_TO_ONE_LEVEL_DOWN
//    SEND_TO_ON_LEVEL_UP
//    INVERT_MASK <-- will change the color of item to the opposite
//

// 2) Think of icons for whose buttons [FIXED]
// 3) Provide buttons will tooltip [FIXED]
// 4) MaskEditor will own MaskmToolBar widget,
//    create MaskEditor::init_connections()
//    which will connect all signals in one place (i.e. not in constructor) [FIXED]


// Move up/down functionality [FIXED]
// Use SessionModel::moveParameterizedItem(item_to_move, new_parent, row);
//
// For example, you have rectangleItem which belongs to model (to the root of the model), and it is located in the row #5
// You want to move it in the raw number 4, you write
// model->moveParameterizedItem(rectangleItem, 0, 4);
//
// This will trigger onRowInserted
// You will have to run through all views and update they z-coordinate, i.e. will recalculate them from row number of corresponding items


// Drawing of rectangle
// When one tries to draw a rectangle and draws it too small, the rectangle is not drawn. That's ok.
// But if it was the case, the scene should not switch automatically in selection mode, it should stays in rectangle mode.
// Only if creation of view was successfull -> switch to selection mode. [FIXED]

// RectangleView, EllipseView
// 1) Rectangle should have a tiny frame around, which is a bit darker, than filling color.
//    use QColor::darker() for that [FIXED]
// 2) Green rectangular corners are ugly and too big. Use smaller rectangle as in Libreoffice/Impress.
//    The color of corner rectangle should be as main rectangle's frame [FIXED]
// 3) Same of EllipseView [FIXED]

// Selection of Rectangle or Ellipse
// 1) First click on the rectangle should select it [FIXED]
// 2) second click on selected rectangle should switch it to the rotation mode
//    Corner rectangle should be replaced with rotation symbols, as in inkscape [FIXED]
// 3) Every next click just switch between selected/rotate modes [FIXED]
// 4) Same for EllipseView [FIXED]

// Bug (deleting rectangle) [FIXED]
// Sometimes, but now always, deleting of rectangle gives an exception throw
// "ParameterizedItem::getRegisteredProperty() -> Error. Unknown property Height model=Rectangle"

// GraphicsView - zoom in/out, pan
// 1) No scroll bars appears when zoom in [FIXED]
// 2) Pan seems to be not making a pan over the whole area [FIXED]
// 3) Make pan automatic then user holds on "spacebar" key. [FIXED]
// 4) zoom out to far should not be possible, i.e. maximum size of scene should be defined [FIXED]




const qreal widthOfScene = 2000;
const qreal heightOfScene = 2000;


MaskEditor::MaskEditor(QWidget *parent)
    : QWidget(parent)
    , m_scene(new MaskGraphicsScene)
    , m_view(new MaskGraphicsView)
    , m_proxyWidget(new GraphicsProxyWidget)
    , m_listView(new QListView)
    , m_toolBar(new MaskToolBar)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMouseTracking(true);
    m_view->setMouseTracking(true);
    m_view->setRenderHint(QPainter::HighQualityAntialiasing);
    m_view->setRenderHint(QPainter::TextAntialiasing);
    m_view->setScene(m_scene);
    m_scene->sceneRect().setWidth(widthOfScene);
    m_scene->setSceneRect(0,0,widthOfScene, heightOfScene);
    m_listView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    init_connections();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(0,0,0,0);
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
    connect(m_view, SIGNAL(panMode(bool)), this, SLOT(panMode(bool)));
    connect(m_toolBar, SIGNAL(rectangleButtonPressed()), this, SLOT(rectangleButtonPressed()));
    connect(m_toolBar, SIGNAL(ellipseButtonPressed()), SLOT(ellipseButtonPressed()));
    connect(m_toolBar, SIGNAL(polygonButtonPressed()), this, SLOT(polygonButtonPressed()));
    connect(m_toolBar, SIGNAL(bringToFrontClicked()), this, SLOT(bringToFrontClicked()));
    connect(m_toolBar, SIGNAL(sendToBackClicked()), this, SLOT(sendToBackClicked()));
    connect(m_toolBar, SIGNAL(includeClicked()), this, SLOT(includeClicked()));
    connect(m_toolBar, SIGNAL(excludeClicked()), this , SLOT(excludeClicked()));
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



