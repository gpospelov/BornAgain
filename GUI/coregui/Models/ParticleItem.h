// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleItem.h
//! @brief     Defines class ParticleItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEITEM_H
#define PARTICLEITEM_H

#include "SessionGraphicsItem.h"

class Particle;

class BA_CORE_API_ ParticleItem : public SessionGraphicsItem
{
public:
    static const QString P_FORM_FACTOR;
    static const QString P_ABUNDANCE;
    static const QString P_MATERIAL;
    static const QString P_POSITION;
    static const QString T_TRANSFORMATION;

    ParticleItem();

    std::unique_ptr<Particle> createParticle() const;

private:
    void updatePropertiesAppearance(SessionItem* parentItem);
};

#endif // PARTICLEITEM_H
