// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/Configurable.h
//! @brief     Declares class Configurable.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CONFIGURABLE_H
#define CONFIGURABLE_H

#include "WinDllMacros.h"
#include "MinimizerOption.h"
#include <map>

class BA_CORE_API_ Configurable {

public:

//    void addOption(std::string &optionName, );

private:
    std::vector<MinimizerOption> m_options;

};

#endif
