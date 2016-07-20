// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IRoughness.h
//! @brief     Declares interface class IRoughness.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IROUGHNESS_H
#define IROUGHNESS_H

#include "ISample.h" // inheriting from

//! @class IRoughness
//! @ingroup samples_internal
//! @brief Interface to equip an interface with a roughness.

class BA_CORE_API_ IRoughness : public ISample
{
public:
    IRoughness() {}
    virtual ~IRoughness() {}
    virtual void accept(ISampleVisitor *visitor) const;
};

#endif // IROUGHNESS_H
