// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/MultiPatternFitTest.h
//! @brief     Defines class MultiPatternFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiPatternFitTest.h"
#include "Units.h"
#include "MultiLayer.h"
#include "Layer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "FormFactorCylinder.h"
#include "InterferenceFunction2DLattice.h"
#include "HomogeneousMaterial.h"
#include "GISASSimulation.h"

namespace {
    const double expected_value = 8.0*Units::nanometer;
}

MultiPatternFitTest::MultiPatternFitTest()
    : IMinimizerTest("GSLLMA")
{

}

void MultiPatternFitTest::initParameterPlan()
{
    m_parplans.clear();

    FitParameter par("*2DLattice/LatticeLength*", 8.5*Units::nanometer);
    par.setLimited(4., 12.).addPattern("*Cylinder/Radius").addPattern("*Cylinder/Height");

    const double tolerance(0.01);
    m_parplans.push_back(new FitParameterPlan(par, expected_value, tolerance));
}

std::unique_ptr<MultiLayer> MultiPatternFitTest::createSample()
{
    std::unique_ptr<MultiLayer> result(new MultiLayer);

    Particle cylinder(HomogeneousMaterial("Particle", 6e-4, 2e-8),
                      FormFactorCylinder(expected_value, expected_value));
    ParticleLayout layout(cylinder);

    std::unique_ptr<InterferenceFunction2DLattice> interference(
                InterferenceFunction2DLattice::createSquare(expected_value));
    interference->setDecayFunction(FTDecayFunction2DCauchy(50.0*Units::nm, 50.0*Units::nm));

    layout.setInterferenceFunction(*interference);

    Layer air_layer(HomogeneousMaterial("Air", 0.0, 0.0));
    air_layer.addLayout(layout);
    Layer substrate_layer(HomogeneousMaterial("Substrate", 6e-6, 2e-8));

    result->addLayer(air_layer);
    result->addLayer(substrate_layer);
    return result;
}

