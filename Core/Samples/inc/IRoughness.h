// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/IRoughness.h
//! @brief     Defines interface class IRoughness.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IROUGHNESS_H
#define IROUGHNESS_H

#include "ISample.h"

//! Interface to equip a sample with a roughness.

class BA_CORE_API_ IRoughness : public ISample
{
public:
    IRoughness() {}
    virtual ~IRoughness() {}
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }
};

#endif // IROUGHNESS_H


