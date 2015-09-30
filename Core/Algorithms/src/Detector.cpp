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

Detector::Detector() : m_axes(), mp_detector_resolution(0)
{
    setName("Detector");
    init_parameters();
    initPolarizationOperator();
}

Detector::Detector(const Detector &other)
    : IParameterized(), m_axes(other.m_axes), mp_detector_resolution(0),
      m_analyzer_operator(other.m_analyzer_operator), m_detector_mask(other.m_detector_mask)
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
    std::swap(this->m_detector_mask, other.m_detector_mask);
}

const IAxis &Detector::getAxis(size_t index) const
{
    if (isCorrectAxisIndex(index)) {
        return *m_axes[index];
    }
    throw OutOfBoundsException("Not so many axes in this detector.");
}

void Detector::applyDetectorResolution(OutputData<double> *p_intensity_map) const
{
    if (!p_intensity_map) {
        throw NullPointerException("Detector::applyDetectorResolution() -> "
                                   "Error! Null pointer to intensity map");
    }
    if (mp_detector_resolution) {
        mp_detector_resolution->applyDetectorResolution(p_intensity_map);
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

void Detector::removeMasks()
{
    m_detector_mask.removeMasks();
}

void Detector::addMask(const Geometry::IShape2D &shape, bool mask_value)
{
    m_detector_mask.addMask(shape, mask_value);
    m_detector_mask.initMaskData(*this);
}

void Detector::maskAll()
{
    if(m_axes.size() != 2) return;

    m_detector_mask.removeMasks();

    Geometry::Rectangle rect(m_axes[0]->getMin(), m_axes[1]->getMin(), m_axes[0]->getMax(), m_axes[1]->getMax());
    addMask(rect, true);
}

const DetectorMask *Detector::getDetectorMask() const
{
    return &m_detector_mask;
}

bool Detector::isMasked(size_t index) const
{
    if(!m_detector_mask.getMaskData()->isInitialized()) return false;
    return m_detector_mask.getMask(index);
}

bool Detector::hasMasks() const
{
    return m_detector_mask.hasMasks();
}

std::vector<SimulationElement> Detector::createSimulationElements(const Beam &beam)
{
    std::vector<SimulationElement> result;
    double wavelength = beam.getWavelength();
    double alpha_i = - beam.getAlpha();  // Defined to be always positive in Beam
    double phi_i = beam.getPhi();
    Eigen::Matrix2cd beam_polarization = beam.getPolarization();
    Eigen::Matrix2cd analyzer_operator = getAnalyzerOperator();

    if (getDimension()!=2) {
        throw RuntimeErrorException("Detector::createSimulationElements: "
                                    "detector is not two-dimensional");
    }
    const IAxis &phi_axis = getAxis(0);
    if (phi_axis.getName()!=BornAgain::PHI_AXIS_NAME) {
        throw RuntimeErrorException("Detector::createSimulationElements: "
                                    "phi-axis is not correct");
    }
    const IAxis &alpha_axis =getAxis(1);
    if (alpha_axis.getName()!=BornAgain::ALPHA_AXIS_NAME) {
        throw RuntimeErrorException("Detector::createSimulationElements: "
                                    "alpha-axis is not correct");
    }

    if (!hasMasks()) m_detector_mask.initMaskData(*this);
    const OutputData<bool>* mask_data = m_detector_mask.getMaskData();
    for (size_t index=0; index<mask_data->getAllocatedSize(); ++index) {
        if ((*mask_data)[index]) continue;
        Bin1D phi_bin = mask_data->getAxisBin(index, BornAgain::X_AXIS_INDEX);
        Bin1D alpha_bin = mask_data->getAxisBin(index, BornAgain::Y_AXIS_INDEX);
        SimulationElement sim_element(wavelength, alpha_i, phi_i, alpha_bin.m_lower,
                                      alpha_bin.m_upper, phi_bin.m_lower, phi_bin.m_upper);
        sim_element.setPolarization(beam_polarization);
        sim_element.setAnalyzerOperator(analyzer_operator);
        result.push_back(sim_element);
    }
    return result;
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

void Detector::normalize(OutputData<double> *p_data, double sin_alpha_i) const
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
    for (OutputData<double>::iterator it = p_data->begin(); it != p_data->end(); ++it) {
        double factor = getSolidAngle(p_data, it.getIndex()) / sin_alpha_i;
        (*it) *= factor;
    }
}

double Detector::getSolidAngle(OutputData<double> *p_data, size_t index) const
{
    const IAxis *p_alpha_axis = p_data->getAxis(BornAgain::ALPHA_AXIS_NAME);
    const IAxis *p_phi_axis = p_data->getAxis(BornAgain::PHI_AXIS_NAME);
//    size_t alpha_index = p_data->getAxisBinIndex(BornAgain::ALPHA_AXIS_NAME, index);
    size_t alpha_index = p_data->getAxisBinIndex(index, BornAgain::ALPHA_AXIS_NAME);
    size_t alpha_size = p_alpha_axis->getSize();
//    size_t phi_index = p_data->getAxisBinIndex(BornAgain::PHI_AXIS_NAME, index);
    size_t phi_index = p_data->getAxisBinIndex(index, BornAgain::PHI_AXIS_NAME);
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

AngularPixelMap::AngularPixelMap(double alpha, double phi, double dalpha, double dphi)
    : m_alpha(alpha), m_phi(phi), m_dalpha(dalpha), m_dphi(dphi)
{
    m_solid_angle = m_dphi*(std::sin(m_alpha+m_dalpha) - std::sin(m_alpha));
}

AngularPixelMap *AngularPixelMap::clone() const
{
    return new AngularPixelMap(m_alpha, m_phi, m_dalpha, m_dphi);
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
    double alpha = m_alpha + x*m_dalpha;
    return std::cos(alpha);
}

