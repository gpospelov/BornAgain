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

// Can we move push button along graphics scene?
// How to insert widget into specified position?
// If widget is active, why CustomPlot  (ColorMapPlot) is not reacting?
// Are there some

TestView::TestView(QWidget *parent)
    : QWidget(parent), m_scene(new QGraphicsScene), m_view(new QGraphicsView),
      m_rectangle(new Rectangle(0, 0, 100, 100)), m_ellipse(new Ellipse(0, 0, 100, 50)),
      m_polygon(new Polygon(0, 0, 100, 100))
{
    // set scene into view and switch of scrollbar from view
    setMouseTracking(true);
    m_view->setMouseTracking(true);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->showMaximized();
    m_view->setScene(m_scene);

    // convert widget into custom QProxywidget and put it in to the scene
    DistributionEditor *editor = new DistributionEditor;
    editor->setItem(new BeamWavelengthItem);
    editor->resize(800, 600);
    GraphicsProxyWidget *widget = new GraphicsProxyWidget;
    widget->resize(width(), height());
    widget->setWidget(editor);
    m_scene->addItem(widget);

    // connect buttons
    QPushButton *rectangleButton = new QPushButton("Rectangle");
    connect(rectangleButton, SIGNAL(clicked()), this, SLOT(rectangleButtonClicked()));

    QPushButton *ellipseButton = new QPushButton("Ellipse");
    connect(ellipseButton, SIGNAL(clicked()), this, SLOT(ellipseButtonClicked()));

    QPushButton *polygonButton = new QPushButton("Polygon");
    connect(polygonButton, SIGNAL(clicked()), this, SLOT(polygonButtonClicked()));

    // create widget with buttons
    QWidget *buttons = new QWidget;
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(new QPushButton("Resize Mode"));
    buttonLayout->addWidget(new QPushButton("Rotation Mode"));
    buttonLayout->addWidget(new QPushButton("Drawing Mode"));
    buttonLayout->addWidget(rectangleButton);
    buttonLayout->addWidget(ellipseButton);
    buttonLayout->addWidget(polygonButton);
    buttonLayout->addStretch(1);
    buttons->setLayout(buttonLayout);

    //add scene and buttons into widget
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(buttons);
    this->setLayout(mainLayout);
}

void TestView::rectangleButtonClicked()
{
    delete m_rectangle;
    m_rectangle = new Rectangle(0, 0, 200, 200);
    m_scene->addItem(m_rectangle);
    m_rectangle->setFlag(QGraphicsItem::ItemIsMovable);
}

void TestView::ellipseButtonClicked()
{
    delete m_ellipse;
    m_ellipse = new Ellipse(0, 0, 100, 50);
    m_scene->addItem(m_ellipse);
    m_ellipse->setFlag(QGraphicsItem::ItemIsMovable);
}

void TestView::polygonButtonClicked()
{
    delete m_polygon;
    m_polygon = new Polygon(0, 0, 200, 200);
    m_scene->addItem(m_polygon);
    m_polygon->setFlag(QGraphicsItem::ItemIsMovable);
}
