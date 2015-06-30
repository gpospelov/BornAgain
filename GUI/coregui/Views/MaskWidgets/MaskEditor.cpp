#include <QDebug>
#include "DistributionEditor.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <ColorMapPlot.h>
#include "GraphicsProxyWidget.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "ColorMapPlot.h"
#include "IntensityDataItem.h"
#include "SimulationRegistry.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "MaskEditor.h"
#include "RectangleView.h"
#include "AwesomePropertyEditor.h"
#include "RectangleItem.h"
#include "RectangleView.h"

MaskEditor::MaskEditor(QWidget *parent)
    : QWidget(parent)
    , m_scene(new GraphicsScene)
    , m_view(new GraphicsView)
    , m_buttonLayout(new QVBoxLayout)
{

    setMouseTracking(true);
    m_view->setMouseTracking(true);
    m_view->setRenderHint(QPainter::HighQualityAntialiasing);
    m_view->setRenderHint(QPainter::TextAntialiasing);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setScene(m_scene);
    m_scene->setSceneRect(m_view->viewport()->frameGeometry());



    // convert widget into custom QProxywidget and put it in to the scene
//    SimulationRegistry sim_registry;
//    Simulation *sim = sim_registry.createSimulation("cylinders_ba");
//    sim->runSimulation();
//    IntensityDataItem *dataItem = new IntensityDataItem;
//    dataItem->setOutputData(sim->getIntensityData());

//    ColorMapPlot *colorMapPlot = new ColorMapPlot;
//    colorMapPlot->setItem(dataItem);


//    GraphicsProxyWidget *widget = new GraphicsProxyWidget;
//    widget->setWidget(colorMapPlot);
//    widget->resize(m_scene->width(), m_scene->height());
//    m_widget = widget;
//    m_scene->addItem(widget);


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
    QWidget *buttons = new QWidget;
    m_buttonLayout->addWidget(drawingMode);
    m_buttonLayout->addWidget(selectionMode);
    m_buttonLayout->addStretch(1);
    buttons->setLayout(m_buttonLayout);



    //add scene and buttons into widget
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(buttons);
    this->setLayout(mainLayout);
}

void MaskEditor::rectangleButtonPressed()
{
    m_scene->setDrawing(GraphicsScene::RECTANGLE);
    qDebug() << "void MaskEditor::rectangleButtonPressed()";
}

void MaskEditor::ellipseButtonPressed()
{
    m_scene->setDrawing(GraphicsScene::ELLIPSE);
}

void MaskEditor::polygonButtonPressed()
{
    m_scene->setDrawing(GraphicsScene::POLYGON);
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
    if(m_widget->zValue() > selectedItems[0]->zValue()) {
            m_widget->setZValue(selectedItems[0]->zValue()-1);
    }
    qDebug() << "void MaskEditor::sendToBackClicked()-> current value:" << selectedItems[0]->zValue();
}

void MaskEditor::includeClicked()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        if(Rectangle::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<RectangleView* >(selectedItems[i])->setInclude();
        }
        else if(Ellipse::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<Ellipse* >(selectedItems[i])->setInclude();
        }
        else if(Polygon::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<Polygon* >(selectedItems[i])->setInclude();
        }
    }
}

void MaskEditor::excludeClicked()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        if(Rectangle::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<RectangleView * >(selectedItems[i])->setExclude();
        }
        else if(Ellipse::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<Ellipse* >(selectedItems[i])->setExclude();
        }
        else if(Polygon::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<Polygon* >(selectedItems[i])->setExclude();
        }
    }
}

void MaskEditor::changeToSelectionMode()
{
    m_scene->setDrawing(GraphicsScene::NONE);
}

void MaskEditor::changeToDrawingMode()
{
    m_view->setDragMode(QGraphicsView::NoDrag);
    m_view->setInteractive(true);
}

void MaskEditor::setModel(MaskModel *maskModel)
{
    m_scene->setModel(maskModel);
    QTreeView *treeView = new QTreeView;
    m_scene->setTreeView(treeView);
    m_buttonLayout->addWidget(treeView);
}



