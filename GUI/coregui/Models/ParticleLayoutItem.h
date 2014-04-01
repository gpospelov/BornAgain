// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/ParticleLayoutItem.h
//! @brief     Defines class ParticleLayoutItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLELAYOUTITEM_H
#define PARTICLELAYOUTITEM_H

#include "ParameterizedGraphicsItem.h"

class ParticleLayoutItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    explicit ParticleLayoutItem(ParameterizedItem *parent=0);
    ~ParticleLayoutItem();
};

#endif // PARTICLELAYOUTITEM_H

