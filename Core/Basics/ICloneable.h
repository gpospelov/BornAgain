// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/ICloneable.h
//! @brief     Declares the standard mix-in ICloneable.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICLONEABLE_H
#define ICLONEABLE_H

#include "WinDllMacros.h"

//! @class ICloneable
//! @ingroup tools_internal
//! @brief Interface for objects that must not be copied, except by cloning.
//!
//! This virtual base class disables the copy constructor and the operator=
//! in all its child classes.
//! Child classes should provide clone().

class BA_CORE_API_ ICloneable
{
public:
    ICloneable(){}
    ICloneable(const ICloneable&) = delete;
    virtual ~ICloneable() {}

    ICloneable& operator=(const ICloneable&) = delete;

    virtual ICloneable* clone() const = 0;

    //! Used for Python overriding of clone
    virtual void transferToCPP() {}
};

#endif // ICLONEABLE_H
