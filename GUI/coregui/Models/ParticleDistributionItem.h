// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/ParticleDistributionItem.h
//! @brief     Defines class ParticleDistributionItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEDISTRIBUTIONITEM_H
#define PARTICLEDISTRIBUTIONITEM_H

#include "ParameterizedGraphicsItem.h"

class BA_CORE_API_ ParticleDistributionItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_PARAMETER_NAME;
    explicit ParticleDistributionItem(ParameterizedItem *parent=0);
    ~ParticleDistributionItem();
};

#endif // PARTICLEDISTRIBUTIONITEM_H

