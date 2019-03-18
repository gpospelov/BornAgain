// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/QSpecScan.cpp
//! @brief     Implements QSpecScan class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "QSpecScan.h"
#include "BornAgainNamespace.h"
#include "FixedBinAxis.h"
#include "PointwiseAxis.h"
#include "PythonFormatting.h"
#include "RealLimits.h"
#include "SpecularSimulationElement.h"

namespace {
const RealLimits qz_limits = RealLimits::nonnegative();
}

QSpecScan::QSpecScan(std::vector<double> qs_nm)
    : ISpecularScan(SPECULAR_DATA_TYPE::q)
    , m_qs(std::make_unique<PointwiseAxis>("qs", std::move(qs_nm)))
{
    checkInitialization();
}

QSpecScan::QSpecScan(const IAxis& qs_nm)
    : ISpecularScan(SPECULAR_DATA_TYPE::q)
    , m_qs(qs_nm.clone())
{
    checkInitialization();
}

QSpecScan::QSpecScan(int nbins, double qz_min, double qz_max)
    : ISpecularScan(SPECULAR_DATA_TYPE::q)
    , m_qs(std::make_unique<FixedBinAxis>("qs", nbins, qz_min, qz_max))
{
    checkInitialization();
}

QSpecScan::~QSpecScan() = default;

QSpecScan* QSpecScan::clone() const
{
    return new QSpecScan(*m_qs);
}

//! Generates simulation elements for specular simulations
std::vector<SpecularSimulationElement> QSpecScan::generateSimulationElements() const
{
    std::vector<SpecularSimulationElement> result;

    const size_t axis_size = m_qs->size();
    std::vector<double> qs = m_qs->getBinCenters();
    result.reserve(axis_size);
    for (size_t i = 0; i < axis_size; ++i) {
        const double kz = qs[i] / 2.0;
        result.emplace_back(kz);
        if (!qz_limits.isInRange(kz))
            result.back().setCalculationFlag(false); // false = exclude from calculations
    }

    return result;
}

double QSpecScan::footprint(size_t i) const
{
    if (i >= numberOfSimulationElements())
        throw std::runtime_error("Error in QSpecScan::footprint: given index exceeds the "
                                 "number of simulation elements");
    return 1.0;
}

//! Returns the number of simulation elements
size_t QSpecScan::numberOfSimulationElements() const
{
    return m_qs->size();
}

std::string QSpecScan::print() const
{
    std::stringstream result;
    const std::string axis_def = PythonFormatting::indent() + "axis = ";
    result << axis_def
           << PythonFormatting::printAxis(*coordinateAxis(), BornAgain::UnitsNone,
                                          axis_def.size())
           << "\n";

    result << PythonFormatting::indent() << "scan = ba.QSpecScan(axis)";
    return result.str();
}

void QSpecScan::checkInitialization()
{
    std::vector<double> axis_values = m_qs->getBinCenters();
    if (!std::is_sorted(axis_values.begin(), axis_values.end()))
        throw std::runtime_error("Error in QSpecScan::checkInitialization: q-vector values shall "
                                 "be sorted in ascending order.");

    if (!qz_limits.isInRange(axis_values.front()))
        throw std::runtime_error("Error in QSpecScan::checkInitialization: q-vector values are out "
                                 "of acceptable range.");
}
