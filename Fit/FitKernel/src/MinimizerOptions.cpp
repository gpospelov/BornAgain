// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/MinimizerOptions.cpp
//! @brief     Implement class MinimizerOptions.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerOptions.h"


MinimizerOptions::MinimizerOptions()
    : m_tolerance(0.01)
    , m_precision(-1)
    , m_max_iterations(0)
    , m_max_function_calls(0)
{

}

void MinimizerOptions::setRealValue(const std::string &name, double val)
{
    m_RealOpts[name] = val;
}

void MinimizerOptions::setIntValue(const std::string &name, int val)
{
    m_IntOpts[name] = val;
}

void MinimizerOptions::setNamedValue(const std::string &name, const std::string &val)
{
    m_NamOpts[name] = val;
}
