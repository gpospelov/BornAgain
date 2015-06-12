// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IComponentLocator.h
//! @brief     Defines interface IComponentLocator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOMPONENTLOCATOR_H
#define ICOMPONENTLOCATOR_H

#include "WinDllMacros.h"

class IFormFactor;

//! @class IComponentLocator
//! @ingroup simulation_internal
//! @brief Interface to the class which provides client with objects he needs

class BA_CORE_API_ IComponentLocator
{
public:
    virtual IFormFactor *getFormFactor() { return 0;}

};


#endif /* ICOMPONENTLOCATOR_H */
