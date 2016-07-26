// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/MinimizerOptions.cpp
//! @brief     Implement class MinimizerOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerOptions.h"

MinimizerOptions::MinimizerOptions()
    : m_tolerance(0.01)
    , m_precision(-1)
    , m_max_iterations(0)
    , m_max_function_calls(0)
    , m_print_level(0)
{
}

void MinimizerOptions::print_common(std::ostream & os) const
{
    os << std::setw(24) << std::left << "Tolerance " << " : " << std::setw(15) << m_tolerance << std::endl;
    os << std::setw(24) << std::left << "Precision " << " : " << std::setw(15) << m_precision << std::endl;
    os << std::setw(24) << std::left << "MaxIterations " << " : " << std::setw(15) << m_max_iterations << std::endl;
    os << std::setw(24) << std::left << "MaxFunctionCalls " << " : " << std::setw(15) << m_max_function_calls << std::endl;
    os << std::setw(24) << std::left << "PrintLevel " << " : " << std::setw(15) << m_print_level << std::endl;
}
