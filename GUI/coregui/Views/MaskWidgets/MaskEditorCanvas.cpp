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

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    init_widget();
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

    m_scene->setSceneRect(0,0,500, 500);

    qDebug() << "XXX SceneRect " << m_scene->width() << m_scene->height() << m_scene->sceneRect().topLeft();

    m_graphicsProxy->setWidget(plot);
    m_graphicsProxy->setPos(m_scene->sceneRect().topLeft());
    m_graphicsProxy->resize(m_scene->width(), m_scene->height());

    m_scene->addItem(m_graphicsProxy);
}
