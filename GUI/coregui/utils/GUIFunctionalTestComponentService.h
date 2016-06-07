// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/GUIFunctionalTestComponentService.h
//! @brief     Declares class GUIFunctionalTestComponentService.
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

#include "FunctionalTestComponentService.h"

class FunctionalTestInfo;

//! @class GUIFunctionalTestComponentService
//! @ingroup standard_samples
//! @brief Contains all necessary information to compose GUI functional test.

class GUIFunctionalTestComponentService : public FunctionalTestComponentService
{
public:
    GUIFunctionalTestComponentService(const FunctionalTestInfo* info);

    IFunctionalTest* getFunctionalTest() const;
};

#endif
