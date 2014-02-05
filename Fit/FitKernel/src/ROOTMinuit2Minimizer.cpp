// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/ROOTMinuit2Minimizer.cpp
//! @brief     Implements class ROOTMinuit2Minimizer.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ROOTMinuit2Minimizer.h"


ROOTMinuit2Minimizer::ROOTMinuit2Minimizer(const std::string& minimizer_name, const std::string& algo_type)
    : ROOTMinimizer(minimizer_name, algo_type)
{
    m_minuit2_minimizer = new ROOT::Minuit2::Minuit2Minimizer(algo_type.c_str());
    m_root_minimizer = m_minuit2_minimizer;
}


// this function serve as a bridge and propagates MinimizerOptions inside Minuit2Minimizer
void ROOTMinuit2Minimizer::propagateOptions()
{
    ROOTMinimizer::propagateOptions();
}


