// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleDistributionItem.h
//! @brief     Defines class ParticleDistributionItem
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEDISTRIBUTIONITEM_H
#define PARTICLEDISTRIBUTIONITEM_H

#include "ParameterizedGraphicsItem.h"

#include <QStringList>

class BA_CORE_API_ ParticleDistributionItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_DISTRIBUTED_PARAMETER;
    static const QString P_DISTRIBUTION;
    static const QString P_SAMPLE_NUMBER;
    static const QString P_SIGMA_FACTOR;
    static const QString P_CACHED_SELECTED_PARAMETER;
    explicit ParticleDistributionItem(ParameterizedItem *parent=0);
    ~ParticleDistributionItem();

    void onPropertyChange(const QString &name);

    void onChildPropertyChange();
public slots:
    void updateParameterList();
private:
    static const QString NO_SELECTION;
};

#endif // PARTICLEDISTRIBUTIONITEM_H

