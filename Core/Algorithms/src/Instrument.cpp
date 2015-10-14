// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/Instrument.cpp
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
#include "ConvolutionDetectorResolution.h"
#include "BornAgainNamespace.h"
#include "CustomBinAxis.h"
#include "ConstKBinAxis.h"

Instrument::Instrument()
    : IParameterized("Instrument")
{
    mP_detector.reset(new Detector());
    init_parameters();
}

Instrument::Instrument(const Instrument& other)
: IParameterized()
, m_beam(other.m_beam)
{
    mP_detector.reset(other.mP_detector->clone());
    setName(other.getName());
    init_parameters();
}

Instrument &Instrument::operator=(const Instrument &other)
{
    if (this!=&other) {
        mP_detector.reset(other.mP_detector->clone());
        setName(other.getName());
        init_parameters();
    }
    return *this;
}

void Instrument::matchDetectorParameters(const OutputData<double>& output_data)
{
    mP_detector->clear();
    for(size_t i_axis=0; i_axis<output_data.getRank(); ++i_axis) {
        const IAxis *axis = output_data.getAxis(i_axis);
        mP_detector->addAxis(*axis);
    }
}

void Instrument::setDetectorParameters(
    size_t n_phi, double phi_f_min, double phi_f_max,
    size_t n_alpha, double alpha_f_min, double alpha_f_max,
    bool isgisaxs_style)
{
    if(phi_f_max <= phi_f_min) {
        throw LogicErrorException("Instrument::setDetectorParameters() -> Error! phi_f_max <= phi_f_min");
    }
    if(alpha_f_max <= alpha_f_min) {
        throw LogicErrorException("Instrument::setDetectorParameters() -> Error! alpha_f_max <= alpha_f_min");
    }
    if(n_phi == 0) {
        throw LogicErrorException("Instrument::setDetectorParameters() -> Error! Number of n_phi bins can't be zero.");
    }
    if(n_alpha == 0) {
        throw LogicErrorException("Instrument::setDetectorParameters() -> Error! Number of n_alpha bins can't be zero.");
    }

    mP_detector->clear();

    if(isgisaxs_style) {
        mP_detector->addAxis(CustomBinAxis(BornAgain::PHI_AXIS_NAME, n_phi, phi_f_min, phi_f_max));
        mP_detector->addAxis(CustomBinAxis(BornAgain::ALPHA_AXIS_NAME, n_alpha, alpha_f_min, alpha_f_max));
    } else {
        mP_detector->addAxis(ConstKBinAxis(BornAgain::PHI_AXIS_NAME, n_phi, phi_f_min, phi_f_max));
        mP_detector->addAxis(ConstKBinAxis(BornAgain::ALPHA_AXIS_NAME, n_alpha, alpha_f_min, alpha_f_max));
    }
}

void Instrument::setDetectorAxes(const IAxis &axis0, const IAxis &axis1)
{
    mP_detector->clear();

    IAxis *p_axis0 = axis0.clone();
    p_axis0->setName(BornAgain::PHI_AXIS_NAME);

    IAxis *p_axis1 = axis1.clone();
    p_axis1->setName(BornAgain::ALPHA_AXIS_NAME);

    mP_detector->addAxis(*p_axis0);
    mP_detector->addAxis(*p_axis1);

    delete p_axis0;
    delete p_axis1;
}

std::string Instrument::addParametersToExternalPool(
    std::string path,
    ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the beam
    m_beam.addParametersToExternalPool(new_path, external_pool, -1);

    // add parameters of the detector
    mP_detector->addParametersToExternalPool(new_path, external_pool, -1);

    return new_path;
}

void Instrument::normalize(OutputData<double> *p_intensity) const
{
    // normalize by intensity, if strictly positive
    if (getIntensity()>0.0) {
        p_intensity->scaleAll(getIntensity());
    }
    kvector_t realpart(getBeam().getCentralK().x().real(),
                   getBeam().getCentralK().y().real(),
                   getBeam().getCentralK().z().real());

    // normalize by detector cell sizes
    double sin_alpha_i = std::abs(realpart.cosTheta());
    if (sin_alpha_i==0.0) sin_alpha_i = 1.0;
    mP_detector->normalize(p_intensity, sin_alpha_i);
}

std::vector<SimulationElement> Instrument::createSimulationElements()
{
    return mP_detector->createSimulationElements(m_beam);
}

void Instrument::setDetectorResolutionFunction(
    IResolutionFunction2D* p_resolution_function)
{
    if(p_resolution_function) {
        mP_detector->setDetectorResolution(
            new ConvolutionDetectorResolution(p_resolution_function) );
    } else {
        mP_detector->setDetectorResolution(0);
    }
}

void Instrument::setDetectorResolutionFunction(
    const IResolutionFunction2D &p_resolution_function)
{
    mP_detector->setDetectorResolution(
                new ConvolutionDetectorResolution(p_resolution_function) );
}

void Instrument::applyDetectorResolution(OutputData<double>* p_intensity_map) const
{
    mP_detector->applyDetectorResolution(p_intensity_map);
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
