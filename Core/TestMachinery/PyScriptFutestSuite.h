// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/PyScriptFutestSuite.h
//! @brief     Declares class PyScriptFutestSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYSCRIPTFUNCTIONALTESTCOMPONENTSERVICE_H
#define PYSCRIPTFUNCTIONALTESTCOMPONENTSERVICE_H

#include "FutestSuite.h"

class FunctionalTestInfo;

//! @class PyScriptFutestSuite
//! @ingroup standard_samples
//! @brief Contains all necessary information to compose pyscript functional test.

class BA_CORE_API_ PyScriptFutestSuite : public FutestSuite
{
public:
    PyScriptFutestSuite(const FunctionalTestInfo* info);

    IFunctionalTest* getFunctionalTest() const;
};

#endif
