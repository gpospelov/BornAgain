// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleLayoutItem.h
//! @brief     Defines class ParticleLayoutItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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
    static const QString P_TOTAL_DENSITY;
    static const QString T_PARTICLES;
    static const QString T_TRANSFORMATION;
    explicit ParticleLayoutItem();
    virtual ~ParticleLayoutItem();
};

#endif // PARTICLELAYOUTITEM_H
