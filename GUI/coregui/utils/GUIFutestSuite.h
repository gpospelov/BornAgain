// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/GUIFutestSuite.h
//! @brief     Declares class GUIFutestSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GUIFUNCTIONALTESTCOMPONENTSERVICE_H
#define GUIFUNCTIONALTESTCOMPONENTSERVICE_H

#include "FutestSuite.h"

class FunctionalTestInfo;

//! @class GUIFutestSuite
//! @ingroup standard_samples
//! @brief Contains all necessary information to compose GUI functional test.

class BA_CORE_API_ GUIFutestSuite : public FutestSuite
{
public:
    GUIFutestSuite(const FunctionalTestInfo* info);

    IFunctionalTest* getFunctionalTest() const;
};

#endif
