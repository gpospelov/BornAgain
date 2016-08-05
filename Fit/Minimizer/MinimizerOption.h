// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerOption.h
//! @brief     Declares class MinimizerOption.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZEROPTION_H
#define MINIMIZEROPTION_H

#include "WinDllMacros.h"
#include <variant.hpp>
#include <string>

//! @class MinimizerOption
//! @ingroup fitting_internal
//! @brief The MinimizerOption class is intended to store a single option for minimization
//! algorithm. Relies on https://github.com/mapbox/variant

class BA_CORE_API_ MinimizerOption
{
public:

private:
    std::string m_name;
    std::string m_description;
    mapbox::util::variant<int, double, std::string> m_value;
    mapbox::util::variant<int, double, std::string> m_default_value;
};



#endif

