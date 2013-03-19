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
//! @file      Algorithms/ISimulation.h 
//! @brief     Defines class ISimulation.
//
// ************************************************************************** //

#ifndef ISIMULATION_H
#define ISIMULATION_H

#include "ICloneable.h"

class ISimulation : public ICloneable
{
public:
    virtual ~ISimulation() { }
    ISimulation *clone() const { throw NotImplementedException("ISimulation::clone() -> Error: not implemented exception."); }
    virtual void run() { }
};

#endif // ISIMULATION_H
