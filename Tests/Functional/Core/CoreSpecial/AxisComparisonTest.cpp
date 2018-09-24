// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/AxisComparisonTest.cpp
//! @brief     Implements class AxisComparisonTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "AxisComparisonTest.h"
#include "Distributions.h"
#include "FixedBinAxis.h"
#include "FootprintFactorSquare.h"
#include "MultiLayer.h"
#include "ParameterPattern.h"
#include "PointwiseAxis.h"
#include "SampleBuilderFactory.h"
#include "SpecularSimulation.h"
#include "Units.h"

namespace  {
const double error_tolerance = 1e-10;
double relative_difference(double ref, double value)
{
    return std::abs(2.0 * (ref - value) / (ref + value));
}
}

AxisComparisonTest::AxisComparisonTest() = default;
AxisComparisonTest::~AxisComparisonTest() = default;

std::unique_ptr<Simulation> AxisComparisonTest::createSimulation(const IAxis& axis)
{
const double wavelength = 1.54 * Units::angstrom;
const size_t n_integration_points = 5;
const auto square_ff = std::make_unique<FootprintFactorSquare>(0.1);
const DistributionGaussian alpha_distr(0.0, 0.1*Units::degree);

std::unique_ptr<SpecularSimulation> result(new SpecularSimulation());
result->setBeamParameters(wavelength, axis, square_ff.get());

ParameterPattern pattern;
pattern.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Inclination);
result->addParameterDistribution(pattern.toStdString(), alpha_distr, n_integration_points);

std::unique_ptr<MultiLayer> sample(
    SampleBuilderFactory().createSample("PlainMultiLayerBySLDBuilder"));
result->setSample(*sample);

result->runSimulation();

return result;
}

bool AxisComparisonTest::runTest()
{
    // creating reference simulation
    FixedBinAxis axis("reference", 10, 0.0, 10.0 * Units::degree);
    auto reference = createSimulation(axis);

    // simulation with poinwise axis
    const std::vector<size_t> mask {0u, 2u, 3u, 4u, 7u, 8u, 9u};
    std::vector<double> coordinates;
    for (auto index: mask)
        coordinates.push_back(axis.getBinCenter(index));
    PointwiseAxis pointwise_axis("pointwise", coordinates);
    auto pointwise_simulation = createSimulation(pointwise_axis);

    // comparing simulations
    auto ref_result = reference->result();
    auto pointwise_result = pointwise_simulation->result();
    for (size_t i = 0; i < mask.size(); ++i) {
        double rel_error = relative_difference(ref_result[mask[i]], pointwise_result[i]);
        if (std::abs(rel_error) > error_tolerance) {
            std::cout << "AxisComparisonTest: " << "Relative error " << rel_error <<
                         " Exceeds error tolerance " << error_tolerance << std::endl;
            return false;
        }
    }
    return true;
}
