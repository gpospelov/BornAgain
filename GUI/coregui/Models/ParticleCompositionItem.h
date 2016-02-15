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
#include "ParameterizedGraphicsItem.h"

#include <QStringList>
#include <memory>

class BA_CORE_API_ ParticleCompositionItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    explicit ParticleCompositionItem(ParameterizedItem *parent=0);
    virtual ~ParticleCompositionItem() {}
    virtual void insertChildItem(int row, ParameterizedItem *item);
    virtual void onPropertyChange(const QString &name);
    std::unique_ptr<ParticleComposition> createParticleComposition() const;
};

#endif // PARTICLECOMPOSITIONITEM_H
