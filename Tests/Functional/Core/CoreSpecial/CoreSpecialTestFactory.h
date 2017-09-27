// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/CoreSpecialTestFactory.h
//! @brief     Defines CoreSpecialTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CORESPECIALTESTFACTORY_H
#define CORESPECIALTESTFACTORY_H

#include "FunctionalTestFactory.h"

//! @class CoreSpecialTestFactory
//! @brief Collection of special case for Core library.

class CoreSpecialTestFactory : public FunctionalTestFactory
{
public:
    CoreSpecialTestFactory();
};

#endif
