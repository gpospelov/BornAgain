// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/IDetector2D.cpp
//! @brief     Implements shared functionality of interface IDetector2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InfinitePlane.h"
#include "MessageService.h"
#include "IDetector2D.h"


IDetector2D::IDetector2D()
    : m_axes()
{
    init_parameters();
    initPolarizationOperator();
}

IDetector2D::IDetector2D(const IDetector2D &other)
    : IParameterized(), m_axes(other.m_axes),
      m_analyzer_operator(other.m_analyzer_operator), m_detector_mask(other.m_detector_mask)
{
    setName(other.getName());
    if (other.mP_detector_resolution.get())
        mP_detector_resolution.reset(other.mP_detector_resolution->clone());
    init_parameters();
}

void IDetector2D::init(const Beam &beam)
{
    (void)beam;
}

const IAxis &IDetector2D::getAxis(size_t index) const
{
    if (isCorrectAxisIndex(index)) {
        return *m_axes[index];
    }
    throw Exceptions::OutOfBoundsException("Not so many axes in this detector.");
}

void IDetector2D::matchDetectorAxes(const OutputData<double> &output_data)
{
    if (output_data.getRank()!=2) {
        throw Exceptions::LogicErrorException(
            "IDetector2D::matchDetectorAxes() -> Error! Data is not two dimensional");
    }
    clear();
    for (size_t i_axis = 0; i_axis < output_data.getRank(); ++i_axis) {
        addAxis(*output_data.getAxis(i_axis));
    }
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::setDetectorParameters(size_t n_x, double x_min, double x_max,
                                        size_t n_y, double y_min, double y_max)
{
    clear();
    const std::unique_ptr<IAxis> P_axis0(createAxis(0, n_x, x_min, x_max));
    const std::unique_ptr<IAxis> P_axis1(createAxis(1, n_y, y_min, y_max));
    addAxis(*P_axis0);
    addAxis(*P_axis1);
}

void IDetector2D::setDetectorAxes(const IAxis &axis0, const IAxis &axis1)
{
    clear();
    addAxis(axis0);
    addAxis(axis1);
}

void IDetector2D::applyDetectorResolution(OutputData<double> *p_intensity_map) const
{
    if (!p_intensity_map) {
        throw Exceptions::NullPointerException("IDetector2D::applyDetectorResolution() -> "
                                   "Error! Null pointer to intensity map");
    }
    if (mP_detector_resolution.get()) {
        mP_detector_resolution->applyDetectorResolution(p_intensity_map);
    } else {
        msglog(MSG::WARNING) << "IDetector2D::applyDetectorResolution() -> "
                                "No detector resolution function found";
    }
}

void IDetector2D::setAnalyzerProperties(const kvector_t direction, double efficiency,
                                     double total_transmission)
{
    if (!checkAnalyzerProperties(direction, efficiency, total_transmission))
        throw Exceptions::ClassInitializationException(
            "IDetector2D::setAnalyzerProperties: the given properties are not physical");
    m_analyzer_operator = calculateAnalyzerOperator(direction, efficiency, total_transmission);
}


std::string IDetector2D::addParametersToExternalPool(
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

OutputData<double> *IDetector2D::createDetectorMap(
    const Beam& /* beam */, EAxesUnits /* units_type */) const
{
    return 0;
}

std::vector<IDetector2D::EAxesUnits> IDetector2D::getValidAxesUnits() const
{
    std::vector<EAxesUnits> result = {NBINS};
    return result;
}

IDetector2D::EAxesUnits IDetector2D::getDefaultAxesUnits() const
{
    return DEFAULT;
}

void IDetector2D::removeMasks()
{
    m_detector_mask.removeMasks();
}

void IDetector2D::addMask(const Geometry::IShape2D &shape, bool mask_value)
{
    m_detector_mask.addMask(shape, mask_value);
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::maskAll()
{
    if(m_axes.size() != 2) return;
    m_detector_mask.removeMasks();
    addMask(Geometry::InfinitePlane(), true);
}

const DetectorMask *IDetector2D::getDetectorMask() const
{
    return &m_detector_mask;
}

int IDetector2D::getNumberOfMaskedChannels() const
{
    if(getDetectorMask()) {
        return getDetectorMask()->getNumberOfMaskedChannels();
    } else {
        return 0;
    }
}

bool IDetector2D::isMasked(size_t index) const
{
    if(!m_detector_mask.getMaskData()->isInitialized()) return false;
    return m_detector_mask.getMask(index);
}

bool IDetector2D::hasMasks() const
{
    return m_detector_mask.hasMasks();
}

std::vector<SimulationElement> IDetector2D::createSimulationElements(const Beam &beam)
{
    std::vector<SimulationElement> result;
    double wavelength = beam.getWavelength();
    double alpha_i = - beam.getAlpha();  // Defined to be always positive in Beam
    double phi_i = beam.getPhi();
    Eigen::Matrix2cd beam_polarization = beam.getPolarization();
    Eigen::Matrix2cd analyzer_operator = getAnalyzerOperator();

    if (getDimension()!=2)
        throw Exceptions::RuntimeErrorException("IDetector2D::createSimulationElements: "
                                    "detector is not two-dimensional");
    if (!hasMasks()) m_detector_mask.initMaskData(*this);
    const OutputData<bool>* mask_data = m_detector_mask.getMaskData();
    for (size_t index=0; index<mask_data->getAllocatedSize(); ++index) {
        if ((*mask_data)[index]) continue;
        const std::unique_ptr<IPixelMap> P_pixel_map(createPixelMap(index));
        SimulationElement sim_element(wavelength, alpha_i, phi_i, P_pixel_map.get());
        sim_element.setPolarization(beam_polarization);
        sim_element.setAnalyzerOperator(analyzer_operator);
        result.push_back(sim_element);
    }
    return result;
}

//! create single simulation element
SimulationElement IDetector2D::getSimulationElement(size_t index, const Beam &beam) const
{
    double wavelength = beam.getWavelength();
    double alpha_i = - beam.getAlpha();  // Defined to be always positive in Beam
    double phi_i = beam.getPhi();
    const std::unique_ptr<IPixelMap> P_pixel_map(createPixelMap(index));
    return SimulationElement(wavelength, alpha_i, phi_i, P_pixel_map.get());
}

bool IDetector2D::dataShapeMatches(const OutputData<double> *p_data) const
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

void IDetector2D::initPolarizationOperator()
{
    m_analyzer_operator = Eigen::Matrix2cd::Identity();
}

size_t IDetector2D::getAxisBinIndex(size_t index, size_t selected_axis) const
{
    size_t remainder(index);
    for (size_t i=0; i<getDimension(); ++i)
    {
        size_t i_axis = getDimension()-1-i;
        int result = remainder % m_axes[i_axis]->getSize();
        if(selected_axis == i_axis ) return result;
        remainder /= m_axes[i_axis]->getSize();
    }
    throw Exceptions::LogicErrorException("IDetector2D::getAxisBinIndex() -> "
                              "Error! No axis with given number");
}

void IDetector2D::swapContent(IDetector2D &other)
{
    std::swap(this->m_axes, other.m_axes);
    std::swap(this->mP_detector_resolution, other.mP_detector_resolution);
    std::swap(this->m_analyzer_operator, other.m_analyzer_operator);
    std::swap(this->m_detector_mask, other.m_detector_mask);
}

bool IDetector2D::checkAnalyzerProperties(
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

Eigen::Matrix2cd IDetector2D::calculateAnalyzerOperator(
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
