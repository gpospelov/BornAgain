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
#include "FitObjective.h"
#include "FormFactorCylinder.h"
#include "GISASSimulation.h"
#include "InterferenceFunction2DLattice.h"
#include "Layer.h"
#include "MaterialFactoryFuncs.h"
#include "MultiLayer.h"
#include "Parameters.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "Rectangle.h"
#include "RectangularDetector.h"
#include "FTDecayFunctions.h"
#include "Units.h"

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
    : FitPlan("CylindersInBAEasyPlan")
{
    setBuilderName("CylindersInBABuilder");
    setSimulationName("MiniGISASFit");
    const double tolerance = 0.1;
    addParameter(Parameter("height", 4.5*nm, AttLimits::limited(4.0, 6.0), 0.1),
                 5.0*nm, tolerance);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::limited(4.0, 6.0), 0.1),
                 5.0*nm, tolerance);
}

CylindersInBAResidualPlan::CylindersInBAResidualPlan()
    : FitPlan("CylindersInBAResidualPlan", /*residual_based*/true)
{
    setBuilderName("CylindersInBABuilder");
    setSimulationName("MiniGISAS");
    addParameter(Parameter("height", 4.5*nm, AttLimits::limitless(), 0.01), 5.0*nm);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::limitless(), 0.01), 5.0*nm);
}

// ----------------------------------------------------------------------------

RectDetPlan::RectDetPlan()
    : FitPlan("RectDetPlan")
{
    setBuilderName("CylindersInBABuilder");
    addParameter(Parameter("height", 4.5*nm, AttLimits::limited(4.0, 6.0), 0.01), 5.0*nm);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::limited(4.0, 6.0), 0.01), 5.0*nm);
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
    result->setRegionOfInterest(5.0, 6.0, 15.0, 12.0);
    result->addMask(Rectangle(0.0, 0.0, 2.0, 2.0), true);
    return std::unique_ptr<Simulation>(result.release());
}

// ----------------------------------------------------------------------------

SpecularPlan::SpecularPlan()
    : SpecularPlan("SpecularPlan")
{}

SpecularPlan::~SpecularPlan() = default;

SpecularPlan::SpecularPlan(std::string name)
    : FitPlan(name, /*residual_based = */ true)
{
    setSimulationName("BasicSpecular");
    addParameter(Parameter("thickness", 5.0 * nm, AttLimits::limited(1.0 * nm, 7.0 * nm), 0.1),
                 3.0 * nm);
}

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

// ----------------------------------------------------------------------------

MultipleSpecPlan::MultipleSpecPlan()
    : SpecularPlan("MultipleSpecPlan")
{}

MultipleSpecPlan::~MultipleSpecPlan() = default;

std::unique_ptr<FitObjective> MultipleSpecPlan::createFitObjective() const
{
    std::unique_ptr<FitObjective> result(new FitObjective);

    simulation_builder_t builder = [&](const Fit::Parameters& params) {
        return buildSimulation(params);
    };

    result->addSimulationAndData(builder, *createOutputData(), 0.5);
    result->addSimulationAndData(builder, *createOutputData(), 0.5);
    result->initPrint(1);

    return result;
}

// ----------------------------------------------------------------------------

OffSpecFitPlan::OffSpecFitPlan()
    : FitPlan("OffSpecFitPlan", /*residual_based*/true)
{
    setBuilderName("ResonatorBuilder");
    setSimulationName("OffSpecMini");
    addParameter(
        Parameter("ti_thickness", 12.0 * nm, AttLimits::limited(11.5 * nm, 14.0 * nm), 0.1 * nm),
        13.0 * nm);
}
