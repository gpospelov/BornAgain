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
class ParameterDistribution;


//! The BeamDistributionItem handles wavelength, inclination and azimuthal parameter
//! distribution for BeamItem
class BA_CORE_API_ BeamDistributionItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_DISTRIBUTION;
    static const QString P_CACHED_VALUE;
    explicit BeamDistributionItem(ParameterizedItem *parent=0);
    ~BeamDistributionItem(){}
    void onPropertyChange(const QString &name);

    void setInitialValue(double value, const PropertyAttribute &attribute);

    ParameterDistribution *getParameterDistributionForName(const QString &parameter_name, bool clever_alpha_invert_flag = false);

protected slots:
    void onSubItemChanged(const QString &propertyName);
    void onSubItemPropertyChanged(const QString &property_group, const QString &property_name);
};

#endif
