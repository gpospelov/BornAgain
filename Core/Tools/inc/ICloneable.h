// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/ICloneable.h
//! @brief     Defines the standard mix-in ICloneable.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef ICLONEABLE_H
#define ICLONEABLE_H

#include "Exceptions.h"

//! Standard mix-in for objects that must not be copied, except by cloning.

//! This virtual base class disables the copy constructor and the operator=
//! in all its child classes.
//! Child classes should provide clone().

class ICloneable
{
 public:
    ICloneable(){}
    virtual ~ICloneable() {}
    virtual ICloneable *clone() const = 0;

 private:
    ICloneable(const ICloneable& ) { throw NotImplementedException(
        "ICloneable(const ICloneable& ) -> Error: not implemented."); }
    ICloneable& operator=(const ICloneable& ) { throw NotImplementedException(
        "ICloneable& operator=(const ICloneable& ) -> Error: not implemented."); }
};

#endif // ICLONEABLE_H
