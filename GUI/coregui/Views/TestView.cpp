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
      m_rectangleButton(new QPushButton("Rectangle")), m_ellipseButton(new QPushButton("Ellipse")),
      m_polygonButton(new QPushButton("Polygon")),m_panButton(new QPushButton("Pan Mode"))
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
    widget->resize(m_view->viewport()->rect().width(), m_view->viewport()->rect().height());
    widget->setWidget(colorMapPlot);
    m_scene->addItem(widget);

    // -----------------------
    QGraphicsRectItem *rect1 = new QGraphicsRectItem(0,0,100,100);
    rect1->setFlag(QGraphicsItem::ItemIsSelectable);
    rect1->setFlag(QGraphicsItem::ItemIsMovable);
    rect1->setBrush(Qt::red);
    QGraphicsRectItem *rect2 = new QGraphicsRectItem(0,0,100,100);
    rect2->setFlag(QGraphicsItem::ItemIsSelectable);
    rect2->setFlag(QGraphicsItem::ItemIsMovable);
    rect2->setBrush(Qt::blue);

    m_scene->addItem(rect1);
    m_scene->addItem(rect2);

    //-------------------------


    // connect buttons
    m_rectangleButton->setCheckable(true);
    connect(m_rectangleButton, SIGNAL(pressed()), this, SLOT(rectangleButtonPressed()));

    m_ellipseButton->setCheckable(true);
    connect(m_ellipseButton, SIGNAL(pressed()), this, SLOT(ellipseButtonPressed()));

    m_polygonButton->setCheckable(true);
    connect(m_polygonButton, SIGNAL(pressed()), this, SLOT(polygonButtonPressed()));

    m_panButton->setCheckable(true);
    connect(m_panButton, SIGNAL(pressed()), this, SLOT(panMode()));

    QPushButton *deleteButton = new QPushButton("Delete");
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteSelectedItem()));

    QPushButton *bringToFrontButton = new QPushButton("Bring to front");
    connect(bringToFrontButton, SIGNAL(clicked()), this, SLOT(bringToFrontClicked));

    QPushButton *sendToBackButton = new QPushButton("Send to back");
    connect(sendToBackButton, SIGNAL(clicked()), this, SLOT(sendToBackClicked()));


    // create widget with buttons
    QWidget *buttons = new QWidget;
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(new QPushButton("Include"));
    buttonLayout->addWidget(new QPushButton("Exclude"));
    buttonLayout->addWidget(new QPushButton("Drawing Mode"));
    buttonLayout->addWidget(m_rectangleButton);
    buttonLayout->addWidget(m_ellipseButton);
    buttonLayout->addWidget(m_polygonButton);
    buttonLayout->addWidget(m_panButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(bringToFrontButton);
    buttonLayout->addWidget(sendToBackButton);
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
    m_ellipseButton->setChecked(false);
    m_polygonButton->setChecked(false);
    m_panButton->setChecked(false);

    if(m_rectangleButton->isChecked()) {
        m_scene->setDrawing(GraphicsScene::NONE);
    }
    else {
        m_scene->setDrawing(GraphicsScene::RECTANGLE);
    }
}

void TestView::ellipseButtonPressed()
{
    m_rectangleButton->setChecked(false);
    m_polygonButton->setChecked(false);
    m_panButton->setChecked(false);

    if(m_ellipseButton->isChecked()) {
        m_scene->setDrawing(GraphicsScene::NONE);
    }
    else {
        m_scene->setDrawing(GraphicsScene::ELLIPSE);
    }
}

void TestView::polygonButtonPressed()
{
    m_rectangleButton->setChecked(false);
    m_ellipseButton->setChecked(false);
    m_panButton->setChecked(false);

    if(m_polygonButton->isChecked()) {
        m_scene->setDrawing(GraphicsScene::NONE);
    }
    else {
        m_scene->setDrawing(GraphicsScene::POLYGON);
    }
}

void TestView::panMode()
{
    m_rectangleButton->setChecked(false);
    m_ellipseButton->setChecked(false);
    m_polygonButton->setChecked(false);

    if(!m_panButton->isChecked()) {
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
    m_rectangleButton->setChecked(false);
    m_ellipseButton->setChecked(false);
    m_polygonButton->setChecked(false);
    m_panButton->setChecked(false);

    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
     qDebug() << "TestView::deleteSelectedItem()-> " << selectedItems.length();
    for(int i = 0; i < selectedItems.length(); ++i) {
        delete selectedItems.at(i);
    }

}

void TestView::bringToFrontClicked()
{
    m_rectangleButton->setChecked(false);
    m_ellipseButton->setChecked(false);
    m_polygonButton->setChecked(false);
    m_panButton->setChecked(false);

    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    qDebug() << "TestView::deleteSelectedItem()-> " << selectedItems.length();
    for(int i = 0; i < selectedItems.length(); ++i) {
        qDebug() << selectedItems[i]->zValue();
        selectedItems[i]->setZValue(selectedItems[i]->zValue()+1);
    }
}

void TestView::sendToBackClicked()
{
    m_rectangleButton->setChecked(false);
    m_ellipseButton->setChecked(false);
    m_polygonButton->setChecked(false);
    m_panButton->setChecked(false);

    QList<QGraphicsItem*> selectedItems = m_view->scene()->selectedItems();
    qDebug() << "TestView::deleteSelectedItem()-> " << selectedItems.length();
    for(int i = 0; i < selectedItems.length(); ++i) {
        qDebug() << selectedItems[i]->zValue();
        selectedItems[i]->setZValue(selectedItems[i]->zValue()-1);
    }
}
