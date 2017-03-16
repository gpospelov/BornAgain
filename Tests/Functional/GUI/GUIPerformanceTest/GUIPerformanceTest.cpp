// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIPerformanceTest/GUIPerformanceTest.cpp
//! @brief     Implements GUI performance functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIPerformanceTest.h"
#include "Benchmark.h"
#include "ApplicationModels.h"
#include "SampleBuilderFactory.h"
#include "GUIObjectBuilder.h"
#include "MultiLayer.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "DomainSimulationBuilder.h"
#include "GISASSimulation.h"
#include "JobItem.h"
#include "JobModel.h"
#include "DocumentModel.h"
#include "ParameterTreeUtils.h"
#include "ParameterTreeItems.h"
#include "InstrumentItem.h"
#include "DetectorItems.h"
#include "ModelPath.h"
#include "IntensityDataItem.h"
#include "FitParameterHelper.h"
#include <QCoreApplication>
#include <random>
#include <QDebug>

namespace {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> rndm_radius(5., 6.);
}

GUIPerformanceTest::GUIPerformanceTest()
    : m_models(new ApplicationModels(nullptr))
    , m_sample_name("ParticleCompositionBuilder")
{
}

GUIPerformanceTest::~GUIPerformanceTest()
{

}

bool GUIPerformanceTest::runTest()
{
#ifndef NDEBUG
    const int mult = 1;
#else
    const int mult = 10;
#endif

    std::cout << "GUIPerformanceTest -> Running ..." << mult << std::endl;
    Benchmark bench;

    bench.test("domain2gui", [this]() { test_domain_to_gui();}, 300*mult);
    bench.test("gui2domain", [this]() { test_gui_to_domain();}, 300*mult);
    bench.test("realTime", [this]() { test_real_time();}, 20*mult);

    std::cout << bench.report().toStdString() << std::endl;
    return true;
}

//! Creates domain sample once and then populates sample model.

void GUIPerformanceTest::test_domain_to_gui()
{
    static std::unique_ptr<ISample> sample;

    if(!sample) {
        m_models->resetModels();
        SampleBuilderFactory factory;
        sample.reset(factory.createSample(m_sample_name.toStdString()));
    }

    m_models->sampleModel()->clear();
    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(m_models->sampleModel(), *sample);
}

//! Creates gui sample once and then populates domain.

void GUIPerformanceTest::test_gui_to_domain()
{
    static bool is_initialized(false);

    if(!is_initialized) {
        is_initialized = true;

        m_models->resetModels();

        SampleBuilderFactory factory;
        const std::unique_ptr<ISample> sample(factory.createSample(m_sample_name.toStdString()));

        GUIObjectBuilder guiBuilder;
        guiBuilder.populateSampleModel(m_models->sampleModel(), *sample);

    }

    std::unique_ptr<GISASSimulation> sim(DomainSimulationBuilder::getSimulation(
        m_models->sampleModel()->multiLayerItem(),
        m_models->instrumentModel()->instrumentItem()));
}

void GUIPerformanceTest::test_real_time()
{
    static JobItem* jobItem(0);

    if(!jobItem) {
        m_models->resetModels();

        SimulationOptionsItem *optionsItem = m_models->documentModel()->getSimulationOptionsItem();

        SampleBuilderFactory factory;
        const std::unique_ptr<ISample> sample(factory.createSample(m_sample_name.toStdString()));

        GUIObjectBuilder guiBuilder;
        guiBuilder.populateSampleModel(m_models->sampleModel(), *sample);

        m_models->instrumentModel()->instrumentItem()->detectorItem()->setSize(25, 25);

        jobItem = m_models->jobModel()->addJob(
                   m_models->sampleModel()->multiLayerItem(),
                   m_models->instrumentModel()->instrumentItem(),
                   0,
                   optionsItem);

    }

    SessionItem *container = jobItem->parameterContainerItem();

//    ParameterTreeUtils::visitParameterContainer(container, [&](ParameterItem* parItem)
//    {
//        QString parPath = FitParameterHelper::getParameterItemPath(parItem);
//        qDebug() << parPath;
//    });

    ParameterItem* parItem = dynamic_cast<ParameterItem*>(ModelPath::getItemFromPath(
        "MultiLayer/Layer0/ParticleLayout/ParticleComposition/Particle1/FullSphere/Radius",
                                                              container));
    Q_ASSERT(parItem);

    double radius = rndm_radius(mt);
    parItem->propagateValueToLink(radius);

    m_models->jobModel()->runJob(jobItem->index());

    while(m_models->jobModel()->hasUnfinishedJobs())
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
}

