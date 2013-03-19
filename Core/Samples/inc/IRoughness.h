// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/IRoughness.h
//! @brief     Defines class IRoughness.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef IROUGHNESS_H
#define IROUGHNESS_H

#include "ISample.h"

//! Roughness interface

class IRoughness : public ISample
{
public:
    IRoughness() { }
    virtual ~IRoughness() { }
};

#endif // IROUGHNESS_H
