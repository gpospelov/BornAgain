// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitPlanCases.h
//! @brief     Implements collection of FitPlanCases classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitPlanCases.h"
#include "Units.h"
#include "GISASSimulation.h"
#include "RectangularDetector.h"
#include "Rectangle.h"
#include "MultiLayer.h"
#include "MaterialFactoryFuncs.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "Parameters.h"
#include "InterferenceFunction2DLattice.h"
#include "FTDecayFunctions.h"
#include "Layer.h"
#include "FormFactorCylinder.h"

using namespace Fit;

namespace {
    const double nm = Units::nanometer;
}

CylindersInBAPlan::CylindersInBAPlan()
    : FitPlan("CylindersInBAPlan")
{
    setBuilderName("CylindersInBABuilder");
    setSimulationName("MiniGISAS");
    addParameter(Parameter("height", 4.5*nm, AttLimits::lowerLimited(0.01), 0.01), 5.0*nm);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::lowerLimited(0.01), 0.01), 5.0*nm);
}

CylindersInBAEasyPlan::CylindersInBAEasyPlan()
    : FitPlan("CylindersInBAPlan")
{
    setBuilderName("CylindersInBABuilder");
    setSimulationName("MiniGISAS");
    const double tolerance = 0.1;
    addParameter(Parameter("height", 4.5*nm, AttLimits::limited(4.0, 6.0), 0.01),
                 5.0*nm, tolerance);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::limited(4.0, 6.0), 0.01),
                 5.0*nm, tolerance);
}

CylindersInBAResidualPlan::CylindersInBAResidualPlan()
    : FitPlan("CylindersInBAResidualPlan", /*residual_based*/true)
{
    setBuilderName("CylindersInBABuilder");
    setSimulationName("MiniGISAS");
    addParameter(Parameter("height", 4.5*nm, AttLimits::lowerLimited(0.01), 0.01), 5.0*nm);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::lowerLimited(0.01), 0.01), 5.0*nm);
}

// ----------------------------------------------------------------------------

RectDetPlan::RectDetPlan()
    : FitPlan("RectDetPlan")
{
    setBuilderName("CylindersInBABuilder");
    addParameter(Parameter("height", 4.5*nm, AttLimits::lowerLimited(0.01), 0.01), 5.0*nm);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::lowerLimited(0.01), 0.01), 5.0*nm);
}

RectDetPlan::~RectDetPlan() = default;

std::unique_ptr<Simulation> RectDetPlan::createSimulation(const Parameters&) const
{
    std::unique_ptr<GISASSimulation> result(new GISASSimulation());

    double detector_distance(500.0);
    double width(20.0), height(18.0);
    RectangularDetector detector(20u, width, 18u, height);
    detector.setPerpendicularToSampleX(detector_distance, width/2., 0.0);

    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    result->setDetector(detector);
    result->setRegionOfInterest(6.0, 6.0, 14.0, 12.0);
    result->addMask(Rectangle(8.0, 8.0, 10.0, 10.0), true);
    return std::unique_ptr<Simulation>(result.release());
}

// ----------------------------------------------------------------------------

MultiPatternPlan::MultiPatternPlan()
    : FitPlan("MultiPatternPlan", true)
{
    setSimulationName("MiniGISAS");
    addParameter(Parameter("length", 8.5*nm, AttLimits::limited(4.0, 12.0), 0.01), 8.0*nm);
}

MultiPatternPlan::~MultiPatternPlan() = default;

std::unique_ptr<MultiLayer> MultiPatternPlan::createMultiLayer(const Parameters& params) const
{
    double custom_length = params["length"].value();

    std::unique_ptr<MultiLayer> result(new MultiLayer);

    Particle cylinder(HomogeneousMaterial("Particle", 6e-4, 2e-8),
                      FormFactorCylinder(custom_length, custom_length));
    ParticleLayout layout(cylinder);

    std::unique_ptr<InterferenceFunction2DLattice> interference(
                InterferenceFunction2DLattice::createSquare(custom_length));
    interference->setDecayFunction(FTDecayFunction2DCauchy(50.0*Units::nm, 50.0*Units::nm));

    layout.setInterferenceFunction(*interference);

    Layer air_layer(HomogeneousMaterial("Air", 0.0, 0.0));
    air_layer.addLayout(layout);
    Layer substrate_layer(HomogeneousMaterial("Substrate", 6e-6, 2e-8));

    result->addLayer(air_layer);
    result->addLayer(substrate_layer);
    return result;
}

// ----------------------------------------------------------------------------

SpecularPlan::SpecularPlan()
    : FitPlan("SpecularPlan", /*residual_based = */ true)
{
    setSimulationName("BasicSpecular");
    addParameter(Parameter("thickness", 5.0 * nm, AttLimits::limited(1.0 * nm, 7.0 * nm), 0.1),
                 3.0 * nm);
}

SpecularPlan::~SpecularPlan() = default;

std::unique_ptr<MultiLayer> SpecularPlan::createMultiLayer(const Fit::Parameters& params) const
{
    const size_t number_of_layers = 10;
    double thick_ni = 7.0 * nm;
    double thick_ti = params["thickness"].value();

    Material vacuum_material = MaterialBySLD();
    Material substrate_material = MaterialBySLD("Si_substrate", 2.0704e-06, 2.3726e-11);
    Material ni_material = MaterialBySLD("Ni", -1.9493e-06, 9.6013e-10);
    Material ti_material = MaterialBySLD("Ti", 9.4245e-06, 1.1423e-09);

    Layer vacuum_layer(vacuum_material, 0);
    Layer ni_layer(ni_material, thick_ni);
    Layer ti_layer(ti_material, thick_ti);
    Layer substrate_layer(substrate_material, 0);

    std::unique_ptr<MultiLayer> multi_layer(new MultiLayer());
    multi_layer->addLayer(vacuum_layer);
    for (size_t i = 0; i < number_of_layers; ++i) {
        multi_layer->addLayer(ti_layer);
        multi_layer->addLayer(ni_layer);
    }
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
