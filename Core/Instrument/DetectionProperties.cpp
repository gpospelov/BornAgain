// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectionProperties.cpp
//! @brief     Implements class DetectionProperties.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DetectionProperties.h"
#include "Exceptions.h"
#include "Complex.h"

namespace {
// Calculates the vector 2*T*E*d from an analyzer operator, where
//     T: total transmission
//     E: efficiency
//     d: unit vector (if non-zero) of analyzer direction
kvector_t CalculateDifferenceTimesDirection(Eigen::Matrix2cd analyzer_op);
}

DetectionProperties::DetectionProperties()
{
    initPolarizationOperator();
}

void DetectionProperties::setAnalyzerProperties(const kvector_t direction, double efficiency,
                                               double total_transmission)
{
    if (!checkAnalyzerProperties(direction, efficiency, total_transmission))
        throw Exceptions::ClassInitializationException("IDetector2D::setAnalyzerProperties: the "
                                                       "given properties are not physical");

    m_analyzer_operator = calculateAnalyzerOperator(direction, efficiency, total_transmission);
}

Eigen::Matrix2cd DetectionProperties::analyzerOperator() const
{
    return m_analyzer_operator;
}

kvector_t DetectionProperties::analyzerDirection() const
{
    double T = analyzerTotalTransmission();
    auto diffdir = CalculateDifferenceTimesDirection(m_analyzer_operator);
    if (T<=0.0 || diffdir.mag()==0.0)
        return {};
    return diffdir.unit();
}

double DetectionProperties::analyzerEfficiency() const
{
    double T = analyzerTotalTransmission();
    if (T<=0.0)
        return 0.0;
    auto diffdir = CalculateDifferenceTimesDirection(m_analyzer_operator);
    return diffdir.mag()/T/2.0;
}

double DetectionProperties::analyzerTotalTransmission() const
{
    return std::abs(m_analyzer_operator.trace())/2.0;
}

void DetectionProperties::initPolarizationOperator()
{
    m_analyzer_operator = Eigen::Matrix2cd::Identity();
}

bool DetectionProperties::checkAnalyzerProperties(
    const kvector_t direction, double efficiency, double total_transmission) const
{
    if (direction.mag() == 0.0)
        return false;
    double aplus = total_transmission * (1.0 + efficiency);
    double amin = total_transmission * (1.0 - efficiency);
    if (aplus < 0.0 || aplus > 1.0)
        return false;
    if (amin < 0.0 || amin > 1.0)
        return false;
    return true;
}

Eigen::Matrix2cd DetectionProperties::calculateAnalyzerOperator(
    const kvector_t direction, double efficiency, double total_transmission) const
{
    Eigen::Matrix2cd result;
    double x = direction.x()/direction.mag();
    double y = direction.y()/direction.mag();
    double z = direction.z()/direction.mag();
    double sum = total_transmission * 2.0;
    double diff = total_transmission * efficiency * 2.0;
    complex_t im(0.0, 1.0);
    result(0, 0) = (sum + diff*z) / 2.0;
    result(0, 1) = diff*(x - im * y) / 2.0;
    result(1, 0) = diff*(x + im * y) / 2.0;
    result(1, 1) = (sum - diff*z) / 2.0;
    return result;
}

namespace {
kvector_t CalculateDifferenceTimesDirection(Eigen::Matrix2cd analyzer_op)
{
    double x = 2.0*analyzer_op(0, 1).real();
    double y = 2.0*analyzer_op(1, 0).imag();
    double z = (analyzer_op(0, 0) - analyzer_op(1, 1)).real();
    return { x, y, z };
}
}

