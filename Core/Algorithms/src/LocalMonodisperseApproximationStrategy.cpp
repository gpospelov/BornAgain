// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/LocalMonodisperseApproximationStrategy.cpp
//! @brief     Implements class LocalMonodisperseApproximationStrategy.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LocalMonodisperseApproximationStrategy.h"
#include "Exceptions.h"
#include "MathFunctions.h"
#include <cassert>


LocalMonodisperseApproximationStrategy::LocalMonodisperseApproximationStrategy(SimulationParameters sim_params)
: IInterferenceFunctionStrategy(sim_params)
{
}

void LocalMonodisperseApproximationStrategy::init(
        const SafePointerVector<FormFactorInfo>& form_factor_infos,
        const SafePointerVector<IInterferenceFunction>& ifs)
{
    IInterferenceFunctionStrategy::init(form_factor_infos, ifs);
    if (!checkVectorSizes()) {
        throw ClassInitializationException("Wrong number of formfactors or interference functions for Local Monodisperse Approximation.");
    }
}

double LocalMonodisperseApproximationStrategy::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const
{
    double intensity = 0.0;
    cvector_t q = getQ(k_i, k_f_bin);
    if (m_sim_params.me_lattice_type==SimulationParameters::LATTICE) {
        complex_t amplitude(0.0, 0.0);
        // double mean_squared_ff =
        // meanSquaredFormFactor(k_i, k_f_bin, alpha_i, alpha_f);
        for (SafePointerVector<FormFactorInfo>::const_iterator it =
                m_ff_infos.begin(); it != m_ff_infos.end(); ++it) {
            double fraction = (*it)->m_abundance;
            complex_t ff = (*it)->mp_ff->evaluate(
                    k_i, k_f_bin, alpha_f_bin);
            complex_t phase = q.x()*(*it)->m_pos_x + q.y()*(*it)->m_pos_y;
            amplitude += fraction*std::abs(ff)
                       * std::exp(complex_t(0.0, 1.0)*phase);
        }
        intensity = std::norm(amplitude)*m_ifs[0]->evaluate(
                k_i-k_f_bin.getMidPoint());
    }
    else {
        for (size_t i=0; i<m_ff_infos.size(); ++i) {
            complex_t ff = m_ff_infos[i]->mp_ff->evaluate(
                    k_i, k_f_bin, alpha_f_bin);
            double itf_function = m_ifs[i]->evaluate(k_i-k_f_bin.getMidPoint());
            double fraction = m_ff_infos[i]->m_abundance;
            intensity += fraction*(itf_function*std::norm(ff));
        }
    }
    assert(!MathFunctions::isnan(intensity));
    assert(!MathFunctions::isinf(intensity));

    return intensity;
}

Eigen::Matrix2d LocalMonodisperseApproximationStrategy::evaluatePol(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin,
        Bin1D alpha_f_bin, Bin1D phi_f_bin) const
{
    Eigen::Matrix2d intensity = Eigen::Matrix2d::Zero();
    cvector_t q = getQ(k_i, k_f_bin);
    if (m_sim_params.me_lattice_type==SimulationParameters::LATTICE) {
        Eigen::Matrix2cd amplitude = Eigen::Matrix2cd::Zero();
        // double mean_squared_ff =
        // meanSquaredFormFactor(k_i, k_f_bin, alpha_i, alpha_f);
        for (SafePointerVector<FormFactorInfo>::const_iterator it =
                m_ff_infos.begin(); it != m_ff_infos.end(); ++it) {
            double fraction = (*it)->m_abundance;
            Eigen::Matrix2cd ff = (*it)->mp_ff->evaluatePol(
                    k_i, k_f_bin, alpha_f_bin, phi_f_bin);
            complex_t phase = q.x()*(*it)->m_pos_x + q.y()*(*it)->m_pos_y;
            amplitude += fraction * std::exp(complex_t(0.0, 1.0)*phase)
                         * MathFunctions::Abs(ff);
        }
        intensity = MathFunctions::Norm(amplitude) * m_ifs[0]->evaluate(
                k_i-k_f_bin.getMidPoint());
    }
    else {
        for (size_t i=0; i<m_ff_infos.size(); ++i) {
            Eigen::Matrix2cd ff = m_ff_infos[i]->mp_ff->evaluatePol(
                    k_i, k_f_bin, alpha_f_bin, phi_f_bin);
            double itf_function = m_ifs[i]->evaluate(k_i-k_f_bin.getMidPoint());
            double fraction = m_ff_infos[i]->m_abundance;
            intensity += fraction * itf_function * MathFunctions::Norm(ff);
        }
    }
    assert(!intensity.hasNaN());

    return intensity;
}

bool LocalMonodisperseApproximationStrategy::checkVectorSizes()
{
    size_t n_ffs = m_ff_infos.size();
    size_t n_ifs = m_ifs.size();
    if (m_sim_params.me_lattice_type==SimulationParameters::LATTICE) {
        return (n_ffs>0 && n_ifs==1);
    }
    return (n_ffs>0 && n_ifs==n_ffs);
}


