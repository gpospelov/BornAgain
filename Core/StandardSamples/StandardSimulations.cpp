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
#include "IsGISAXSDetector.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "Line.h"
#include "InfinitePlane.h"

GISASSimulation *StandardSimulations::PolarizedDWBAMagCylinders2()
{
    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("MagneticCylindersBuilder");

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

//! Basic GISAS for polarization studies
GISASSimulation *StandardSimulations::BasicGISAS00()
{
    GISASSimulation *result = BasicGISAS();
    kvector_t zplus(0.0, 0.0, 1.0);
    result->setBeamPolarization(zplus);
    result->setAnalyzerProperties(zplus, 1.0, 0.5);
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

GISASSimulation *StandardSimulations::MiniGISASWithMasks()
{
    GISASSimulation *result = new GISASSimulation();
    result->setDetectorParameters(100, -1.0*Units::degree, 1.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    result->setBeamIntensity(1e-06);
//    result->maskAll();
//    result->addMask(Geometry::Ellipse(0.0*Units::deg, 1.0*Units::deg,
//                                      0.5*Units::deg, 0.5*Units::deg), true);

//    std::vector<double> x = {Units::deg2rad(0.5), Units::deg2rad(-0.5), Units::deg2rad(0.5), Units::deg2rad(-0.5), Units::deg2rad(0.5)};
//    std::vector<double> y = {Units::deg2rad(1.8), Units::deg2rad(1.8), Units::deg2rad(0.1), Units::deg2rad(0.1), Units::deg2rad(1.8)};
//    result->addMask(Geometry::Polygon(x, y), true);

//    result->addMask(Geometry::InfinitePlane(), true);
//    result->addMask(Geometry::Rectangle(Units::deg2rad(0.0), Units::deg2rad(0.0), Units::deg2rad(1.0), Units::deg2rad(0.5)), false);
//    result->addMask(Geometry::VerticalLine(Units::deg2rad(-0.25)), false);


    result->maskAll();
    // pacman
    const double deg = Units::degree;
    result->addMask(Geometry::Ellipse(0.0*deg, 1.0*deg, 0.5*deg, 0.5*deg), false);
    result->addMask(Geometry::Ellipse(0.11*deg, 1.25*deg, 0.05*deg, 0.05*deg), true);

    std::vector<std::vector<double> >  points = {{0.0*deg, 1.0*deg}, {0.5*deg, 1.2*deg}, {0.5*deg, 0.8*deg}, {0.0*deg, 1.0*deg}};
    result->addMask(Geometry::Polygon(points), true);

    result->addMask(Geometry::Rectangle(0.45*deg, 0.95*deg, 0.55*deg, 1.05*deg), false);
    result->addMask(Geometry::Rectangle(0.61*deg, 0.95*deg, 0.71*deg, 1.05*deg), false);
    result->addMask(Geometry::Rectangle(0.75*deg, 0.95*deg, 0.85*deg, 1.05*deg), false);

    // more stuff
    result->addMask(Geometry::Ellipse(-0.5*deg, 1.5*deg, 0.3*deg, 0.1*deg, 45.*deg), false);


    return result;
}


GISASSimulation *StandardSimulations::MiniGISASDetectorResolution()
{
    GISASSimulation *result = MiniGISAS();
    ResolutionFunction2DGaussian resfunc(0.0025, 0.0025);
    result->setDetectorResolutionFunction(resfunc);
    return result;
}

//! GISAS simulation with large detector to test performance
GISASSimulation *StandardSimulations::MaxiGISAS()
{
    GISASSimulation *result = new GISASSimulation();
    result->setDetectorParameters(256, -2.0*Units::degree, 2.0*Units::degree,
                                     256, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    return result;
}

//! Basic GISAS for polarization studies
GISASSimulation *StandardSimulations::MaxiGISAS00()
{
    GISASSimulation *result = MaxiGISAS();
    kvector_t zplus(0.0, 0.0, 1.0);
    result->setBeamPolarization(zplus);
    result->setAnalyzerProperties(zplus, 1.0, 0.5);
    return result;
}


//! Typical IsGISAXS simulation with the detector phi[-1,1], theta[0,2]
GISASSimulation *StandardSimulations::IsGISAXSSimulation1()
{
    GISASSimulation *result = new GISASSimulation();
    IsGISAXSDetector detector;
    detector.setDetectorParameters(100,-1.0*Units::degree, 1.0*Units::degree,
                                   100, 0.0*Units::degree, 2.0*Units::degree);
    result->setDetector(detector);
    result->setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    return result;
}


//! Typical IsGISAXS simulation with the detector phi[0,2], theta[0,2]
GISASSimulation *StandardSimulations::IsGISAXSSimulation2()
{
    GISASSimulation *result = new GISASSimulation();
    IsGISAXSDetector detector;
    detector.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                   100, 0.0*Units::degree, 2.0*Units::degree);
    result->setDetector(detector);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
                0.0*Units::degree);
    return result;
}

