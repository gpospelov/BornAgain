// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestDetectorResolution.cpp
//! @brief     Implements class TestDetectorResolution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestDetectorResolution.h"

#include "IsGISAXSTools.h"
#include "Types.h"
#include "Units.h"
#include "Simulation.h"
#include "MultiLayer.h"
#include "Materials.h"
#include "MathFunctions.h"
#include "ResolutionFunction2DGaussian.h"


void TestDetectorResolution::execute()
{
    if (mp_intensity_output) delete mp_intensity_output;
    initializeSample();
    GISASSimulation simulation(mp_options);
    simulation.setSample(*mp_sample);
    simulation.setDetectorParameters
        (100, 0.0*Units::degree, 2.0*Units::degree,
         100, 0.0*Units::degree, 2.0*Units::degree);
    ResolutionFunction2DGaussian resfunc(0.001, 0.001);
    simulation.setDetectorResolutionFunction(resfunc);
    simulation.setBeamParameters
        (1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    simulation.runSimulation();
    mp_intensity_output = simulation.getDetectorIntensity();
    IsGISAXSTools::drawLogOutputData
        (*mp_intensity_output,
         "c1_test_detector_resolution",
         "Detector resolution",
         "CONT4 Z",
         "Detector resolution");
}

void TestDetectorResolution::initializeSample()
{
    delete mp_sample;
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-5e-6, 2e-8);
    HomogeneousMaterial air_material("Air", n_air);
    HomogeneousMaterial substrate_material("Substrate", n_substrate);
    HomogeneousMaterial particle_material("Particle", 5e-5, 2e-8);

    Layer air_layer;
    air_layer.setMaterial(air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(substrate_material);
    InterferenceFunctionRadialParaCrystal *p_interference_function =
        new InterferenceFunctionRadialParaCrystal(20.0*Units::nanometer,
            1e7*Units::nanometer);
    FTDistribution1DGauss pdf(7*Units::nanometer);
    p_interference_function->setProbabilityDistribution(pdf);
    Particle particle(particle_material, FormFactorCylinder(5*Units::nanometer,
                                                            5*Units::nanometer));
    ParticleLayout particle_layout(particle);
    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.addLayout(particle_layout);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;
}


