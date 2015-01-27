// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleLayoutItem.h
//! @brief     Defines class ParticleLayoutItem
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLELAYOUTITEM_H
#define PARTICLELAYOUTITEM_H

#include "ParameterizedGraphicsItem.h"

class BA_CORE_API_ ParticleLayoutItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_APPROX;
    explicit ParticleLayoutItem(ParameterizedItem *parent=0);
    ~ParticleLayoutItem();
};

#endif // PARTICLELAYOUTITEM_H

