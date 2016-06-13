// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/ROOTLMAMinimizer.cpp
//! @brief     Implements class ROOTLMAMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ROOTLMAMinimizer.h"
#include "Math/GenAlgoOptions.h"


ROOTLMAMinimizer::ROOTLMAMinimizer(const std::string& minimizer_name, const std::string& algo_type)
  : ROOTMinimizer(minimizer_name, algo_type)
{
//    m_lma_minimizer = new ROOT::Patch::GSLNLSMinimizer(2);
    m_lma_minimizer = new BA_ROOT::Math::GSLNLSMinimizer(2);
    m_root_minimizer = m_lma_minimizer;
}

// this function serve as a bridge and propagates MinimizerOptions inside GSLNLSMinimizer
void ROOTLMAMinimizer::propagateOptions()
{
    ROOTMinimizer::propagateOptions();
}

