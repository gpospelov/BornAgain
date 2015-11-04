// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorCanvas.cpp
//! @brief     Implements class MaskEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskEditorCanvas.h"
#include "MaskGraphicsScene.h"
#include "MaskGraphicsView.h"
#include "MaskGraphicsProxy.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QGraphicsRectItem>

#include "SimulationRegistry.h"
#include <boost/scoped_ptr.hpp>
#include "SampleBuilderFactory.h"
#include "IntensityDataItem.h"
#include "ColorMapPlot.h"

MaskEditorCanvas::MaskEditorCanvas(QWidget *parent)
    : QWidget(parent)
    , m_scene(new MaskGraphicsScene(this))
    , m_view(new MaskGraphicsView(m_scene, this))
    , m_graphicsProxy(new MaskGraphicsProxy)
{
    setObjectName(QStringLiteral("MaskEditorCanvas"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_view->setColorMapProxy(m_graphicsProxy);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

//    init_widget();
}

void MaskEditorCanvas::setModel(SessionModel *model)
{
    m_scene->setModel(model);
}

void MaskEditorCanvas::resizeEvent(QResizeEvent *event)
{
    qDebug() << "MaskEditorCanvas::resizeEvent()" << event->size();
    QWidget::resizeEvent(event);

}

void MaskEditorCanvas::init_widget()
{
    SimulationRegistry simRegistry;
    boost::scoped_ptr<GISASSimulation> simulation(simRegistry.createSimulation("BasicGISAS"));

    SampleBuilderFactory sampleFactory;
    boost::scoped_ptr<ISample> sample(sampleFactory.createSample("CylindersAndPrismsBuilder"));

    simulation->setSample(*sample.get());
    simulation->runSimulation();

    IntensityDataItem *item = new IntensityDataItem;
    item->setOutputData(simulation->getOutputData()->clone());

    ColorMapPlot *plot = new ColorMapPlot;
    plot->setItem(item);
    plot->resize(800,600);

    m_scene->setSceneRect(0,0,800, 600);

    qDebug() << "XXX SceneRect " << m_scene->width() << m_scene->height() << m_scene->sceneRect().topLeft();

    m_graphicsProxy->setPos(m_scene->sceneRect().topLeft());
    m_graphicsProxy->resize(m_scene->width(), m_scene->height());
    m_graphicsProxy->setWidget(plot);
    m_graphicsProxy->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);

    m_scene->addItem(m_graphicsProxy);

    QGraphicsRectItem *b_rect = new QGraphicsRectItem(0, 0, 800, 600);
    b_rect->setPos(0, 0);
    b_rect->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    m_scene->addItem(b_rect);

    QGraphicsRectItem *b_rect2 = new QGraphicsRectItem(1, 1, 798, 598);
    b_rect2->setPos(1, 1);
    b_rect2->setPen(QPen(Qt::red));
    m_scene->addItem(b_rect2);


    QGraphicsRectItem *rect = new QGraphicsRectItem(400, 300, 300, 100);
    m_scene->addItem(rect);
}
