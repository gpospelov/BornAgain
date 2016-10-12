// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/WeightedFormFactor.h
//! @brief     Defines class WeightedFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef WEIGHTEDFORMFACTOR_H
#define WEIGHTEDFORMFACTOR_H

#include "ICloneable.h"
class IFormFactor;

//! Information about particle form factor and abundance.
//! @ingroup formfactors_internal

class BA_CORE_API_ WeightedFormFactor : public ICloneable
{
public:
    WeightedFormFactor(IFormFactor* ff, double abundance)
        : mp_ff(ff), m_abundance(abundance) {}
    virtual ~WeightedFormFactor();
    virtual WeightedFormFactor* clone() const;
    IFormFactor* mp_ff;
    double m_abundance;
};

#endif // WEIGHTEDFORMFACTOR_H
