// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootWrapper/ROOTMinuit2Minimizer.cpp
//! @brief     Implements class ROOTMinuit2Minimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ROOTMinuit2Minimizer.h"
#include <string>

ROOTMinuit2Minimizer::ROOTMinuit2Minimizer(const std::string& minimizer_name, const std::string& algo_type)
    : ROOTMinimizer(minimizer_name, algo_type)
{
    m_minuit2_minimizer = new BA_ROOT::Minuit2::Minuit2Minimizer(algo_type.c_str());
    m_root_minimizer = m_minuit2_minimizer;

    m_options.addValue("Strategy", 1);
    m_options.addValue("ErrorDef", 1);

//    addOption(std::string("xxx"), 1.0);

}


bool ROOTMinuit2Minimizer::isGradientBasedAgorithm()
{
    if(m_algo_type == "Fumili") return true;
    return false;
}


// this function serve as a bridge and propagates MinimizerOptions inside Minuit2Minimizer
void ROOTMinuit2Minimizer::propagateOptions()
{
    ROOTMinimizer::propagateOptions();
    m_minuit2_minimizer->SetStrategy(m_options.getIntValue("Strategy"));
    m_minuit2_minimizer->SetErrorDef(m_options.getIntValue("ErrorDef"));
}


