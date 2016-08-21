// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FormFactorInfo.h
//! @brief     Defines class FormFactorInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORINFO_H
#define FORMFACTORINFO_H

#include "ICloneable.h"
class IFormFactor;

//! Information about particle position and abundance.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorInfo : public ICloneable
{
public:
    FormFactorInfo(IFormFactor* ff, double abundance)
        : mp_ff(ff), m_abundance(abundance) {}
    virtual ~FormFactorInfo();
    virtual FormFactorInfo* clone() const;
    IFormFactor* mp_ff;
    double m_abundance;
};

#endif // FORMFACTORINFO_H
