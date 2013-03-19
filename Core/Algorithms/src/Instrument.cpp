// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/Instrument.cpp
//! @brief     Implements class Instrument.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "Instrument.h"

#include "ExperimentConstants.h"
#include "ConvolutionDetectorResolution.h"

Instrument::Instrument()
: IParameterized("Instrument")
{
    init_parameters();
}

Instrument::Instrument(const Instrument& other)
: IParameterized()
, m_detector(other.m_detector)
, m_beam(other.m_beam)
{
    setName(other.getName());
    init_parameters();
}

void Instrument::matchDetectorParameters(const OutputData<double>& output_data)
{
    m_detector.clear();
    for(size_t i_axis=0; i_axis<output_data.getNdimensions(); ++i_axis) {
        const IAxis *axis = output_data.getAxis(i_axis);
        m_detector.addAxis(*axis);
    }
}

void Instrument::setDetectorParameters(size_t n_phi, double phi_f_min,
        double phi_f_max, size_t n_alpha, double alpha_f_min,
        double alpha_f_max, bool isgisaxs_style)
{
    AxisParameters phi_params;
    phi_params.m_name = NDetector2d::PHI_AXIS_NAME;
    phi_params.m_range = TSampledRange<double>(n_phi, phi_f_min, phi_f_max);
    AxisParameters alpha_params;
    alpha_params.m_name = NDetector2d::ALPHA_AXIS_NAME;
    alpha_params.m_range = TSampledRange<double>(n_alpha, alpha_f_min, alpha_f_max);
    if (isgisaxs_style) {
        phi_params.m_sample_method = AxisParameters::E_ISGISAXS;
        alpha_params.m_sample_method = AxisParameters::E_ISGISAXS;
    }
    else {
        phi_params.m_sample_method = AxisParameters::E_DEFAULT;
        alpha_params.m_sample_method = AxisParameters::E_DEFAULT;
    }
    DetectorParameters detector_params = { phi_params, alpha_params };
    setDetectorParameters(detector_params);
}

void Instrument::setDetectorParameters(const DetectorParameters& params)
{
    m_detector.clear();

    m_detector.addAxis(params.m_phi_params);
    m_detector.addAxis(params.m_alpha_params);
}

std::string Instrument::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the beam
    m_beam.addParametersToExternalPool(new_path, external_pool, -1);

    // add parameters of the detector
    m_detector.addParametersToExternalPool(new_path, external_pool, -1);

    return new_path;
}

void Instrument::normalize(OutputData<double> *p_intensity) const
{
    // normalize by intensity, if strictly positive
    if (getIntensity()>0.0) {
        p_intensity->scaleAll(getIntensity());
    }

    // normalize by detector cell sizes
    double sin_alpha_i = std::abs(getBeam().getCentralK().cosTheta());
    m_detector.normalize(p_intensity, sin_alpha_i);
}

void Instrument::setDetectorResolutionFunction(
        IResolutionFunction2D* p_resolution_function)
{
    m_detector.setDetectorResolution( new ConvolutionDetectorResolution(p_resolution_function) );
}

void Instrument::applyDetectorResolution(
        OutputData<double>* p_intensity_map) const
{
    m_detector.applyDetectorResolution(p_intensity_map);
}

void Instrument::init_parameters()
{
}
