// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/ROOTSimAnMinimizer.cpp
//! @brief     Implements class ROOTSimAnMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ROOTSimAnMinimizer.h"

ROOTSimAnMinimizer::ROOTSimAnMinimizer(const std::string& minimizer_name, const std::string& algo_type)
    : ROOTMinimizer(minimizer_name, algo_type)
{
//    m_siman_minimizer = new ROOT::Patch::GSLSimAnMinimizer();
    m_siman_minimizer = new BA_ROOT::Math::GSLSimAnMinimizer();
    m_root_minimizer = m_siman_minimizer;

    m_options.addValue("ntries", 100);
    m_options.addValue("niters_fixed_t", 10);
    m_options.addValue("step_size", 1.0);
    m_options.addValue("k", 1.0);
    m_options.addValue("t_initial", 50.0);
    m_options.addValue("mu", 1.05);
    m_options.addValue("t_min", 0.1);
    m_options.setMaxIterations(100);
}


// this function serve as a bridge and propagates MinimizerOptions inside GSLSimAnMinimizer
void ROOTSimAnMinimizer::propagateOptions()
{
    ROOTMinimizer::propagateOptions();

    BA_ROOT::Math::GSLSimAnParams& pars = m_siman_minimizer->getSolver().Params();
    m_options.getValue("ntries", pars.n_tries);
    m_options.getValue("niters_fixed_t", pars.iters_fixed_T);
    m_options.getValue("step_size", pars.step_size);
    m_options.getValue("k", pars.k);
    m_options.getValue("t_initial", pars.t_initial);
    m_options.getValue("mu", pars.mu);
    m_options.getValue("t_min", pars.t_min);
}
