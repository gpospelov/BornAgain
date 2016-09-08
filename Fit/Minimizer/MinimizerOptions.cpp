// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerOptions.cpp
//! @brief     Implements class MinimizerOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerOptions.h"
#include <sstream>

std::string MinimizerOptions::toOptionString(const std::string &delimeter) const
{
    std::ostringstream result;
    for(auto option: m_options) {
        result << option->name() << std::string("=") << option->value() << delimeter;
    }
    return result.str();
}

