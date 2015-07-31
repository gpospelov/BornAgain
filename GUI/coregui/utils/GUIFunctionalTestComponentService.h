// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/GUIFunctionalTestComponentService.h
//! @brief     Defines class GUIFunctionalTestComponentService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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
    GUIFunctionalTestComponentService(const FunctionalTestInfo &info);

    IFunctionalTest *getFunctionalTest() const;
};

#endif

