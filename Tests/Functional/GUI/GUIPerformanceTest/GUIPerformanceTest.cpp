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
#include <QDebug>

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
    Benchmark bench;

    bench.test("domain2gui", [this]() { test_domain_to_gui();}, 300);
    bench.test("gui2domain", [this]() { test_gui_to_domain();}, 300);
//    bench.test("realTime", [this]() { test_real_time();}, 1);

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

