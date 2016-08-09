// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleCompositionItem.h
//! @brief     Defines class ParticleCompositionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECOMPOSITIONITEM_H
#define PARTICLECOMPOSITIONITEM_H

#include "SessionGraphicsItem.h"
#include "ParticleComposition.h"


class BA_CORE_API_ ParticleCompositionItem : public SessionGraphicsItem
{

public:
    const static QString T_PARTICLES;
    explicit ParticleCompositionItem();
    virtual ~ParticleCompositionItem() {}
    std::unique_ptr<ParticleComposition> createParticleComposition() const;
};

#endif // PARTICLECOMPOSITIONITEM_H
