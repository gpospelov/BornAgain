// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamDistributionItem.h
//! @brief     Defines class BeamDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef BEAMDISTRIBUTIONITEM_H
#define BEAMDISTRIBUTIONITEM_H

#include "DistributionItems.h"

class ParameterDistribution;

//! The BeamDistributionItem handles wavelength, inclination and azimuthal parameter
//! distribution for BeamItem

class BA_CORE_API_ BeamDistributionItem : public SessionItem
{
public:
    static const QString P_DISTRIBUTION;
    explicit BeamDistributionItem(const QString& name);

    std::unique_ptr<ParameterDistribution> getParameterDistributionForName(
            const std::string &parameter_name);

    virtual double meanValue() const;

protected:
    virtual double scaleFactor() const;
    void register_distribution_group();
    void initDistributionItem();

    virtual std::unique_ptr<IDistribution1D> createDistribution1D() const;
};

#endif // BEAMDISTRIBUTIONITEM_H
