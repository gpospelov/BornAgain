// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/Instrument.cpp
//! @brief     Implements class Instrument.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Instrument.h"
#include "SphericalDetector.h"
#include "ConvolutionDetectorResolution.h"

Instrument::Instrument()
    : IParameterized("Instrument")
{
    mP_detector.reset(new SphericalDetector());
    init_parameters();
}

Instrument::Instrument(const Instrument &other) : IParameterized(), m_beam(other.m_beam)
{
    mP_detector.reset(other.mP_detector->clone());
    setName(other.getName());
    init_parameters();
}

Instrument &Instrument::operator=(const Instrument &other)
{
    if (this != &other) {
        m_beam = other.m_beam;
        mP_detector.reset(other.mP_detector->clone());
        init_parameters();
    }
    return *this;
}

void Instrument::setDetector(const IDetector2D& detector)
{
    mP_detector.reset(detector.clone());
    initDetector();
}

void Instrument::matchDetectorAxes(const OutputData<double> &output_data)
{
    mP_detector->matchDetectorAxes(output_data);
}

void Instrument::setDetectorParameters(size_t n_x, double x_min, double x_max,
                                       size_t n_y, double y_min, double y_max)
{
    mP_detector->setDetectorParameters(n_x, x_min, x_max, n_y, y_min, y_max);
}

void Instrument::setDetectorAxes(const IAxis &axis0, const IAxis &axis1)
{
    mP_detector->setDetectorAxes(axis0, axis1);
}

std::string Instrument::addParametersToExternalPool(
    std::string path, ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string new_path = IParameterized::addParametersToExternalPool(
        path, external_pool, copy_number);

    // add parameters of the beam
    m_beam.addParametersToExternalPool(new_path, external_pool, -1);

    // add parameters of the detector
    mP_detector->addParametersToExternalPool(new_path, external_pool, -1);

    return new_path;
}

void Instrument::initDetector()
{
    if(!mP_detector)
        throw Exceptions::RuntimeErrorException(
            "Instrument::initDetector() -> Error. Detector is not initialized.");
    getDetector()->init(getBeam());
}


std::vector<SimulationElement> Instrument::createSimulationElements()
{
    return mP_detector->createSimulationElements(m_beam);
}

void Instrument::setDetectorResolutionFunction(IResolutionFunction2D* p_resolution_function)
{
    if (p_resolution_function) {
        mP_detector->setDetectorResolution(
            new ConvolutionDetectorResolution(p_resolution_function));
    } else {
        mP_detector->setDetectorResolution(0);
    }
}

void Instrument::setDetectorResolutionFunction(const IResolutionFunction2D& p_resolution_function)
{
    mP_detector->setDetectorResolution(new ConvolutionDetectorResolution(p_resolution_function));
}

void Instrument::applyDetectorResolution(OutputData<double>* p_intensity_map) const
{
    mP_detector->applyDetectorResolution(p_intensity_map);
}

OutputData<double>* Instrument::getDetectorIntensity(
    const OutputData<double> &data, IDetector2D::EAxesUnits units_type) const
{
    std::unique_ptr<OutputData<double> > result (data.clone());
    applyDetectorResolution(result.get());

    if(units_type == IDetector2D::DEFAULT) {
        return result.release();
    } else {
        OutputData<double>* detectorMap = mP_detector->createDetectorMap(m_beam, units_type);
        if(!detectorMap) {
            throw Exceptions::RuntimeErrorException("Instrument::getDetectorIntensity() -> Error."
                                        "Can't create detector map.");
        }
        detectorMap->setRawDataVector(result->getRawDataVector());
        return detectorMap;
    }
}

void Instrument::init_parameters()
{
}

void Instrument::print(std::ostream& ostr) const
{
    ostr << "Instrument: '" << getName() << "' " << m_parameters << std::endl;
    ostr << "    " << m_beam << std::endl;
    ostr << "    " << *mP_detector << std::endl;
}

void Instrument::setBeamParameters(double wavelength, double alpha_i, double phi_i)
{
    m_beam.setCentralK(wavelength, alpha_i, phi_i);
    if(mP_detector) initDetector();
}

void Instrument::setBeam(const Beam &beam)
{
    m_beam = beam;
    if(mP_detector) initDetector();
}
