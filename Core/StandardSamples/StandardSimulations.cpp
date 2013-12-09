#include "StandardSimulations.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "ResolutionFunction2DSimple.h"
#include "Units.h"

Simulation *StandardSimulations::IsGISAXS01()
{
    SampleBuilderFactory factory;
    ISampleBuilder *builder = factory.createBuilder("isgisaxs01");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs02");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs03_ba");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs03_dwba");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs03_basize");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs04_1DDL");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs04_2DDL");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs06_lattice1");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs06_lattice2");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs06_lattice3");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs06_lattice4");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs07");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs08a");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs08b");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs09a");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs09b");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs10");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs11");

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
    ISampleBuilder *builder = factory.createBuilder("isgisaxs15");

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
    ISampleBuilder *builder = factory.createBuilder("mesocrystal01");

    Simulation *result = new Simulation();
    result->setBeamParameters(1.77*Units::angstrom, 0.4*Units::degree, 0.0*Units::degree);
    result->setBeamIntensity(5.0090e+12);
//    result->setDetectorResolutionFunction(
//            new ResolutionFunction2DSimple(0.0002, 0.0002));

    result->setSampleBuilder( builder );

    return result;
}


Simulation *StandardSimulations::PolarizedDWBAZeroMag()
{
    SampleBuilderFactory factory;
    ISampleBuilder *builder = factory.createBuilder("PolarizedDWBAZeroMag");

    Simulation *result = new Simulation();

	result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree,
                                     true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}
