#include <QDebug>
#include <ColorMapPlot.h>
#include "GraphicsProxyWidget.h"
#include "ColorMapPlot.h"
#include "IntensityDataItem.h"
#include "SimulationRegistry.h"
#include "MaskGraphicsScene.h"
#include "MaskGraphicsView.h"
#include "MaskEditor.h"
#include "RectangleView.h"
#include "EllipseView.h"
#include "PolygonView.h"
#include "MaskModel.h"
#include "SampleBuilderFactory.h"
#include "AwesomePropertyEditor.h"
#include "RectangleItem.h"



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

// 2) Think of icons for whose buttons
// 3) Provide buttons will tooltip
// 4) MaskEditor will own MaskToolBar widget, create MaskEditor::init_connections() which will connect all signals in one place (i.e. not in constructor)


// Move up/down functionality
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
//    use QColor::darker() for that
// 2) Green rectangular corners are ugly and too big. Use smaller rectangle as in Libreoffice/Impress.
//    The color of corner rectangle should be as main rectangle's frame
// 3) Same of EllipseView

// Selection of Rectangle or Ellipse
// 1) First click on the rectangle should select it
// 2) second click on selected rectangle should switch it to the rotation mode
//    Corner rectangle should be replaced with rotation symbols, as in inkscape
// 3) Every next click just switch between selected/rotate modes
// 4) Same for EllipseView

// Bug (deleting rectangle) [FIXED]
// Sometimes, but now always, deleting of rectangle gives an exception throw
// "ParameterizedItem::getRegisteredProperty() -> Error. Unknown property Height model=Rectangle"

// GraphicsView - zoom in/out, pan
// 1) No scroll bars appears when zoom in
// 2) Pan seems to be not making a pan over the whole area
// 3) Make pan automatic then user holds on "spacebar" key.
// 4) zoom out to far should not be possible, i.e. maximum size of scene should be defined










MaskEditor::MaskEditor(QWidget *parent)
    : QWidget(parent)
    , m_scene(new MaskGraphicsScene)
    , m_view(new MaskGraphicsView)
    , m_proxyWidget(new GraphicsProxyWidget)
    , m_buttonLayout(new QVBoxLayout)
{

    setMouseTracking(true);
    m_view->setMouseTracking(true);
    m_view->setRenderHint(QPainter::HighQualityAntialiasing);
    m_view->setRenderHint(QPainter::TextAntialiasing);
//    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setScene(m_scene);
    m_scene->setSceneRect(m_view->viewport()->rect());



    // convert widget into custom QProxywidget and put it in to the scene
    SimulationRegistry sim_registry;
    Simulation *sim = sim_registry.createSimulation("BasicGISAS");
    SampleBuilderFactory sampleFactory;
    SampleBuilder_t builder = sampleFactory.createBuilder("CylindersAndPrismsBuilder");
    sim->setSampleBuilder(builder);

    sim->runSimulation();
    qDebug() << sim->getIntensityData() << sim->getIntensityData()->totalSum();

    IntensityDataItem *dataItem = new IntensityDataItem;
    dataItem->setOutputData(sim->getIntensityData());

    ColorMapPlot *colorMapPlot = new ColorMapPlot;
    colorMapPlot->setItem(dataItem);

    m_proxyWidget->setWidget(new QCustomPlot);
    m_proxyWidget->resize(m_scene->width(), m_scene->height());
    m_scene->addItem(m_proxyWidget);


    // connect buttons
    QPushButton *rectangleButton = new QPushButton("Rectangle");
    rectangleButton->setCheckable(true);
    connect(rectangleButton, SIGNAL(pressed()), this, SLOT(rectangleButtonPressed()));

    QPushButton *ellipseButton = new QPushButton("Ellipse");
    ellipseButton->setCheckable(true);
    connect(ellipseButton, SIGNAL(pressed()), this, SLOT(ellipseButtonPressed()));

    QPushButton *polygonButton = new QPushButton("Polygon");
    polygonButton->setCheckable(true);
    connect(polygonButton, SIGNAL(pressed()), this, SLOT(polygonButtonPressed()));

    QPushButton *selectionButton = new QPushButton("Selection Mode");
    selectionButton->setCheckable(true);
    connect(selectionButton, SIGNAL(pressed()), this, SLOT(changeToSelectionMode()));

    QPushButton *panButton = new QPushButton("Pan Mode");
    panButton->setCheckable(true);
    connect(panButton, SIGNAL(toggled(bool)), this, SLOT(panMode()));

    QPushButton *deleteButton = new QPushButton("Delete");
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteSelectedItem()));

    QPushButton *bringToFrontButton = new QPushButton("Bring to front");
    connect(bringToFrontButton, SIGNAL(clicked()), this, SLOT(bringToFrontClicked()));

    QPushButton *sendToBackButton = new QPushButton("Send to back");
    connect(sendToBackButton, SIGNAL(clicked()), this, SLOT(sendToBackClicked()));

    QPushButton *includeButton = new QPushButton("Include area");
    connect(includeButton, SIGNAL(clicked()), this, SLOT(includeClicked()));

    QPushButton *excludeButton = new QPushButton("Exclude area");
    connect(excludeButton, SIGNAL(clicked()), this, SLOT(excludeClicked()));

    QPushButton *drawingButton = new QPushButton("Drawing Mode");
    drawingButton->setCheckable(true);
    connect(drawingButton, SIGNAL(pressed()), this, SLOT(changeToDrawingMode()));

    connect(m_scene, SIGNAL(itemIsDrawn()), selectionButton, SLOT(click()));

    QGroupBox *drawingMode = new QGroupBox(this);
    QVBoxLayout *drawingModeLayout = new QVBoxLayout;
    drawingMode->setLayout(drawingModeLayout);
    drawingMode->setTitle("Drawing Mode");
    drawingModeLayout->addWidget(rectangleButton);
    drawingModeLayout->addWidget(ellipseButton);
    drawingModeLayout->addWidget(polygonButton);
    drawingModeLayout->addWidget(panButton);
    drawingModeLayout->addWidget(selectionButton);
//    drawingMode->setDisabled(true);

    QGroupBox *selectionMode = new QGroupBox(this);
    QVBoxLayout *selectionModeBoxLayout = new QVBoxLayout;
    selectionMode->setLayout(selectionModeBoxLayout);
    selectionMode->setTitle("Selection Mode");
    selectionModeBoxLayout->addWidget(includeButton);
    selectionModeBoxLayout->addWidget(excludeButton);
    selectionModeBoxLayout->addWidget(deleteButton);
    selectionModeBoxLayout->addWidget(bringToFrontButton);
    selectionModeBoxLayout->addWidget(sendToBackButton);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(rectangleButton);
    buttonGroup->addButton(ellipseButton);
    buttonGroup->addButton(polygonButton);
    buttonGroup->addButton(panButton);
    buttonGroup->addButton(selectionButton);

    // create widget with buttons
    QWidget *buttons = new QWidget(this);
//    buttons->resize(200,200);
    m_buttonLayout->addWidget(drawingMode);
    m_buttonLayout->addWidget(selectionMode);
    buttons->setLayout(m_buttonLayout);



    //add scene and buttons into widget
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(buttons);
    this->setLayout(mainLayout);



}

void MaskEditor::rectangleButtonPressed()
{
    m_scene->setDrawing(MaskGraphicsScene::RECTANGLE);

    qDebug() << "void MaskEditor::rectangleButtonPressed()";
}

void MaskEditor::ellipseButtonPressed()
{
    m_scene->setDrawing(MaskGraphicsScene::ELLIPSE);
}

void MaskEditor::polygonButtonPressed()
{
    m_scene->setDrawing(MaskGraphicsScene::POLYGON);
}

void MaskEditor::panMode()
{
    if(((QPushButton*) this->sender())->isChecked()) {
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
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        selectedItems[i]->setZValue(selectedItems[i]->zValue()+1);
    }
    qDebug() << "void MaskEditor::bringToFrontClicked()-> current value:" << selectedItems[0]->zValue();
}

void MaskEditor::sendToBackClicked()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        selectedItems[i]->setZValue(selectedItems[i]->zValue()-1);
    }
    // To make sure that ColorMap is always bottom level item
    if(m_proxyWidget->zValue() > selectedItems[0]->zValue()) {
            m_proxyWidget->setZValue(selectedItems[0]->zValue()-1);
    }
    qDebug() << "void MaskEditor::sendToBackClicked()-> current value:" << selectedItems[0]->zValue();
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

    QListView *listView = new QListView;
    listView->setModel(maskModel);
    m_scene->setModel(maskModel);

//    ParameterizedItem *item = maskModel->insertNewItem(Constants::RectangleType);
//    item->setRegisteredProperty(RectangleItem::P_WIDTH, 100.0);
//    item->setRegisteredProperty(RectangleItem::P_HEIGHT, 100.0);
//    item->setRegisteredProperty(RectangleItem::P_POSX, 100.0);
//    item->setRegisteredProperty(RectangleItem::P_POSY, 100.0);
//    item->setRegisteredProperty(RectangleItem::P_ANGLE, 30.0);

//    AwesomePropertyEditor *m_editor = new AwesomePropertyEditor();
//    m_editor->setItem(item);
//    m_buttonLayout->addWidget(m_editor);

    m_scene->setSelectionModel(listView->selectionModel());
    m_buttonLayout->addWidget(listView);
}



