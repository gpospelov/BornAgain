// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/CoreFunctionalTestComponentService.h
//! @brief     Declares class CoreFunctionalTestComponentService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COREFUNCTIONALTESTCOMPONENTSERVICE_H
#define COREFUNCTIONALTESTCOMPONENTSERVICE_H

#include "FunctionalTestComponentService.h"

class FunctionalTestInfo;

//! @class CoreFunctionalTestComponentService
//! @ingroup standard_samples
//! @brief Contains all necessary information to compose core functional test.

class CoreFunctionalTestComponentService : public FunctionalTestComponentService
{
public:
    CoreFunctionalTestComponentService(const FunctionalTestInfo &info);

    IFunctionalTest *getFunctionalTest() const;
};

#endif
