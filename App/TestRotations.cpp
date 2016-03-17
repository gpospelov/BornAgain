// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestRoughness.cpp
//! @brief     Implements class TestRoughness.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestRotations.h"
#include "SimulationRegistry.h"
#include "SampleBuilderFactory.h"
#include "FormFactors.h"
#include "MultiLayer.h"
#include "ParticleComposition.h"
#include "HomogeneousMaterial.h"
#include "Simulation.h"
#include "IntensityDataFunctions.h"
#include "OutputData.h"
#include <iostream>
#include <memory>

void TestRotations::execute()
{
    std::cout << "TestRotations::execute()" << std::endl;

    SimulationRegistry simRegistry;
    const std::unique_ptr<Simulation> simulation(simRegistry.createSimulation("BasicGISAS"));

    ThreadInfo thread_info;
    thread_info.n_threads = -1;

    simulation->setThreadInfo(thread_info);

    // reference simulation
    const std::unique_ptr<MultiLayer> box(createReferenceSample());
    simulation->setSample(*box);
    simulation->runSimulation();
    const std::unique_ptr<OutputData<double> > reference(simulation->getDetectorIntensity());

    // simulation with composition
    const std::unique_ptr<MultiLayer> composition(createComposition());
    simulation->setSample(*composition);
    simulation->runSimulation();
    const std::unique_ptr<OutputData<double> > data(simulation->getDetectorIntensity());

    double diff = IntensityDataFunctions::getRelativeDifference(*data, *reference);
    std::cout << "diff:" << diff << std::endl;
}


MultiLayer *TestRotations::createComposition()
{
    const double layer_thickness(100.0);
    const double length(50.0), width(20.0), height(10.0);

    HomogeneousMaterial mAmbience("Air", 0.0, 0.0);
    HomogeneousMaterial mMiddle("Teflon", 2.900e-6, 6.019e-9);
    HomogeneousMaterial mSubstrate("Substrate", 3.212e-6, 3.244e-8);
    HomogeneousMaterial mCore("Ag", 1.245e-5, 5.419e-7);

    // composition
    Particle box(mCore, FormFactorBox(length/2, width, height));
    ParticleComposition composition;
    composition.addParticle(box, kvector_t(0, 0, 0));
    composition.addParticle(box, kvector_t(length/2, 0, 0));
    composition.setRotation(RotationY(90*Units::degree));
    composition.setPosition(kvector_t(0, 0, -layer_thickness/2 + length/4));

    ParticleLayout layout;
    layout.addParticle(composition);

    Layer air_layer(mAmbience);
    Layer middle_layer(mMiddle, layer_thickness);
    middle_layer.addLayout(layout);
    Layer substrate(mSubstrate);

    MultiLayer *multi_layer = new MultiLayer();
    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(middle_layer);
    multi_layer->addLayer(substrate);
    return multi_layer;
}


MultiLayer *TestRotations::createReferenceSample()
{
    const double layer_thickness(100.0);
    const double length(10.0), width(20.0), height(50.0);

    HomogeneousMaterial mAmbience("Air", 0.0, 0.0);
    HomogeneousMaterial mMiddle("Teflon", 2.900e-6, 6.019e-9);
    HomogeneousMaterial mSubstrate("Substrate", 3.212e-6, 3.244e-8);
    HomogeneousMaterial mCore("Ag", 1.245e-5, 5.419e-7);

    // composition
    Particle box(mCore, FormFactorBox(length, width, height));
    box.setPosition(kvector_t(0, 0, -layer_thickness/2 - height/2));

    ParticleLayout layout;
    layout.addParticle(box);

    Layer air_layer(mAmbience);
    Layer middle_layer(mMiddle, layer_thickness);
    middle_layer.addLayout(layout);
    Layer substrate(mSubstrate);

    MultiLayer *multi_layer = new MultiLayer();
    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(middle_layer);
    multi_layer->addLayer(substrate);
    return multi_layer;
}
