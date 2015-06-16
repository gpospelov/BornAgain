// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestView.cpp
//! @brief     Implements class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestView.h"
#include "TestItem.h"
#include "LayerItem.h"
#include "AwesomePropertyEditor.h"
#include "BeamWavelengthItem.h"
#include "ParameterizedItem.h"
//#include <QGroupBox>
#include <QGridLayout>
#include <QDebug>
#include "DistributionEditor.h"
#include "qgroupbox.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <ColorMapPlot.h>
#include "DistributionDialog.h"
#include "DistributionWidget.h"
#include "GraphicsProxyWidget.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "ColorMapPlot.h"
#include "IntensityDataItem.h"
#include "SimulationRegistry.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"

TestView::TestView(QWidget *parent)
    : QWidget(parent), m_scene(new GraphicsScene), m_view(new GraphicsView),
      m_buttonGroup(new QButtonGroup(this))
{

    // set scene into view and switch of scrollbar from view
    setMouseTracking(true);
    m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
//    m_view->resize(10000,10000);
    m_view->setMouseTracking(true);
//    m_view->setAcceptDrops(true);
//    m_view->setAcceptDrops(true);
//    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setRenderHint(QPainter::HighQualityAntialiasing);
    m_view->setRenderHint(QPainter::TextAntialiasing);
//    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->showMaximized();
    m_scene->setSceneRect(m_view->viewport()->rect());
    m_view->setScene(m_scene);

    // convert widget into custom QProxywidget and put it in to the scene
//    DistributionEditor *editor = new DistributionEditor;
//    editor->setItem(new BeamWavelengthItem);
//    editor->resize(800, 600);

    SimulationRegistry sim_registry;
    Simulation *sim = sim_registry.createSimulation("cylinders_ba");
    sim->runSimulation();
    IntensityDataItem *dataItem = new IntensityDataItem;
    dataItem->setOutputData(sim->getIntensityData());

    ColorMapPlot *colorMapPlot = new ColorMapPlot;
    colorMapPlot->setItem(dataItem);


    GraphicsProxyWidget *widget = new GraphicsProxyWidget;
//    widget->resize(m_view->viewport()->rect().width(), m_view->viewport()->rect().height());
    widget->setWidget(colorMapPlot);
    m_scene->addItem(widget);

    m_view->fitInView(widget);

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

    QPushButton *selectionButton = new QPushButton("Change to Selection Mode");
    selectionButton->setCheckable(true);
    connect(selectionButton, SIGNAL(pressed()), this, SLOT(changeToSelectionMode()));

    QGroupBox *drawingMode = new QGroupBox(this);
    QVBoxLayout *drawingModeLayout = new QVBoxLayout;
    drawingMode->setLayout(drawingModeLayout);
    drawingMode->setTitle("Drawing Mode");
    drawingModeLayout->addWidget(rectangleButton);
    drawingModeLayout->addWidget(ellipseButton);
    drawingModeLayout->addWidget(polygonButton);
    drawingModeLayout->addWidget(selectionButton);
    drawingMode->setDisabled(true);


    QPushButton *panButton = new QPushButton("Pan Mode");
//    panButton->setCheckable(true);
    connect(panButton, SIGNAL(pressed()), this, SLOT(panMode()));

    QPushButton *deleteButton = new QPushButton("Delete");
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteSelectedItem()));

    QPushButton *bringToFrontButton = new QPushButton("Bring to front");
    connect(bringToFrontButton, SIGNAL(clicked()), this, SLOT(bringToFrontClicked()));

    QPushButton *sendToBackButton = new QPushButton("Send to back");
    connect(sendToBackButton, SIGNAL(toggled(bool)), this, SLOT(sendToBackClicked()));

    QPushButton *includeButton = new QPushButton("Include area");
//    includeButton->setCheckable(true);
    connect(includeButton, SIGNAL(clicked()), this, SLOT(includeClicked()));

    QPushButton *excludeButton = new QPushButton("Exclude area");
//    excludeButton->setCheckable(true);
    connect(excludeButton, SIGNAL(clicked()), this, SLOT(excludeClicked()));

    QPushButton *drawingButton = new QPushButton("Change to Drawing Mode");
    drawingButton->setCheckable(true);
    connect(drawingButton, SIGNAL(pressed()), this, SLOT(changeToDrawingMode()));

    QGroupBox *selectionMode = new QGroupBox(this);
    QVBoxLayout *selectionModeBoxLayout = new QVBoxLayout;
    selectionMode->setLayout(selectionModeBoxLayout);
    selectionMode->setTitle("Selection Mode");
    selectionModeBoxLayout->addWidget(includeButton);
    selectionModeBoxLayout->addWidget(excludeButton);
    selectionModeBoxLayout->addWidget(deleteButton);
    selectionModeBoxLayout->addWidget(bringToFrontButton);
    selectionModeBoxLayout->addWidget(sendToBackButton);
    selectionModeBoxLayout->addWidget(panButton);
    selectionModeBoxLayout->addWidget(drawingButton);

    connect(selectionButton, SIGNAL(clicked(bool)), drawingMode, SLOT(setDisabled(bool)));
    connect(selectionButton, SIGNAL(clicked(bool)), selectionMode, SLOT(setEnabled(bool)));

    connect(drawingButton, SIGNAL(clicked(bool)), selectionMode, SLOT(setDisabled(bool)));
    connect(drawingButton, SIGNAL(clicked(bool)), drawingMode, SLOT(setEnabled(bool)));

    m_buttonGroup->addButton(rectangleButton);
    m_buttonGroup->addButton(ellipseButton);
    m_buttonGroup->addButton(polygonButton);
//    m_buttonGroup->addButton(sendToBackButton);
//    m_buttonGroup->addButton(panButton);
//    m_buttonGroup->addButton(includeButton);
//    m_buttonGroup->addButton(excludeButton);
//    m_buttonGroup->addButton(deleteButton);
//    m_buttonGroup->addButton(sendToBackButton);
//    m_buttonGroup->addButton(bringToFrontButton);
    m_buttonGroup->addButton(selectionButton);
    m_buttonGroup->addButton(drawingButton);

    // create widget with buttons
    QWidget *buttons = new QWidget;
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(drawingMode);
    buttonLayout->addWidget(selectionMode);
//    buttonLayout->addWidget(includeButton);
//    buttonLayout->addWidget(excludeButton);
//    buttonLayout->addWidget(rectangleButton);
//    buttonLayout->addWidget(ellipseButton);
//    buttonLayout->addWidget(polygonButton);
//    buttonLayout->addWidget(panButton);
//    buttonLayout->addWidget(deleteButton);
//    buttonLayout->addWidget(bringToFrontButton);
//    buttonLayout->addWidget(sendToBackButton);
//    buttonLayout->addWidget(selectionButton);
    buttonLayout->addStretch(1);
    buttons->setLayout(buttonLayout);


    //add scene and buttons into widget
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(buttons);
    this->setLayout(mainLayout);
}

void TestView::rectangleButtonPressed()
{
    m_scene->setDrawing(GraphicsScene::RECTANGLE);
}

void TestView::ellipseButtonPressed()
{
    m_scene->setDrawing(GraphicsScene::ELLIPSE);
}

void TestView::polygonButtonPressed()
{
    m_scene->setDrawing(GraphicsScene::POLYGON);
}

void TestView::panMode()
{
    if(dynamic_cast<QPushButton*> (this->sender())->isChecked()) {
        m_view->setDragMode(QGraphicsView::ScrollHandDrag);
        m_view->setInteractive(false);
    }
    else {
        m_view->setDragMode(QGraphicsView::NoDrag);
        m_view->setInteractive(true);
    }
}

void TestView::deleteSelectedItem()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        m_scene->removeItem(selectedItems[i]);
    }

}

void TestView::bringToFrontClicked()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        selectedItems[i]->setZValue(selectedItems[i]->zValue()+1);
    }
}

void TestView::sendToBackClicked()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        selectedItems[i]->setZValue(selectedItems[i]->zValue()-1);
    }
}

void TestView::includeClicked()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        if(Rectangle::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<Rectangle * >(selectedItems[i])->setInclude();
        }
        else if(Ellipse::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<Ellipse* >(selectedItems[i])->setInclude();
        }
        else if(Polygon::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<Polygon* >(selectedItems[i])->setInclude();
        }
    }
}

void TestView::excludeClicked()
{
    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    for(int i = 0; i < selectedItems.length(); ++i) {
        if(Rectangle::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<Rectangle * >(selectedItems[i])->setExclude();
        }
        else if(Ellipse::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<Ellipse* >(selectedItems[i])->setExclude();
        }
        else if(Polygon::Type == selectedItems[i]->type()) {
            qgraphicsitem_cast<Polygon* >(selectedItems[i])->setExclude();
        }
    }
}

void TestView::changeToSelectionMode()
{
    m_scene->setDrawing(GraphicsScene::NONE);
}

void TestView::changeToDrawingMode()
{
    m_view->setDragMode(QGraphicsView::NoDrag);
    m_view->setInteractive(true);
}


