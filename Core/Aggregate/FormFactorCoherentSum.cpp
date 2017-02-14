// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FormFactorCoherentSum.cpp
//! @brief     Implements class FormFactorCoherentSum.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCoherentSum.h"
#include "IFormFactor.h"
#include "SimulationElement.h"
#include "WavevectorInfo.h"
#include "IFresnelMap.h"
#include "ILayerRTCoefficients.h"
#include "Exceptions.h"

FormFactorCoherentSum::FormFactorCoherentSum(double abundance)
: m_abundance(abundance)
{
}

FormFactorCoherentSum::~FormFactorCoherentSum() {}

FormFactorCoherentSum* FormFactorCoherentSum::clone() const
{
    return new FormFactorCoherentSum(m_parts, m_abundance);
}

void FormFactorCoherentSum::addFormFactor(IFormFactor* p_ff)
{
    m_parts.emplace_back(p_ff);
}

complex_t FormFactorCoherentSum::evaluate(const SimulationElement& sim_element) const
{
    complex_t result {};
    for (auto& part : m_parts) {
        result += part.evaluate(sim_element);
    }
    return result;
}

Eigen::Matrix2cd FormFactorCoherentSum::evaluatePol(const SimulationElement& sim_element) const
{
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    for (auto& part : m_parts) {
        result += part.evaluatePol(sim_element);
    }
    return result;
}

void FormFactorCoherentSum::setSpecularInfo(const IFresnelMap* p_fresnel_map, size_t layer_index)
{
    m_parts[0].setSpecularInfo(p_fresnel_map, layer_index);
}

void FormFactorCoherentSum::scaleRelativeAbundance(double total_abundance)
{
    if (total_abundance>0.0) {
        m_abundance /= total_abundance;
        return;
    }
    throw Exceptions::LogicErrorException("FormFactorCoherentSum::scaleRelativeAbundance: "
                                          "Trying to scale with non strictly positive factor.");
}

double FormFactorCoherentSum::radialExtension() const
{
    return m_parts[0].radialExtension();
}

FormFactorCoherentSum::FormFactorCoherentSum(const std::vector<FormFactorCoherentPart>& parts,
                                             double abundance)
: m_parts(parts), m_abundance(abundance)
{
}
