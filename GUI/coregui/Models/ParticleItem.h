// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleItem.h
//! @brief     Defines class ParticleItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEITEM_H
#define PARTICLEITEM_H

#include "Particle.h"
#include "ParameterizedGraphicsItem.h"

#include <memory>

class BA_CORE_API_ ParticleItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_FORM_FACTOR;
    static const QString P_ABUNDANCE;
    static const QString P_MATERIAL;
    static const QString P_POSITION;
    explicit ParticleItem(ParameterizedItem *parent=0);
    virtual ~ParticleItem() {}
    virtual void insertChildItem(int row, ParameterizedItem *item);
    virtual void onPropertyChange(const QString &name);
    std::unique_ptr<Particle> createParticle() const;
};

#endif // PARTICLEITEM_H
