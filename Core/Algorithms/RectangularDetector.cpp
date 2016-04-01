// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/RectangularDetector.cpp
//! @brief     Implements class RectangularDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Units.h"
#include "RectangularDetector.h"
#include "MessageService.h"
#include "BornAgainNamespace.h"
#include "FixedBinAxis.h"
#include "ConstKBinAxis.h"
#include "CustomBinAxis.h"
#include "Beam.h"
#include "Rectangle.h"
#include "GISASSimulation.h"
#include "Instrument.h"
#include "Beam.h"

#include <iostream>

RectangularDetector::RectangularDetector(int nxbins, double width, int nybins, double height)
    : m_u0(0.0)
    , m_v0(0.0)
    , m_direction(kvector_t(0.0, -1.0, 0.0))
    , m_distance(0.0)
    , m_dbeam_u0(0.0)
    , m_dbeam_v0(0.0)
    , m_detector_arrangement(GENERIC)
{
    setDetectorParameters(nxbins, 0.0, width, nybins, 0.0, height);
    setName(BornAgain::RectangularDetectorType);
    init_parameters();
}

RectangularDetector::RectangularDetector(const RectangularDetector &other)
    : IDetector2D(other)
    , m_normal_to_detector(other.m_normal_to_detector)
    , m_u0(other.m_u0)
    , m_v0(other.m_v0)
    , m_direction(other.m_direction)
    , m_distance(other.m_distance)
    , m_dbeam_u0(other.m_dbeam_u0)
    , m_dbeam_v0(other.m_dbeam_v0)
    , m_detector_arrangement(other.m_detector_arrangement)
    , m_u_unit(other.m_u_unit)
    , m_v_unit(other.m_v_unit)
{
    setName(BornAgain::RectangularDetectorType);
    init_parameters();
}

RectangularDetector &RectangularDetector::operator=(const RectangularDetector &other)
{
    if (this != &other) {
        RectangularDetector tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

RectangularDetector *RectangularDetector::clone() const
{
    return new RectangularDetector(*this);
}

void RectangularDetector::init(const Beam &beam)
{
    double alpha_i = beam.getAlpha();
    kvector_t central_k = beam.getCentralK();
    initNormalVector(central_k);
    initUandV(alpha_i);
}

void RectangularDetector::setPosition(const kvector_t &normal_to_detector,
                                      double u0, double v0, const kvector_t &direction)
{
    m_detector_arrangement = GENERIC;
    m_normal_to_detector = normal_to_detector;
    m_u0 = u0;
    m_v0 = v0;
    m_direction = direction;
}

void RectangularDetector::setPerpendicularToSampleX(double distance, double u0, double v0)
{
    m_detector_arrangement = PERPENDICULAR_TO_SAMPLE;
    setDistanceAndOffset(distance, u0, v0);
}

void RectangularDetector::setPerpendicularToDirectBeam(double distance, double u0, double v0)
{
    m_detector_arrangement = PERPENDICULAR_TO_DIRECT_BEAM;
    setDistanceAndOffset(distance, u0, v0);
}

void RectangularDetector::setPerpendicularToReflectedBeam(double distance, double u0, double v0)
{
    m_detector_arrangement = PERPENDICULAR_TO_REFLECTED_BEAM;
    setDistanceAndOffset(distance, u0, v0);
}

void RectangularDetector::setDirectBeamPosition(double u0, double v0)
{
    m_detector_arrangement = PERPENDICULAR_TO_REFLECTED_BEAM_DPOS;
    m_dbeam_u0 = u0;
    m_dbeam_v0 = v0;
}

IPixelMap *RectangularDetector::createPixelMap(size_t index) const
{
    const IAxis &u_axis = getAxis(BornAgain::X_AXIS_INDEX);
    const IAxis &v_axis = getAxis(BornAgain::Y_AXIS_INDEX);
    size_t u_index = getAxisBinIndex(index, BornAgain::X_AXIS_INDEX);
    size_t v_index = getAxisBinIndex(index, BornAgain::Y_AXIS_INDEX);

    Bin1D u_bin = u_axis.getBin(u_index);
    Bin1D v_bin = v_axis.getBin(v_index);
    kvector_t corner_position( m_normal_to_detector
            + (u_bin.m_lower - m_u0)*m_u_unit + (v_bin.m_lower - m_v0)*m_v_unit );
    kvector_t width = u_bin.getBinSize()*m_u_unit;
    kvector_t height = v_bin.getBinSize()*m_v_unit;
    return new RectPixelMap(corner_position, width, height);
}

std::string RectangularDetector::addParametersToExternalPool(
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

double RectangularDetector::getWidth() const
{
    const IAxis &axis = getAxis(BornAgain::X_AXIS_INDEX);
    return axis.getMax() - axis.getMin();
}

double RectangularDetector::getHeight() const
{
    const IAxis &axis = getAxis(BornAgain::Y_AXIS_INDEX);
    return axis.getMax() - axis.getMin();
}

size_t RectangularDetector::getNbinsX() const
{
    return getAxis(BornAgain::X_AXIS_INDEX).getSize();
}

size_t RectangularDetector::getNbinsY() const
{
    return getAxis(BornAgain::Y_AXIS_INDEX).getSize();
}

kvector_t RectangularDetector::getNormalVector() const
{
    return m_normal_to_detector;
}

double RectangularDetector::getU0() const
{
    return m_u0;
}

double RectangularDetector::getV0() const
{
    return m_v0;
}

kvector_t RectangularDetector::getDirectionVector() const
{
    return m_direction;
}

double RectangularDetector::getDistance() const
{
    return m_distance;
}

double RectangularDetector::getDirectBeamU0() const
{
    return m_dbeam_u0;
}

double RectangularDetector::getDirectBeamV0() const
{
    return m_dbeam_v0;
}

RectangularDetector::EDetectorArrangement RectangularDetector::getDetectorArrangment() const
{
    return m_detector_arrangement;
}

OutputData<double> *RectangularDetector::createDetectorMap(const Beam &beam,
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

    if (units_type == NBINS) {
        xmin = 0.0;
        ymin = 0.0;
        xmax = double(aX.getSize());
        ymax = double(aY.getSize());
    }

    else if (units_type == RADIANS || units_type == DEGREES) {
        double scale(1.0);
        if (units_type == DEGREES)
            scale = 1. / Units::degree;
        xmin = scale * el_left_bottom.getPhi(0.0, 0.0);
        xmax = scale * el_right_bottom.getPhi(1.0, 0.0);
        ymin = scale * el_center_bottom.getAlpha(0.5, 0.0);
        ymax = scale * el_center_top.getAlpha(0.5, 1.0);
    }

    else if (units_type == QYQZ) {
        xmin = el_left_bottom.getQ(0.0, 0.0).y();
        xmax = el_right_bottom.getQ(1.0, 0.0).y();
        ymin = -el_center_bottom.getQ(0.5, 0.0).z();
        ymax = -el_center_top.getQ(0.5, 1.0).z();
    }

    result->addAxis(FixedBinAxis(BornAgain::U_AXIS_NAME, aX.getSize(), xmin, xmax));
    result->addAxis(FixedBinAxis(BornAgain::V_AXIS_NAME, aY.getSize(), ymin, ymax));

    return result.release();
}

std::vector<IDetector2D::EAxesUnits> RectangularDetector::getValidAxesUnits() const
{
    std::vector<IDetector2D::EAxesUnits> result = IDetector2D::getValidAxesUnits();
    std::vector<IDetector2D::EAxesUnits> addon =
        { IDetector2D::RADIANS, IDetector2D::DEGREES, IDetector2D::MM, IDetector2D::QYQZ };
    result.insert(result.end(), addon.begin(), addon.end());
    return result;
}

IDetector2D::EAxesUnits RectangularDetector::getDefaultAxesUnits() const
{
    return IDetector2D::MM;
}

void RectangularDetector::print(std::ostream &ostr) const
{
    ostr << "RectangularDetector: '" << getName() << "' " << m_parameters;
    for (size_t i = 0; i < m_axes.size(); ++i) {
        ostr << "    IAxis:" << *m_axes[i] << std::endl;
    }
}

IAxis *RectangularDetector::createAxis(size_t index, size_t n_bins, double min, double max) const
{
    if (max <= min) {
        throw LogicErrorException(
            "RectangularDetector::createAxis() -> Error! max <= min");
    }
    if (n_bins == 0) {
        throw LogicErrorException(
            "RectangularDetector::createAxis() -> Error! Number n_bins can't be zero.");
    }    return new FixedBinAxis(getAxisName(index), n_bins, min, max);
}

std::string RectangularDetector::getAxisName(size_t index) const
{
    switch (index) {
    case 0:
        return BornAgain::U_AXIS_NAME;
        break;
    case 1:
        return BornAgain::V_AXIS_NAME;
        break;
    default:
        throw LogicErrorException(
            "RectangularDetector::getAxisName(size_t index) -> Error! index > 1");
    }
}

void RectangularDetector::swapContent(RectangularDetector &other)
{
    IDetector2D::swapContent(other);
    std::swap(this->m_normal_to_detector, other.m_normal_to_detector);
    std::swap(this->m_u_unit, other.m_u_unit);
    std::swap(this->m_v_unit, other.m_v_unit);
}

void RectangularDetector::setDistanceAndOffset(double distance, double u0, double v0)
{
    if(distance <= 0.0) {
        std::ostringstream message;
        message << "RectangularDetector::setPerpendicularToSample() -> Error. "
                << "Distance to sample can't be negative or zero";
        throw Exceptions::LogicErrorException(message.str());
    }
    m_distance = distance;
    m_u0 = u0;
    m_v0 = v0;
}

void RectangularDetector::initNormalVector(const kvector_t &central_k)
{
    kvector_t central_k_unit = central_k.unit();

    if (m_detector_arrangement == GENERIC) {
        // do nothing
    }

    else if(m_detector_arrangement == PERPENDICULAR_TO_SAMPLE) {
        m_normal_to_detector = kvector_t(m_distance, 0.0, 0.0);
    }

    else if(m_detector_arrangement == PERPENDICULAR_TO_DIRECT_BEAM) {
        m_normal_to_detector = m_distance*central_k_unit;
    }

    else if(m_detector_arrangement == PERPENDICULAR_TO_REFLECTED_BEAM) {
        m_normal_to_detector = m_distance*central_k_unit;
        m_normal_to_detector.setZ(-m_normal_to_detector.z());
    }

    else if(m_detector_arrangement == PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
        m_normal_to_detector = m_distance*central_k_unit;
        m_normal_to_detector.setZ(-m_normal_to_detector.z());
    }

    else {
        throw LogicErrorException("RectangularDetector::init() -> Unknown detector arrangement");
    }
}

void RectangularDetector::initUandV(double alpha_i)
{
    double d2 = m_normal_to_detector.dot(m_normal_to_detector);
    kvector_t u_direction =
            d2 * m_direction - m_direction.dot(m_normal_to_detector) * m_normal_to_detector;
    m_u_unit = u_direction.unit();
    m_v_unit = m_u_unit.cross(m_normal_to_detector).unit();

    if(m_detector_arrangement == PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
        kvector_t z(0.0, 0.0, 1.0);
        kvector_t normal_unit = m_normal_to_detector.unit();
        kvector_t zp = z - z.dot(normal_unit)*normal_unit;
        double uz = zp.dot(m_u_unit)/zp.mag();
        double vz = zp.dot(m_v_unit)/zp.mag();
        m_u0 = m_dbeam_u0 + m_distance*std::tan(2*alpha_i)*uz;
        m_v0 = m_dbeam_v0 + m_distance*std::tan(2*alpha_i)*vz;
    }
}

RectPixelMap::RectPixelMap(kvector_t corner_pos, kvector_t width, kvector_t height)
    : m_corner_pos(corner_pos), m_width(width), m_height(height)
{
    m_normal = m_width.cross(m_height);
    m_solid_angle = calculateSolidAngle();
}

RectPixelMap *RectPixelMap::clone() const
{
    return new RectPixelMap(m_corner_pos, m_width, m_height);
}

RectPixelMap *RectPixelMap::createZeroSizeMap(double x, double y) const
{
    kvector_t position = m_corner_pos + x*m_width + y*m_height;
    kvector_t null_vector;
    return new RectPixelMap(position, null_vector, null_vector);
}

kvector_t RectPixelMap::getK(double x, double y, double wavelength) const
{
    kvector_t direction = m_corner_pos + x*m_width + y*m_height;
    double length = 2.0*M_PI/wavelength;
    return normalizeLength(direction, length);
}

double RectPixelMap::getIntegrationFactor(double x, double y) const
{
    if (m_solid_angle==0.0) return 1.0;
    kvector_t position = m_corner_pos + x*m_width + y*m_height;
    double length = position.mag();
    return std::abs(position.dot(m_normal))/std::pow(length, 3)/m_solid_angle;
}

double RectPixelMap::getSolidAngle() const
{
    if (m_solid_angle<=0.0) return 1.0;
    return m_solid_angle;
}

kvector_t RectPixelMap::normalizeLength(const kvector_t &direction, double length) const
{
    return direction.unit()*length;
}

double RectPixelMap::calculateSolidAngle() const
{
    kvector_t position = m_corner_pos + 0.5*m_width + 0.5*m_height;
    double length = position.mag();
    return std::abs(position.dot(m_normal))/std::pow(length, 3);
}
