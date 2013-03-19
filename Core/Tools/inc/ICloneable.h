// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Tools/ICloneable.h 
//! @brief     Defines virtual class ICloneable.
//
// ************************************************************************** //

#ifndef ICLONEABLE_H
#define ICLONEABLE_H

#include "Exceptions.h"

//! Disable copy constructor and = operator; child classes must provide clone().

class ICloneable
{
public:
    ICloneable(){}
    virtual ~ICloneable() {}
    virtual ICloneable *clone() const = 0;

private:
    ICloneable(const ICloneable &) { throw NotImplementedException("ICloneable(const ICloneable &) -> Error: not implemented."); }
    ICloneable &operator=(const ICloneable &) { throw NotImplementedException("ICloneable &operator=(const ICloneable &) -> Error: not implemented."); }
};

#endif // ICLONEABLE_H
