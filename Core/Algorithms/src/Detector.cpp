// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/Detector.cpp
//! @brief     Implements class Detector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Detector.h"
#include "MessageService.h"
#include "BornAgainNamespace.h"
#include "FixedBinAxis.h"
#include "ConstKBinAxis.h"
#include "CustomBinAxis.h"
#include "Beam.h"
#include "Rectangle.h"

#include <iostream>
#include <Eigen/LU>
#include <boost/scoped_ptr.hpp>

Detector::Detector()
{
    setName("Detector");
    init_parameters();
}

Detector::Detector(const Detector &other)
    : IDetector2D(other)
{
    init_parameters();
}

Detector &Detector::operator=(const Detector &other)
{
    if (this != &other) {
        Detector tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

Detector *Detector::clone() const
{
    return new Detector(*this);
}

IPixelMap *Detector::createPixelMap(size_t index) const
{
    const IAxis &phi_axis = getAxis(BornAgain::X_AXIS_INDEX);
    const IAxis &alpha_axis = getAxis(BornAgain::Y_AXIS_INDEX);
    size_t phi_index = getAxisBinIndex(index, BornAgain::X_AXIS_INDEX);
    size_t alpha_index = getAxisBinIndex(index, BornAgain::Y_AXIS_INDEX);

    Bin1D alpha_bin = alpha_axis.getBin(alpha_index);
    Bin1D phi_bin = phi_axis.getBin(phi_index);
    return new AngularPixelMap(alpha_bin, phi_bin);
}

std::string Detector::addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                  int copy_number) const
{
    // add own parameters
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the resolution function
    if (mP_detector_resolution) {
        mP_detector_resolution->addParametersToExternalPool(new_path, external_pool, -1);
    }
    return new_path;
}

void Detector::print(std::ostream &ostr) const
{
    ostr << "Detector: '" << getName() << "' " << m_parameters;
    for (size_t i = 0; i < m_axes.size(); ++i) {
        ostr << "    IAxis:" << *m_axes[i] << std::endl;
    }
}

AngularPixelMap::AngularPixelMap(Bin1D alpha_bin, Bin1D phi_bin)
    : m_alpha(alpha_bin.m_lower), m_phi(phi_bin.m_lower),
      m_dalpha(alpha_bin.getBinSize()), m_dphi(phi_bin.getBinSize())
{
    m_solid_angle = std::abs(m_dphi*(std::sin(m_alpha+m_dalpha) - std::sin(m_alpha)));
}

AngularPixelMap *AngularPixelMap::clone() const
{
    Bin1D alpha_bin(m_alpha, m_alpha+m_dalpha);
    Bin1D phi_bin(m_phi, m_phi+m_dphi);
    return new AngularPixelMap(alpha_bin, phi_bin);
}

AngularPixelMap *AngularPixelMap::createZeroSizeMap(double x, double y) const
{
    double alpha = m_alpha + x*m_dalpha;
    double phi = m_phi + y*m_dphi;
    Bin1D alpha_bin(alpha, alpha);
    Bin1D phi_bin(phi, phi);
    return new AngularPixelMap(alpha_bin, phi_bin);
}

kvector_t AngularPixelMap::getK(double x, double y, double wavelength) const
{
    kvector_t result;
    double alpha = m_alpha + x*m_dalpha;
    double phi = m_phi + y*m_dphi;
    result.setLambdaAlphaPhi(wavelength, alpha, phi);
    return result;
}

double AngularPixelMap::getIntegrationFactor(double x, double y) const
{
    (void)y;
    if (m_dalpha==0.0) return 1.0;
    double alpha = m_alpha + x*m_dalpha;
    return std::cos(alpha)*m_dalpha/(std::sin(m_alpha+m_dalpha)-std::sin(m_alpha));
}

double AngularPixelMap::getSolidAngle() const
{
    if (m_solid_angle<=0.0) return 1.0;
    return m_solid_angle;
}

