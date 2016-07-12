// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/SphericalDetector.cpp
//! @brief     Implements class SphericalDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Units.h"
#include "SphericalDetector.h"
#include "MessageService.h"
#include "BornAgainNamespace.h"
#include "FixedBinAxis.h"
#include "ConstKBinAxis.h"
#include "CustomBinAxis.h"
#include "Beam.h"
#include "Rectangle.h"

#include <iostream>

SphericalDetector::SphericalDetector()
{
    setName(BornAgain::SphericalDetectorType);
    init_parameters();
}

SphericalDetector::SphericalDetector(size_t n_phi, double phi_min, double phi_max, size_t n_alpha,
                                     double alpha_min, double alpha_max)
{
    setName(BornAgain::SphericalDetectorType);
    init_parameters();
    setDetectorParameters(n_phi, phi_min, phi_max, n_alpha, alpha_min, alpha_max);
}

SphericalDetector::SphericalDetector(const SphericalDetector &other)
    : IDetector2D(other)
{
    setName(BornAgain::SphericalDetectorType);
    init_parameters();
}

SphericalDetector &SphericalDetector::operator=(const SphericalDetector &other)
{
    if (this != &other) {
        SphericalDetector tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

SphericalDetector *SphericalDetector::clone() const
{
    return new SphericalDetector(*this);
}

std::string SphericalDetector::addParametersToExternalPool(
    std::string path, ParameterPool *external_pool, int copy_number) const
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

OutputData<double> *SphericalDetector::createDetectorMap(const Beam &beam,
                                                         IDetector2D::EAxesUnits units_type) const
{
    if (getDimension() != 2)
        return 0;

    std::unique_ptr<OutputData<double>> result(new OutputData<double>);

    const IAxis &aX = getAxis(BornAgain::X_AXIS_INDEX);
    const IAxis &aY = getAxis(BornAgain::Y_AXIS_INDEX);

    result->addAxis(aX);
    result->addAxis(aY);

    if (units_type == DEFAULT)
        return result.release();

    std::vector<int> indices_left_bottom = {0, 0};
    std::vector<int> indices_right_bottom = {(int)aX.getSize() - 1, 0};
    std::vector<int> indices_center_bottom = {(int)aX.getSize() / 2, 0};
    std::vector<int> indices_center_top = {(int)aX.getSize() / 2, (int)aY.getSize() - 1};
    SimulationElement el_left_bottom
        = getSimulationElement(result->toGlobalIndex(indices_left_bottom), beam);
    SimulationElement el_right_bottom
        = getSimulationElement(result->toGlobalIndex(indices_right_bottom), beam);
    SimulationElement el_center_bottom
        = getSimulationElement(result->toGlobalIndex(indices_center_bottom), beam);
    SimulationElement el_center_top
        = getSimulationElement(result->toGlobalIndex(indices_center_top), beam);

    result->clear();

    double xmin(aX.getMin()), xmax(aX.getMax()), ymin(aY.getMin()), ymax(aY.getMax());

    if (units_type == MM) {
        return 0;
    }

    else if (units_type == NBINS) {
        xmin = 0.0;
        ymin = 0.0;
        xmax = double(aX.getSize());
        ymax = double(aY.getSize());
    }

    else if (units_type == DEGREES) {
        xmin = aX.getMin() / Units::degree;
        xmax = aX.getMax() / Units::degree;
        ymin = aY.getMin() / Units::degree;
        ymax = aY.getMax() / Units::degree;
    }

    else if (units_type == QYQZ) {
        xmin = el_left_bottom.getQ(0.0, 0.0).y();
        xmax = el_right_bottom.getQ(1.0, 0.0).y();
        ymin = -el_center_bottom.getQ(0.5, 0.0).z();
        ymax = -el_center_top.getQ(0.5, 1.0).z();
    }

    result->addAxis(FixedBinAxis(BornAgain::PHI_AXIS_NAME, aX.getSize(), xmin, xmax));
    result->addAxis(FixedBinAxis(BornAgain::ALPHA_AXIS_NAME, aY.getSize(), ymin, ymax));

    return result.release();
}

std::vector<IDetector2D::EAxesUnits> SphericalDetector::getValidAxesUnits() const
{
    std::vector<IDetector2D::EAxesUnits> result = IDetector2D::getValidAxesUnits();
    std::vector<IDetector2D::EAxesUnits> addon =
        { IDetector2D::RADIANS, IDetector2D::DEGREES, IDetector2D::QYQZ };
    result.insert(result.end(), addon.begin(), addon.end());
    return result;
}

IDetector2D::EAxesUnits SphericalDetector::getDefaultAxesUnits() const
{
    return IDetector2D::RADIANS;
}

IPixelMap* SphericalDetector::createPixelMap(size_t index) const
{
    const IAxis &phi_axis = getAxis(BornAgain::X_AXIS_INDEX);
    const IAxis &alpha_axis = getAxis(BornAgain::Y_AXIS_INDEX);
    size_t phi_index = getAxisBinIndex(index, BornAgain::X_AXIS_INDEX);
    size_t alpha_index = getAxisBinIndex(index, BornAgain::Y_AXIS_INDEX);

    Bin1D alpha_bin = alpha_axis.getBin(alpha_index);
    Bin1D phi_bin = phi_axis.getBin(phi_index);
    return new AngularPixelMap(alpha_bin, phi_bin);
}

void SphericalDetector::print(std::ostream &ostr) const
{
    ostr << "SphericalDetector: '" << getName() << "' " << m_parameters;
    for (size_t i = 0; i < m_axes.size(); ++i) {
        ostr << "    IAxis:" << *m_axes[i] << std::endl;
    }
}

IAxis* SphericalDetector::createAxis(size_t index, size_t n_bins, double min, double max) const
{
    if (max <= min) {
        throw Exceptions::LogicErrorException(
            "SphericalDetector::createAxis() -> Error! max <= min");
    }
    if (n_bins == 0) {
        throw Exceptions::LogicErrorException(
            "SphericalDetector::createAxis() -> Error! Number n_bins can't be zero.");
    }    return new FixedBinAxis(getAxisName(index), n_bins, min, max);
}

std::string SphericalDetector::getAxisName(size_t index) const
{
    switch (index) {
    case 0:
        return BornAgain::PHI_AXIS_NAME;
        break;
    case 1:
        return BornAgain::ALPHA_AXIS_NAME;
        break;
    default:
        throw Exceptions::LogicErrorException(
            "SphericalDetector::getAxisName(size_t index) -> Error! index > 1");
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
    double phi = m_phi + x*m_dphi;
    double alpha = m_alpha + y*m_dalpha;
    Bin1D alpha_bin(alpha, alpha);
    Bin1D phi_bin(phi, phi);
    return new AngularPixelMap(alpha_bin, phi_bin);
}

kvector_t AngularPixelMap::getK(double x, double y, double wavelength) const
{
    double phi = m_phi + x*m_dphi;
    double alpha = m_alpha + y*m_dalpha;
    return Geometry::vecOfLambdaAlphaPhi(wavelength, alpha, phi);
}

double AngularPixelMap::getIntegrationFactor(double /* x */, double y) const
{
    if (m_dalpha==0.0) return 1.0;
    double alpha = m_alpha + y*m_dalpha;
    return std::cos(alpha)*m_dalpha/(std::sin(m_alpha+m_dalpha)-std::sin(m_alpha));
}

double AngularPixelMap::getSolidAngle() const
{
    if (m_solid_angle<=0.0) return 1.0;
    return m_solid_angle;
}
