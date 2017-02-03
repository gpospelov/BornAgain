// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleDistributionItem.h
//! @brief     Defines class ParticleDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEDISTRIBUTIONITEM_H
#define PARTICLEDISTRIBUTIONITEM_H

#include "SessionGraphicsItem.h"
#include "ParticleDistribution.h"

class BA_CORE_API_ ParticleDistributionItem : public SessionGraphicsItem
{
public:
    static const QString P_DISTRIBUTED_PARAMETER;
    static const QString P_DISTRIBUTION;
    static const QString NO_SELECTION;
    static const QString T_PARTICLES;
    ParticleDistributionItem();
    virtual ~ParticleDistributionItem();

    std::unique_ptr<ParticleDistribution> createParticleDistribution() const;
    QString translateParameterNameToGUI(const QString& par_name);
    QString translateParameterNameToGUI_V2(const QString& par_name);

    void updateParameterList();

private:
    QStringList childParameterNames() const;
};

#endif // PARTICLEDISTRIBUTIONITEM_H

