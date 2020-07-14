// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SphericalDetector.cpp
//! @brief     Implements class SphericalDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Instrument/SphericalDetector.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Beam/Beam.h"
#include "Core/Binning/IPixel.h"
#include "Core/Instrument/IDetectorResolution.h"
#include "Core/Parametrization/Units.h"
#include "Core/SimulationElement/SimulationElement.h"

SphericalDetector::SphericalDetector()
{
    setName("SphericalDetector");
}

SphericalDetector::SphericalDetector(size_t n_phi, double phi_min, double phi_max, size_t n_alpha,
                                     double alpha_min, double alpha_max)
{
    setName("SphericalDetector");
    setDetectorParameters(n_phi, phi_min, phi_max, n_alpha, alpha_min, alpha_max);
}

SphericalDetector::SphericalDetector(const SphericalDetector& other) : IDetector2D(other)
{
    setName("SphericalDetector");
}

SphericalDetector* SphericalDetector::clone() const
{
    return new SphericalDetector(*this);
}

AxesUnits SphericalDetector::defaultAxesUnits() const
{
    return AxesUnits::RADIANS;
}

IPixel* SphericalDetector::createPixel(size_t index) const
{
    const IAxis& phi_axis = getAxis(0);
    const IAxis& alpha_axis = getAxis(1);
    const size_t phi_index = axisBinIndex(index, 0);
    const size_t alpha_index = axisBinIndex(index, 1);

    const Bin1D alpha_bin = alpha_axis.getBin(alpha_index);
    const Bin1D phi_bin = phi_axis.getBin(phi_index);
    return new SphericalPixel(alpha_bin, phi_bin);
}

std::string SphericalDetector::axisName(size_t index) const
{
    switch (index) {
    case 0:
        return "phi_f";
    case 1:
        return "alpha_f";
    default:
        throw Exceptions::LogicErrorException(
            "SphericalDetector::getAxisName(size_t index) -> Error! index > 1");
    }
}

size_t SphericalDetector::getIndexOfSpecular(const Beam& beam) const
{
    if (dimension() != 2)
        return totalSize();
    double alpha = beam.getAlpha();
    double phi = beam.getPhi();
    const IAxis& phi_axis = getAxis(0);
    const IAxis& alpha_axis = getAxis(1);
    if (phi_axis.contains(phi) && alpha_axis.contains(alpha))
        return getGlobalIndex(phi_axis.findClosestIndex(phi), alpha_axis.findClosestIndex(alpha));
    return totalSize();
}

SphericalPixel::SphericalPixel(const Bin1D& alpha_bin, const Bin1D& phi_bin)
    : m_alpha(alpha_bin.m_lower), m_phi(phi_bin.m_lower), m_dalpha(alpha_bin.getBinSize()),
      m_dphi(phi_bin.getBinSize())
{
    auto solid_angle_value = std::abs(m_dphi * (std::sin(m_alpha + m_dalpha) - std::sin(m_alpha)));
    m_solid_angle = solid_angle_value <= 0.0 ? 1.0 : solid_angle_value;
}

SphericalPixel* SphericalPixel::clone() const
{
    return new SphericalPixel(*this);
}

SphericalPixel* SphericalPixel::createZeroSizePixel(double x, double y) const
{
    double phi = m_phi + x * m_dphi;
    double alpha = m_alpha + y * m_dalpha;
    Bin1D alpha_bin(alpha, alpha);
    Bin1D phi_bin(phi, phi);
    return new SphericalPixel(alpha_bin, phi_bin);
}

kvector_t SphericalPixel::getK(double x, double y, double wavelength) const
{
    double phi = m_phi + x * m_dphi;
    double alpha = m_alpha + y * m_dalpha;
    return vecOfLambdaAlphaPhi(wavelength, alpha, phi);
}

double SphericalPixel::getIntegrationFactor(double /* x */, double y) const
{
    if (m_dalpha == 0.0)
        return 1.0;
    double alpha = m_alpha + y * m_dalpha;
    return std::cos(alpha) * m_dalpha / (std::sin(m_alpha + m_dalpha) - std::sin(m_alpha));
}

double SphericalPixel::getSolidAngle() const
{
    return m_solid_angle;
}
