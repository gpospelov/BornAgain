// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FormFactorCoherentPart.cpp
//! @brief     Implements class FormFactorCoherentPart.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCoherentPart.h"
#include "IFormFactor.h"
#include "SimulationElement.h"
#include "WavevectorInfo.h"
#include "LayerSpecularInfo.h"
#include "ILayerRTCoefficients.h"


FormFactorCoherentPart::FormFactorCoherentPart(IFormFactor* p_ff)
: mP_ff(p_ff)
{
}

FormFactorCoherentPart::FormFactorCoherentPart(const FormFactorCoherentPart& other)
: mP_ff(other.mP_ff->clone())
{
    setSpecularInfo(*other.mP_specular_info);
}

FormFactorCoherentPart::~FormFactorCoherentPart() {}

complex_t FormFactorCoherentPart::evaluate(const SimulationElement& sim_element) const
{
    WavevectorInfo wavevectors(sim_element.getKi(), sim_element.getMeanKf(),
                               sim_element.getWavelength());

    const std::unique_ptr<const ILayerRTCoefficients> P_in_coeffs(
        mP_specular_info->getInCoefficients(sim_element));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(sim_element));
    mP_ff->setSpecularInfo(P_in_coeffs.get(), P_out_coeffs.get());
    return mP_ff->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorCoherentPart::evaluatePol(const SimulationElement& sim_element) const
{
    WavevectorInfo wavevectors(sim_element.getKi(), sim_element.getMeanKf(),
                               sim_element.getWavelength());

    const std::unique_ptr<const ILayerRTCoefficients> P_in_coeffs(
        mP_specular_info->getInCoefficients(sim_element));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(sim_element));
    mP_ff->setSpecularInfo(P_in_coeffs.get(), P_out_coeffs.get());
    return mP_ff->evaluatePol(wavevectors);
}

void FormFactorCoherentPart::setSpecularInfo(const LayerSpecularInfo& specular_info)
{
    mP_specular_info.reset(specular_info.clone());
}

double FormFactorCoherentPart::radialExtension() const
{
    return mP_ff->getRadialExtension();
}
