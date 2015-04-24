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

#include <iostream>
#include <Eigen/LU>

Detector::Detector() : m_axes(), mp_detector_resolution(0)
{
    setName("Detector");
    init_parameters();
    initPolarizationOperator();
}

Detector::Detector(const Detector &other)
    : IParameterized(), m_axes(other.m_axes), mp_detector_resolution(0),
      m_analyzer_operator(other.m_analyzer_operator)
{
    setName(other.getName());
    if (other.mp_detector_resolution)
        mp_detector_resolution = other.mp_detector_resolution->clone();
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

void Detector::swapContent(Detector &other)
{
    std::swap(this->m_axes, other.m_axes);
    std::swap(this->mp_detector_resolution, other.mp_detector_resolution);
    std::swap(this->m_analyzer_operator, other.m_analyzer_operator);
}

void Detector::addAxis(const AxisParameters &axis_params)
{
    IAxis *p_new_axis(0);
    switch (axis_params.m_sample_method) {
    case AxisParameters::E_DEFAULT: {

        p_new_axis = new ConstKBinAxis(axis_params.m_name, axis_params.m_range.getNSamples(),
                                       axis_params.m_range.getLowerBound(),
                                       axis_params.m_range.getUpperBound());

        break;
    }
    case AxisParameters::E_ISGISAXS: {
        p_new_axis = new CustomBinAxis(axis_params.m_name, axis_params.m_range.getNSamples(),
                                       axis_params.m_range.getLowerBound(),
                                       axis_params.m_range.getUpperBound());

        break;
    }
    default:
        throw RuntimeErrorException("Invalid sample method for axis.");
    }
    if (p_new_axis)
        m_axes.push_back(p_new_axis);
}

const IAxis &Detector::getAxis(size_t index) const
{
    if (isCorrectAxisIndex(index)) {
        return *m_axes[index];
    }
    throw OutOfBoundsException("Not so many axes in this detector.");
}

void Detector::applyDetectorResolution(OutputData<double> *p_intensity_map,
                                       OutputData<Eigen::Matrix2d> *p_matrix_intensity) const
{
    if (!p_intensity_map) {
        throw NullPointerException("Detector::applyDetectorResolution() -> "
                                   "Error! Null pointer to intensity map");
    }
    if (mp_detector_resolution) {
        mp_detector_resolution->applyDetectorResolution(p_intensity_map);
        if (p_matrix_intensity) {
            mp_detector_resolution->applyDetectorResolutionPol(p_matrix_intensity);
        }
    } else {
        msglog(MSG::WARNING) << "Detector::applyDetectorResolution() -> "
                                "No detector resolution function found";
    }
}

void Detector::setAnalyzerProperties(const kvector_t &direction, double efficiency,
                                     double total_transmission)
{
    if (!checkAnalyzerProperties(direction, efficiency, total_transmission)) {
        throw Exceptions::ClassInitializationException(
            "Detector::setAnalyzerProperties: the given properties are not physical");
    }
    m_analyzer_operator = calculateAnalyzerOperator(direction, efficiency, total_transmission);
}

bool Detector::dataShapeMatches(const OutputData<double> *p_data) const
{
    if (p_data->getRank() != getDimension())
        return false;
    for (size_t i = 0; i < getDimension(); ++i) {
        const IAxis *p_data_axis = p_data->getAxis(i);
        const IAxis &detector_axis = getAxis(i);
        if (detector_axis != *p_data_axis)
            return false;
    }
    return true;
}

std::string Detector::addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                  int copy_number) const
{
    // add own parameters
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the resolution function
    if (mp_detector_resolution) {
        mp_detector_resolution->addParametersToExternalPool(new_path, external_pool, -1);
    }
    return new_path;
}

void Detector::normalize(OutputData<double> *p_data, OutputData<Eigen::Matrix2d> *p_polarized_data,
                         double sin_alpha_i) const
{
    // if shapes do not match, do nothing
    if (!dataShapeMatches(p_data))
        return;

    // if not a 2d detector, do nothing
    if (p_data->getRank() != 2)
        return;

    // if not a gisas detector, do nothing
    const IAxis *p_alpha_axis = p_data->getAxis(BornAgain::ALPHA_AXIS_NAME);
    const IAxis *p_phi_axis = p_data->getAxis(BornAgain::PHI_AXIS_NAME);
    if (!p_alpha_axis || !p_phi_axis)
        return;

    // GISAS normalization
    // This normalization assumes that the intensity map contains
    // total differential scattering cross sections
    // (as opposed to the usual cross section per scattering particle)
    OutputData<Eigen::Matrix2d>::iterator it_pol;
    if (p_polarized_data) {
        it_pol = p_polarized_data->begin();
    }
    for (OutputData<double>::iterator it = p_data->begin(); it != p_data->end(); ++it) {
        double factor = getSolidAngle(p_data, it.getIndex()) / sin_alpha_i;
        (*it) *= factor;
        if (p_polarized_data) {
            (*it_pol) *= factor;
            ++it_pol;
        }
    }
}

double Detector::getSolidAngle(OutputData<double> *p_data, size_t index) const
{
    const IAxis *p_alpha_axis = p_data->getAxis(BornAgain::ALPHA_AXIS_NAME);
    const IAxis *p_phi_axis = p_data->getAxis(BornAgain::PHI_AXIS_NAME);
    size_t alpha_index = p_data->getIndexOfAxis(BornAgain::ALPHA_AXIS_NAME, index);
    size_t alpha_size = p_alpha_axis->getSize();
    size_t phi_index = p_data->getIndexOfAxis(BornAgain::PHI_AXIS_NAME, index);
    size_t phi_size = p_phi_axis->getSize();
    if (alpha_size < 2 && phi_size < 2)
        // Cannot determine detector cell size!
        throw LogicErrorException("Simulation::getSolidAngle() -> "
                                  "Error! Can't determine size of detector cell.");
    double dsinalpha(1.0), dphi(1.0);
    Bin1D alpha_bin = p_alpha_axis->getBin(alpha_index);
    if (alpha_bin.getBinSize()) {
        dsinalpha = std::abs(std::sin(alpha_bin.m_upper) - std::sin(alpha_bin.m_lower));
    }
    Bin1D phi_bin = p_phi_axis->getBin(phi_index);
    if (phi_bin.getBinSize()) {
        dphi = std::abs(phi_bin.m_upper - phi_bin.m_lower);
    }
    return dsinalpha * dphi;
}

void Detector::initPolarizationOperator()
{
    m_analyzer_operator = Eigen::Matrix2cd::Identity();
}

bool Detector::checkAnalyzerProperties(const kvector_t &direction, double efficiency,
                                       double total_transmission) const
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

Eigen::Matrix2cd Detector::calculateAnalyzerOperator(const kvector_t &direction, double efficiency,
                                                     double total_transmission) const
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

void Detector::print(std::ostream &ostr) const
{
    ostr << "Detector: '" << getName() << "' " << m_parameters;
    for (size_t i = 0; i < m_axes.size(); ++i) {
        ostr << "    IAxis:" << *m_axes[i] << std::endl;
    }
}
