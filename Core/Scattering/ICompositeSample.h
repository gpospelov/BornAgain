// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/ICompositeSample.h
//! @brief     Defines interface class ICompositeSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOMPOSITESAMPLE_H
#define ICOMPOSITESAMPLE_H

#include "ISample.h"

//! Pure virtual base class for tree-like composite samples.
//!
//! Inherited by IAbstractParticle, IClusteredParticle, ILayout, ILayer, IMultiLayer.
//!
//! @ingroup samples_internal

class BA_CORE_API_ ICompositeSample : public ISample
{
public:
    ICompositeSample() {}
    virtual ~ICompositeSample(){}
};

#endif // ICOMPOSITESAMPLE_H
