// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/StandardSimulations.cpp
//! @brief     Implements functions for standard simulations.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StandardSimulations.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "ResolutionFunction2DSimple.h"
#include "Units.h"
#include "FileSystem.h"
#include "IntensityDataIOFactory.h"

Simulation *StandardSimulations::IsGISAXS01()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs01");

    Simulation *result = new Simulation();

    result->setDetectorParameters(
        100,-1.0*Units::degree, 1.0*Units::degree, 100,
        0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS02()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs02");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree,
                2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS03BA()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs03_ba");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                         100, 0.0*Units::degree, 2.0*Units::degree,
                                         true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS03DWBA()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs03_dwba");

    Simulation *result = new Simulation();


    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                      100, 0.0*Units::degree, 2.0*Units::degree,
                                      true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
             0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS03BAsize()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs03_basize");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                        100, 0.0*Units::degree, 2.0*Units::degree,
                                        true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
               0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS041DDL()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs04_1DDL");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}


Simulation *StandardSimulations::IsGISAXS042DDL()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs04_2DDL");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS06L1()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs06a");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    result->setSimulationParameters(sim_params);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS06L2()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs06b");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    result->setSimulationParameters(sim_params);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS06L3()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs06c");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    result->setSimulationParameters(sim_params);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS06L4()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs06d");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    result->setSimulationParameters(sim_params);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS07()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs07");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 1.0*Units::degree,
                100, 0.0*Units::degree, 1.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.0*Units::degree, 0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_if_approx = SimulationParameters::ISGISAXSMOR;
    result->setSimulationParameters(sim_params);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS08a()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs08a");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS08b()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs08b");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS09a()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs09a");

    Simulation *result = new Simulation();

    result->setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS09b()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs09b");

    Simulation *result = new Simulation();

    result->setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS10()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs10");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS11()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs11");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::IsGISAXS15()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs15");

    Simulation *result = new Simulation();

    result->setDetectorParameters(150, 0.05*Units::degree, 1.5*Units::degree,
            150, 0.05*Units::degree, 1.5*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    SimulationParameters sim_params;
    sim_params.me_if_approx = SimulationParameters::SSCA;
    result->setSimulationParameters(sim_params);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::MesoCrystal01()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("mesocrystal01");

    Simulation *result = new Simulation();
    result->setBeamParameters(1.77*Units::angstrom, 0.4*Units::degree, 0.0*Units::degree);
    result->setBeamIntensity(5.0090e+12);
//    result->setDetectorParameters(100, 0.5*Units::degree, 2.5*Units::degree,
//                                     120, 0.0*Units::degree, 2.5*Units::degree);

    std::string filename = Utils::FileSystem::GetReferenceDataDir() + "mesocrystal01_reference.int.gz";
    OutputData<double> *reference = IntensityDataIOFactory::readIntensityData(filename);
    result->setDetectorParameters(*reference);
    delete reference;

//    result->setDetectorResolutionFunction(
//            new ResolutionFunction2DSimple(0.0002, 0.0002));

    result->setSampleBuilder( builder );

    return result;
}


Simulation *StandardSimulations::PolarizedDWBAMagCylinders1()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("polmagcylinders1");

    Simulation *result = new Simulation();

	result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}


Simulation *StandardSimulations::PolarizedDWBAMagCylinders2()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("polmagcylinders2");

    Simulation *result = new Simulation();


    result->setDetectorParameters(
        100, -1.0*Units::degree, 1.0*Units::degree, 100,
        0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    result->setBeamIntensity(1e7);

    result->setSampleBuilder( builder );

    return result;
}


Simulation *StandardSimulations::LayerWithRoughness()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("LayerWithRoughness");

    Simulation *result = new Simulation();

    result->setDetectorParameters(
        100,-0.5*Units::degree, 0.5*Units::degree, 100,
        0.0*Units::degree, 1.0*Units::degree);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );
    //result->setBeamIntensity(1e+06);

    return result;
}

Simulation *StandardSimulations::Ripple2()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("ripple2");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, -1.5*Units::degree, 1.5*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.6*Units::angstrom, 0.3*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

Simulation *StandardSimulations::Ripple1()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("ripple1");

    Simulation *result = new Simulation();

    result->setDetectorParameters(100, -1.5*Units::degree, 1.5*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.6*Units::angstrom, 0.3*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}
