// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Samples/IInterferenceFunctionStrategy.cpp
//! @brief     Implements default behaviour of IInterferenceFunctionStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IInterferenceFunctionStrategy.h"
#include "IInterferenceFunction.h"
#include "IntegratorMCMiser.h"
#include "LayerSpecularInfo.h"
#include "ScalarRTCoefficients.h"
#include "SimulationElement.h"
#include "Layer.h"

IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(SimulationOptions sim_params)
    : mP_iff { nullptr }
    , m_options(sim_params)
{
    mP_integrator = make_integrator_miser(
        this, &IInterferenceFunctionStrategy::evaluate_for_fixed_angles, 2);
    mP_integrator_pol = make_integrator_miser(
        this, &IInterferenceFunctionStrategy::evaluate_for_fixed_angles_pol, 2);
}

// destructor should be defined and it should be in *.cpp,
// otherwise forward declaration of IntegratorMCMiser doesn't work
IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy(){}

void IInterferenceFunctionStrategy::init(
    const SafePointerVector<FormFactorInfo>& form_factor_infos, const IInterferenceFunction& iff)
{
    m_ff_infos = form_factor_infos;
    mP_iff.reset(iff.clone());
}

void IInterferenceFunctionStrategy::setSpecularInfo(const LayerSpecularInfo& specular_info)
{
    if (mP_specular_info.get() != &specular_info)
        mP_specular_info.reset(specular_info.clone());
}

double IInterferenceFunctionStrategy::evaluate(const SimulationElement& sim_element) const
{
    if (m_options.isIntegrate() && (sim_element.getSolidAngle() > 0.0)) {
        return MCIntegratedEvaluate(sim_element);
    }
    calculateFormFactorList(sim_element);
    return evaluateForList(sim_element, m_ff);
}

double IInterferenceFunctionStrategy::evaluatePol(const SimulationElement& sim_element) const
{
    if (m_options.isIntegrate())
        return MCIntegratedEvaluatePol(sim_element);
    calculateFormFactorLists(sim_element);
    return evaluateForMatrixList(sim_element, m_ff_pol);
}

void IInterferenceFunctionStrategy::calculateFormFactorList(
        const SimulationElement& sim_element) const
{
    clearFormFactorLists();

    double wavelength = sim_element.getWavelength();
    double wavevector_scattering_factor = Units::PI/wavelength/wavelength;
    double alpha_i = sim_element.getAlphaI();
    double phi_i = sim_element.getPhiI();
    cvector_t k_i = Geometry::vecOfLambdaAlphaPhi(wavelength, alpha_i, phi_i).complex();
    WavevectorInfo wavevectors(k_i, Geometry::toComplexVector(sim_element.getMeanKF()), wavelength);

    const std::unique_ptr<const ILayerRTCoefficients> P_in_coeffs(
        mP_specular_info->getInCoefficients(alpha_i, 0.0, wavelength));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(sim_element.getAlphaMean(), 0.0, wavelength));
    for( auto it: m_ff_infos ) {
        it->mp_ff->setSpecularInfo(P_in_coeffs.get(), P_out_coeffs.get());
        complex_t ff_mat = it->mp_ff->evaluate(wavevectors);
        m_ff.push_back(wavevector_scattering_factor*ff_mat);
    }
}

void IInterferenceFunctionStrategy::calculateFormFactorLists(
        const SimulationElement &sim_element) const
{
    clearFormFactorLists();

    double wavelength = sim_element.getWavelength();
    double wavevector_scattering_factor = Units::PI/wavelength/wavelength;
    double alpha_i = sim_element.getAlphaI();
    double phi_i = sim_element.getPhiI();
    cvector_t k_i = Geometry::vecOfLambdaAlphaPhi(wavelength, alpha_i, phi_i).complex();
    WavevectorInfo wavevectors(k_i, Geometry::toComplexVector(sim_element.getMeanKF()), wavelength);

    const std::unique_ptr<const ILayerRTCoefficients> P_in_coeffs(
        mP_specular_info->getInCoefficients(alpha_i, phi_i, wavelength));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(sim_element.getAlphaMean(), sim_element.getPhiMean(),
                                             wavelength));
    for ( auto it: m_ff_infos ) {
        it->mp_ff->setSpecularInfo(P_in_coeffs.get(), P_out_coeffs.get());
        Eigen::Matrix2cd ff_mat = it->mp_ff->evaluatePol(wavevectors);
        m_ff_pol.push_back(wavevector_scattering_factor*ff_mat);
    }
}

void IInterferenceFunctionStrategy::clearFormFactorLists() const
{
    m_ff.clear();
    m_ff_pol.clear();
}

double IInterferenceFunctionStrategy::MCIntegratedEvaluate(
    const SimulationElement& sim_element) const
{
    double min_array[] = {0.0, 0.0};
    double max_array[] = {1.0, 1.0};
    return mP_integrator->integrate(
        min_array, max_array, (void*)&sim_element, m_options.getMcPoints());
}

double IInterferenceFunctionStrategy::MCIntegratedEvaluatePol(
        const SimulationElement& sim_element) const
{
    double min_array[] = {0.0, 0.0};
    double max_array[] = {1.0, 1.0};
    return mP_integrator_pol->integrate(
        min_array, max_array, (void*)&sim_element, m_options.getMcPoints());
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_angles(
    double* fractions, size_t /* dim */, void* params) const
{
    double par0 = fractions[0];
    double par1 = fractions[1];

    SimulationElement* pars = static_cast<SimulationElement*>(params);

    SimulationElement sim_element(*pars, par0, par1);
    calculateFormFactorList(sim_element);
    return pars->getIntegrationFactor(par0, par1) * evaluateForList(sim_element, m_ff);
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_angles_pol(
    double* fractions, size_t /* dim */, void* params) const
{
    double par0 = fractions[0];
    double par1 = fractions[1];

    SimulationElement* pars = static_cast<SimulationElement*>(params);

    SimulationElement sim_element(*pars, par0, par1);
    calculateFormFactorLists(sim_element);
    return pars->getIntegrationFactor(par0, par1) * evaluateForMatrixList(sim_element, m_ff_pol);
}

cvector_t IInterferenceFunctionStrategy::getQ(
    const cvector_t k_i, const Bin1DCVector& k_f_bin) const
{
    return k_i - k_f_bin.getMidPoint();
}
