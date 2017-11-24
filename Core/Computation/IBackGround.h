// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IBackGround.h
//! @brief     Defines interface IBackGround.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IBACKGROUND_H
#define IBACKGROUND_H

#include "ICloneable.h"
#include <vector>

class SimulationElement;

//! Interface for a simulating the background signal
//!
//! @ingroup algorithms_internal

class IBackGround : public ICloneable
{
public:
    virtual ~IBackGround();
    virtual IBackGround* clone() const =0;

    virtual void addBackGround(std::vector<SimulationElement>::iterator start,
                               std::vector<SimulationElement>::iterator end) const =0;
};

#endif // IBACKGROUND_H
