// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestDetectorResolution.cpp
//! @brief     Implements class TestDetectorResolution.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestDetectorResolution.h"

#include "IsGISAXSTools.h"
#include "Types.h"
#include "Units.h"
#include "Simulation.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "MathFunctions.h"
#include "ResolutionFunction2DSimple.h"


void TestDetectorResolution::execute()
{
    if (mp_intensity_output) delete mp_intensity_output;
    initializeSample();
    Simulation simulation(mp_options);
    simulation.setSample(*mp_sample);
    simulation.setDetectorParameters
        (100, 0.0*Units::degree, 2.0*Units::degree,
         100, 0.0*Units::degree, 2.0*Units::degree);
    IResolutionFunction2D *p_resolution_function =
        new ResolutionFunction2DSimple(0.001, 0.001);
    simulation.setDetectorResolutionFunction(p_resolution_function);
    simulation.setBeamParameters
        (1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    simulation.runSimulation();
    mp_intensity_output = simulation.getIntensityData();
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
    const IMaterial *p_air_material =
        MaterialManager::getHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material =
        MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);

    const IMaterial *particle_material =
            MaterialManager::getHomogeneousMaterial("Particle", 5e-5, 2e-8);

    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_funtion =
        new InterferenceFunction1DParaCrystal(20.0*Units::nanometer,
            7*Units::nanometer, 1e7*Units::nanometer);
    ParticleDecoration particle_decoration(
        new Particle(particle_material,
                     new FormFactorCylinder(5*Units::nanometer,
                                            5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_funtion);

    air_layer.setDecoration(particle_decoration);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;
}


