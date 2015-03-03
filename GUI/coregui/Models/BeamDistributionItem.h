// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamDistributionItem.h
//! @brief     Defines class BeamDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BEAMDISTRIBUTIONITEM_H
#define BEAMDISTRIBUTIONITEM_H

#include "ParameterizedItem.h"
#include "DistributionItem.h"
class ParameterDistribution;
class IDistribution1D;

//! The BeamDistributionItem handles wavelength, inclination and azimuthal parameter
//! distribution for BeamItem
class BA_CORE_API_ BeamDistributionItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_DISTRIBUTION;
    static const QString P_CACHED_VALUE;
    explicit BeamDistributionItem(const QString name = QString(), ParameterizedItem *parent=0);
    ~BeamDistributionItem(){}
    void onPropertyChange(const QString &name);

    ParameterDistribution *getParameterDistributionForName(const QString &parameter_name);

protected slots:
    void onSubItemChanged(const QString &propertyName);
    void onSubItemPropertyChanged(const QString &property_group, const QString &property_name);

protected:
    virtual IDistribution1D *createDistribution1D();
};

#endif
