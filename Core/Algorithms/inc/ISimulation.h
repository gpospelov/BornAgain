// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ISimulation.h
//! @brief     Defines interface class ISimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef ISIMULATION_H
#define ISIMULATION_H

#include "ICloneable.h"

//! Interface class, encapsulating different simulations.

class ISimulation : public ICloneable
{
 public:
    virtual ~ISimulation() {}
    ISimulation *clone() const
    {
        throw NotImplementedException("ISimulation::clone() -> "
                                      "Error: not implemented exception.");
    }
    virtual void run() {}
};

#endif // ISIMULATION_H
