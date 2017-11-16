// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IDetector2D.cpp
//! @brief     Implements shared functionality of interface IDetector2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IDetector2D.h"
#include "Beam.h"
#include "IDetectorResolution.h"
#include "InfinitePlane.h"
#include "SimulationElement.h"
#include "SimulationArea.h"
#include "BornAgainNamespace.h"
#include "Units.h"
#include "RegionOfInterest.h"
#include "Exceptions.h"
#include "ConvolutionDetectorResolution.h"
#include "DetectorFunctions.h"

IDetector2D::IDetector2D() = default;

IDetector2D::IDetector2D(const IDetector2D &other)
    : IDetector(other)
    , m_detector_mask(other.m_detector_mask)
{
    if(other.mP_detector_resolution)
        setDetectorResolution(*other.mP_detector_resolution);
    if(other.regionOfInterest())
        m_region_of_interest.reset(other.regionOfInterest()->clone());
}

IDetector2D::~IDetector2D() {}

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
    if (!p_intensity_map)
        throw Exceptions::NullPointerException("IDetector2D::applyDetectorResolution() -> "
                                   "Error! Null pointer to intensity map");
    if (mP_detector_resolution)
        mP_detector_resolution->applyDetectorResolution(p_intensity_map);
}

OutputData<double> *IDetector2D::createDetectorIntensity(
        const std::vector<SimulationElement> &elements,
        const Beam &beam, IDetector2D::EAxesUnits units_type) const
{
    std::unique_ptr<OutputData<double>> detectorMap(createDetectorMap(beam, units_type));
    if(!detectorMap)
        throw Exceptions::RuntimeErrorException("Instrument::createDetectorIntensity:"
                                                "can't create detector map.");

    if (mP_detector_resolution) {
        if(units_type != DEFAULT) {
            std::unique_ptr<OutputData<double>> defaultMap(createDetectorMap(beam, DEFAULT));
            setDataToDetectorMap(*defaultMap, elements);
            applyDetectorResolution(defaultMap.get());
            detectorMap->setRawDataVector(defaultMap->getRawDataVector());
        } else {
            setDataToDetectorMap(*detectorMap, elements);
            applyDetectorResolution(detectorMap.get());
        }
    } else {
        setDataToDetectorMap(*detectorMap, elements);
    }

    return detectorMap.release();
}

OutputData<double>* IDetector2D::createDetectorMap(const Beam& beam, EAxesUnits units) const
{
    check_axes_units(units);

    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    result->addAxis(*constructAxis(BornAgain::X_AXIS_INDEX, beam, units));
    result->addAxis(*constructAxis(BornAgain::Y_AXIS_INDEX, beam, units));
    result->setAllTo(0.);
    return result.release();
}

std::vector<IDetector2D::EAxesUnits> IDetector2D::getValidAxesUnits() const
{
    std::vector<EAxesUnits> result = {NBINS};
    return result;
}

const RegionOfInterest *IDetector2D::regionOfInterest() const
{
    return m_region_of_interest.get();
}

void IDetector2D::setRegionOfInterest(double xlow, double ylow, double xup, double yup)
{
    m_region_of_interest.reset(new RegionOfInterest(*this, xlow, ylow, xup, yup));
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::resetRegionOfInterest()
{
    m_region_of_interest.reset();
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::removeMasks()
{
    m_detector_mask.removeMasks();
}

void IDetector2D::addMask(const IShape2D &shape, bool mask_value)
{
    m_detector_mask.addMask(shape, mask_value);
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::maskAll()
{
    if(getDimension() != 2) return;
    m_detector_mask.removeMasks();
    addMask(InfinitePlane(), true);
}

const DetectorMask *IDetector2D::getDetectorMask() const
{
    return &m_detector_mask;
}

size_t IDetector2D::numberOfMaskedChannels() const
{
    return getDetectorMask() ? getDetectorMask()->numberOfMaskedChannels() : 0;
}

bool IDetector2D::isMasked(size_t index) const
{
    return m_detector_mask.isMasked(index);
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
    Eigen::Matrix2cd analyzer_operator = detectionProperties().analyzerOperator();

    if (!hasMasks())
        m_detector_mask.initMaskData(*this);
    size_t spec_index = getIndexOfSpecular(beam);

    SimulationArea area(this);
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
        SimulationElement sim_element(wavelength, alpha_i, phi_i, std::unique_ptr<IPixel>(
                                          createPixel(it.detectorIndex())));
        sim_element.setPolarization(beam_polarization);
        sim_element.setAnalyzerOperator(analyzer_operator);
        if (it.index()==spec_index) {
            sim_element.setSpecular(true);
        }
        result.push_back(std::move(sim_element));
    }

    return result;
}

SimulationElement IDetector2D::getSimulationElement(size_t index, const Beam &beam) const
{
    double wavelength = beam.getWavelength();
    double alpha_i = - beam.getAlpha();  // Defined to be always positive in Beam
    double phi_i = beam.getPhi();
    return SimulationElement(wavelength, alpha_i, phi_i,
                             std::unique_ptr<IPixel>(createPixel(index)));
}

size_t IDetector2D::numberOfSimulationElements() const
{
    size_t result(0);
    try {
        SimulationArea area(this);
        for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it)
            ++result;
    } catch (Exceptions::RuntimeErrorException e)
    {
        (void)e;  // do nothing, just return zero
    }
    return result;
}

std::vector<const INode*> IDetector2D::getChildren() const
{
    std::vector<const INode*> result = IDetector::getChildren();
    result << mP_detector_resolution;
    return result;
}

std::unique_ptr<IAxis> IDetector2D::constructAxis(size_t axis_index, const Beam &beam,
                                                  IDetector2D::EAxesUnits units) const
{
    double amin(0), amax(0);
    calculateAxisRange(axis_index, beam, units, amin, amax);

    std::unique_ptr<IAxis> result(new FixedBinAxis(getAxisName(axis_index),
                                                   getAxis(axis_index).size(), amin, amax));

    if (m_region_of_interest)
        return m_region_of_interest->clipAxisToRoi(axis_index, *result);

    return result;
}

void IDetector2D::calculateAxisRange(size_t axis_index, const Beam &beam,
        IDetector2D::EAxesUnits units, double &amin, double &amax) const
{
    amin = 0.0; amax=0.0;

    if(units == DEFAULT) {
        amin = getAxis(axis_index).getMin();
        amax = getAxis(axis_index).getMax();

    }else if(units == NBINS) {
        amin = 0.0;
        amax = static_cast<double>(getAxis(axis_index).size());

    } else if(units == QYQZ && axis_index == BornAgain::X_AXIS_INDEX) {
        const IAxis &aX = getAxis(BornAgain::X_AXIS_INDEX);
        SimulationElement el_left_bottom
            = getSimulationElement(getGlobalIndex(0, 0), beam);
        SimulationElement el_right_bottom
            = getSimulationElement(getGlobalIndex(aX.size()-1, 0), beam);
        amin = el_left_bottom.getQ(0.0, 0.0).y();
        amax = el_right_bottom.getQ(1.0, 0.0).y();

    } else if(units == QYQZ && axis_index == BornAgain::Y_AXIS_INDEX) {
        const IAxis &aX = getAxis(BornAgain::X_AXIS_INDEX);
        const IAxis &aY = getAxis(BornAgain::Y_AXIS_INDEX);
        SimulationElement el_center_bottom
            = getSimulationElement(getGlobalIndex(aX.size()/2, 0), beam);
        SimulationElement el_center_top
            = getSimulationElement(getGlobalIndex(aX.size()/2, aY.size()-1), beam);
        amin = -el_center_bottom.getQ(0.5, 0.0).z();
        amax = -el_center_top.getQ(0.5, 1.0).z();

    } else {
        throw Exceptions::RuntimeErrorException("IDetector2D::calculateAxisRange() -> Error. "
                                                "Unknown units " +std::to_string(units));
    }
}

size_t IDetector2D::getGlobalIndex(size_t x, size_t y) const
{
    if (getDimension() != 2)
        return getTotalSize();
    return x * getAxis(1).size() + y;
}

void IDetector2D::setDataToDetectorMap(OutputData<double> &detectorMap,
                                       const std::vector<SimulationElement> &elements) const
{
    if(elements.empty())
        return;
    SimulationArea area(this);
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it)
        detectorMap[it.roiIndex()] = elements[it.elementIndex()].getIntensity();

}

void IDetector2D::setDetectorResolution(const IDetectorResolution& p_detector_resolution)
{
    mP_detector_resolution.reset(p_detector_resolution.clone());
    registerChild(mP_detector_resolution.get());
}

void IDetector2D::setResolutionFunction(const IResolutionFunction2D& resFunc)
{
    ConvolutionDetectorResolution convFunc(resFunc);
    setDetectorResolution(convFunc);
}

void IDetector2D::removeDetectorResolution()
{
    mP_detector_resolution.reset();
}

const IDetectorResolution* IDetector2D::detectorResolution() const
{
    return mP_detector_resolution.get();
}

//! Checks if given unit is valid for the detector. Throws exception if it is not the case.
void IDetector2D::check_axes_units(IDetector2D::EAxesUnits units) const
{
    if(units == DEFAULT)
        return;

    auto validUnits = getValidAxesUnits();
    if(std::find(validUnits.begin(), validUnits.end(), units) == validUnits.end()) {
        std::ostringstream message;
        message << "IDetector2D::createDetectorMap() -> Error. Unknown axes unit " << units << "\n";
        message << "Available units for this detector type \n";
        for(size_t i=0; i<validUnits.size(); ++i)
        for(auto unit : validUnits)
            message << unit << " ";
        message << "\n";
        throw std::runtime_error(message.str());
    }
}

