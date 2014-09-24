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


LocalMonodisperseApproximationStrategy::LocalMonodisperseApproximationStrategy(
        SimulationParameters sim_params)
: IInterferenceFunctionStrategy(sim_params)
{
}

void LocalMonodisperseApproximationStrategy::init(
        const SafePointerVector<FormFactorInfo>& form_factor_infos,
        const SafePointerVector<IInterferenceFunction>& ifs)
{
    IInterferenceFunctionStrategy::init(form_factor_infos, ifs);
    if (!checkVectorSizes()) {
        throw ClassInitializationException("Wrong number of formfactors or"
            " interference functions for Local Monodisperse Approximation.");
    }
}

double LocalMonodisperseApproximationStrategy::evaluateForList(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin,
        const std::vector<complex_t> &ff_list) const
{
    double intensity = 0.0;
    cvector_t q = getQ(k_i, k_f_bin);
    if (m_sim_params.me_lattice_type==SimulationParameters::LATTICE) {
        complex_t amplitude(0.0, 0.0);
        // double mean_squared_ff =
        // meanSquaredFormFactor(k_i, k_f_bin, alpha_i, alpha_f);
        for (size_t i=0; i<m_ff_infos.size(); ++i) {
            double fraction = m_ff_infos[i]->m_abundance;
            complex_t ff = ff_list[i];
            complex_t phase = q.x()*m_ff_infos[i]->m_pos_x
                            + q.y()*m_ff_infos[i]->m_pos_y;
            amplitude += fraction*std::abs(ff)
                       * std::exp(complex_t(0.0, 1.0)*phase);
        }
        intensity = std::norm(amplitude)*m_ifs[0]->evaluate(
                k_i-k_f_bin.getMidPoint());
    }
    else {
        for (size_t i=0; i<m_ff_infos.size(); ++i) {
            complex_t ff = ff_list[i];
            double itf_function = m_ifs[i]->evaluate(k_i-k_f_bin.getMidPoint());
            double fraction = m_ff_infos[i]->m_abundance;
            intensity += fraction*(itf_function*std::norm(ff));
        }
    }
    assert(!MathFunctions::isnan(intensity));
    assert(!MathFunctions::isinf(intensity));

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


