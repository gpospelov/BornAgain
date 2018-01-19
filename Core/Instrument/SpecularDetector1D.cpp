// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SpecularDetector1D.h
//! @brief     Implements a detector for specular simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Beam.h"
#include "DetectorElement.h"
#include "IPixel.h"
#include "OutputData.h"
#include "SimulationArea.h"
#include "SpecularDetector1D.h"
#include "SpecularSimulationElement.h"
#include "Units.h"

namespace {
class SpecularPixel : public IPixel
{
public:
    SpecularPixel(double alpha_i) : m_alpha_i(alpha_i) {}
    virtual ~SpecularPixel() = default;

    SpecularPixel* clone() const override {return new SpecularPixel(m_alpha_i);}

    // SpecularPixel already has zero size
    SpecularPixel* createZeroSizePixel(double, double) const override {return clone();}

    kvector_t getK(double, double, double wavelength) const override
    {
        return vecOfLambdaAlphaPhi(wavelength, -m_alpha_i, 0.0);
    }

    double getIntegrationFactor(double, double) const override {return 1;}
    double getSolidAngle() const override {return 1;}

private:
    double m_alpha_i;
};
}

SpecularDetector1D::SpecularDetector1D(const IAxis& axis)
{
    addAxis(axis);
}

SpecularDetector1D::SpecularDetector1D(const SpecularDetector1D& detector) : IDetector(detector)
{
}

SpecularDetector1D::~SpecularDetector1D() = default;

SpecularDetector1D* SpecularDetector1D::clone() const {
    return new SpecularDetector1D(*this);
}

AxesUnits SpecularDetector1D::defaultAxesUnits() const {
    return AxesUnits::RADIANS;
}

std::vector<AxesUnits> SpecularDetector1D::validAxesUnits() const {
    std::vector<AxesUnits> result = IDetector::validAxesUnits();
    const std::vector<AxesUnits> addon = {AxesUnits::RADIANS, AxesUnits::DEGREES};
    result.insert(result.end(), addon.begin(), addon.end());
    return result;
}

double SpecularDetector1D::alphaI(size_t index) const
{
    const IAxis& axis = getAxis(BornAgain::X_AXIS_INDEX);
    const size_t axis_index = axisBinIndex(index, BornAgain::X_AXIS_INDEX);
    return axis.getBin(axis_index).getMidPoint();
}

std::vector<SpecularSimulationElement>
SpecularDetector1D::createSimulationElements(const Beam& beam)
{
    std::vector<SpecularSimulationElement> result;

    const double wavelength = beam.getWavelength();
    PolarizationHandler handler;
    handler.setPolarization(beam.getPolarization());
    handler.setAnalyzerOperator(detectionProperties().analyzerOperator());

    SimulationArea area(this);
    result.reserve(area.totalSize());
    for (SimulationArea::iterator it = area.begin(); it != area.end(); ++it) {
        // opposite sign for alpha_i since e_{z_beam} = - e_{z_detector}
        const double alpha_i = -alphaI(it.detectorIndex());
        result.emplace_back(wavelength, alpha_i);
        auto& sim_element = result.back();
        sim_element.setPolarizationHandler(handler);
    }

    return result;
}

std::vector<DetectorElement> SpecularDetector1D::createDetectorElements(const Beam&)
{
    std::vector<DetectorElement> result;
    const Eigen::Matrix2cd& analyzer_operator = detectionProperties().analyzerOperator();

    SimulationArea area(this);
    result.reserve(area.totalSize());
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
        const double alpha_i = -alphaI(it.detectorIndex());
        result.emplace_back(new SpecularPixel(alpha_i), analyzer_operator);
        auto& detector_element = result.back();
        detector_element.setSpecular();
    }
    return result;
}

OutputData<double>*
SpecularDetector1D::createDetectorIntensity(const std::vector<SpecularSimulationElement>& elements,
                                            const Beam& beam, AxesUnits units_type) const
{
    std::unique_ptr<OutputData<double>> detectorMap(createDetectorMap(beam, units_type));
    if (!detectorMap)
        throw std::runtime_error("Instrument::createDetectorIntensity:"
                                                "can't create detector map.");

    if (detectorResolution()) {
        if (units_type != AxesUnits::DEFAULT) {
            std::unique_ptr<OutputData<double>> defaultMap(
                createDetectorMap(beam, AxesUnits::DEFAULT));
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

std::string SpecularDetector1D::axisName(size_t index) const
{
    if (index == 0) {
        return BornAgain::U_AXIS_NAME;
    } else
        throw std::runtime_error(
            "SpecularDetector1D::getAxisName(size_t index) -> Error! index > 0");
}

void SpecularDetector1D::calculateAxisRange(size_t axis_index, const Beam& beam, AxesUnits units,
                                            double& amin, double& amax) const
{
    if (units == AxesUnits::DEGREES) {
        amin = getAxis(axis_index).getMin() / Units::degree;
        amax = getAxis(axis_index).getMax() / Units::degree;
    } else if (units == AxesUnits::RADIANS) {
        amin = getAxis(axis_index).getMin();
        amax = getAxis(axis_index).getMax();
    } else {
        IDetector::calculateAxisRange(axis_index, beam, units, amin, amax);
    }
}

void SpecularDetector1D::setDataToDetectorMap(
    OutputData<double>& detectorMap, const std::vector<SpecularSimulationElement>& elements) const
{
    if(elements.empty())
        return;
    SimulationArea area(this);
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it)
        detectorMap[it.roiIndex()] = elements[it.elementIndex()].getIntensity();

}
