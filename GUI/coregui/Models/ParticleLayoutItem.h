// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleLayoutItem.h
//! @brief     Defines class ParticleLayoutItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARTICLELAYOUTITEM_H
#define PARTICLELAYOUTITEM_H

#include "SessionGraphicsItem.h"

class BA_CORE_API_ ParticleLayoutItem : public SessionGraphicsItem
{
public:
    static const QString P_APPROX;
    static const QString P_TOTAL_DENSITY;
    static const QString T_PARTICLES;
    static const QString T_INTERFERENCE;
    ParticleLayoutItem();

private:
    void updateDensityAppearance(SessionItem* item);
};

#endif // PARTICLELAYOUTITEM_H
