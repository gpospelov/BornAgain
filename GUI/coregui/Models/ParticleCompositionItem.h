// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleCompositionItem.h
//! @brief     Defines class ParticleCompositionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECOMPOSITIONITEM_H
#define PARTICLECOMPOSITIONITEM_H

#include "ParticleComposition.h"
#include "SessionGraphicsItem.h"

#include <QStringList>
#include <memory>

class BA_CORE_API_ ParticleCompositionItem : public SessionGraphicsItem
{

public:
    const static QString T_PARTICLES;
    const static QString T_TRANSFORMATION;
    explicit ParticleCompositionItem();
    virtual ~ParticleCompositionItem() {}
    std::unique_ptr<ParticleComposition> createParticleComposition() const;
};

#endif // PARTICLECOMPOSITIONITEM_H
