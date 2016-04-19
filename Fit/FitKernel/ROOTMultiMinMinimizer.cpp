// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/ROOTMultiMinMinimizer.cpp
//! @brief     Implements class ROOTMultiMinMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ROOTMultiMinMinimizer.h"


ROOTMultiMinMinimizer::ROOTMultiMinMinimizer(const std::string& minimizer_name, const std::string& algo_type)
    : ROOTMinimizer(minimizer_name, algo_type)
{
    m_gsl_minimizer = new BA_ROOT::Math::GSLMinimizer(algo_type.c_str());
    m_root_minimizer = m_gsl_minimizer;
}


// this function serve as a bridge and propagates MinimizerOptions inside Minuit2Minimizer
void ROOTMultiMinMinimizer::propagateOptions()
{
    ROOTMinimizer::propagateOptions();
}


