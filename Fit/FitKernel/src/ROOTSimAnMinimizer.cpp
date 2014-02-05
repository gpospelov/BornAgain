// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/ROOTSimAnMinimizer.cpp
//! @brief     Implements class ROOTSimAnMinimizer.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ROOTSimAnMinimizer.h"

ROOTSimAnMinimizer::ROOTSimAnMinimizer(const std::string& minimizer_name, const std::string& algo_type)
    : ROOTMinimizer(minimizer_name, algo_type)
{
    m_siman_minimizer = new ROOT::Patch::GSLSimAnMinimizer();
    m_root_minimizer = m_siman_minimizer;
}


// this function serve as a bridge and propagates MinimizerOptions inside GSLSimAnMinimizer
void ROOTSimAnMinimizer::propagateOptions()
{
    ROOTMinimizer::propagateOptions();
}

