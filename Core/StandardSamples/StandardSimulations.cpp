// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/StandardSimulations.cpp
//! @brief     Implements functions for standard simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StandardSimulations.h"
#include "SampleBuilderFactory.h"
#include "GISASSimulation.h"
#include "ResolutionFunction2DGaussian.h"
#include "Units.h"
#include "FileSystem.h"
#include "IntensityDataIOFactory.h"
#include "Distributions.h"

GISASSimulation *StandardSimulations::IsGISAXS01()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("CylindersAndPrismsBuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(
        100,-1.0*Units::degree, 1.0*Units::degree, 100,
        0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS02()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("TwoTypesCylindersDistributionBuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree,
                2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::CylindersInBA()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("CylindersInBABuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                         100, 0.0*Units::degree, 2.0*Units::degree,
                                         true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::CylindersInDWBA()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("CylindersInDWBABuilder");

    GISASSimulation *result = new GISASSimulation();


    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                      100, 0.0*Units::degree, 2.0*Units::degree,
                                      true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
             0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::CylindersWithSizeDistribution()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("CylindersWithSizeDistributionBuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                        100, 0.0*Units::degree, 2.0*Units::degree,
                                        true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
               0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS041DDL()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("RadialParaCrystalBuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}


GISASSimulation *StandardSimulations::IsGISAXS042DDL()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("HexParaCrystalBuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS06L1()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("SquareLatticeBuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS06L2()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("CenteredSquareLatticeBuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS06L3()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("RotatedSquareLatticeBuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS06L4()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs06d");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS07()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs07");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 1.0*Units::degree,
                100, 0.0*Units::degree, 1.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.0*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS08a()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs08a");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS08b()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs08b");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS09a()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs09a");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS09b()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("RotatedPyramidsBuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS10()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs10");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS11()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("CoreShellParticleBuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::IsGISAXS15()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("isgisaxs15");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(150, 0.05*Units::degree, 1.5*Units::degree,
            150, 0.05*Units::degree, 1.5*Units::degree, true);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::MesoCrystal01()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("mesocrystal01");

    GISASSimulation *result = new GISASSimulation();
    result->setBeamParameters(1.77*Units::angstrom, 0.4*Units::degree, 0.0*Units::degree);
    result->setBeamIntensity(5.0090e+12);
//    result->setDetectorParameters(100, 0.5*Units::degree, 2.5*Units::degree,
//                                     120, 0.0*Units::degree, 2.5*Units::degree);

    std::string filename = Utils::FileSystem::GetReferenceDataDir() + "mesocrystal01_reference.int.gz";
    OutputData<double> *reference = IntensityDataIOFactory::readIntensityData(filename);
    result->setDetectorParameters(*reference);
    delete reference;

//    result->setDetectorResolutionFunction(
//            new ResolutionFunction2DGaussian(0.0002, 0.0002));

    result->setSampleBuilder( builder );

    return result;
}


GISASSimulation *StandardSimulations::PolarizedDWBAMagCylinders1()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("polmagcylinders1");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}


GISASSimulation *StandardSimulations::PolarizedDWBAMagCylinders2()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("polmagcylinders2");

    GISASSimulation *result = new GISASSimulation();


    result->setDetectorParameters(
        100, -1.0*Units::degree, 1.0*Units::degree, 100,
        0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    result->setBeamIntensity(1e7);

    result->setSampleBuilder( builder );

    return result;
}


GISASSimulation *StandardSimulations::LayerWithRoughness()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("MultiLayerWithRoughnessBuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(
        100,-0.5*Units::degree, 0.5*Units::degree, 100,
        0.0*Units::degree, 1.0*Units::degree);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );
    //result->setBeamIntensity(1e+06);

    return result;
}

GISASSimulation *StandardSimulations::Ripple2()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("ripple2");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, -1.5*Units::degree, 1.5*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.6*Units::angstrom, 0.3*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

GISASSimulation *StandardSimulations::Ripple1()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("ripple1");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, -1.5*Units::degree, 1.5*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.6*Units::angstrom, 0.3*Units::degree, 0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}


// ---

GISASSimulation *StandardSimulations::gui_MultipleLayouts()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("MultipleLayoutBuilder");

    GISASSimulation *result = new GISASSimulation();

    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                100, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);

    result->setSampleBuilder( builder );

    return result;
}

// ------------------------------------------------------------------------------------------------
//
// Toward functional tests refactoring
//
// ------------------------------------------------------------------------------------------------

//! Basic GISAS simulation with the detector phi[0,2], theta[0,2]
GISASSimulation *StandardSimulations::BasicGISAS()
{
    GISASSimulation *result = new GISASSimulation();
    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    return result;
}

//! GISAS simulation with small detector and phi[-2,2], theta[0,2]
GISASSimulation *StandardSimulations::MiniGISAS()
{
    GISASSimulation *result = new GISASSimulation();
    result->setDetectorParameters(25, -2.0*Units::degree, 2.0*Units::degree,
                                     25, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    return result;
}

GISASSimulation *StandardSimulations::MiniGISASBeamDivergence()
{
    GISASSimulation *result = MiniGISAS();

    DistributionLogNormal wavelength_distr(1.0*Units::angstrom, 0.1);
    DistributionGaussian alpha_distr(0.2*Units::degree, 0.1*Units::degree);
    //DistributionGaussian phi_distr(0.0*Units::degree, 0.1*Units::degree);
    DistributionGate phi_distr(-0.1*Units::degree, 0.1*Units::degree);

    result->addParameterDistribution("*/Beam/wavelength", wavelength_distr, 5);
    result->addParameterDistribution("*/Beam/alpha", alpha_distr, 4);
    result->addParameterDistribution("*/Beam/phi", phi_distr, 3);

    return result;
}

GISASSimulation *StandardSimulations::MiniGISASDetectorResolution()
{
    GISASSimulation *result = MiniGISAS();
    ResolutionFunction2DGaussian resfunc(0.0025, 0.0025);
    result->setDetectorResolutionFunction(resfunc);
    return result;
}


//! Typical IsGISAXS simulation with the detector phi[0,2], theta[-1,1]
GISASSimulation *StandardSimulations::IsGISAXSSimulation1()
{
    GISASSimulation *result = new GISASSimulation();
    result->setDetectorParameters(
        100,-1.0*Units::degree, 1.0*Units::degree, 100,
        0.0*Units::degree, 2.0*Units::degree, true);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    return result;
}



