// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamAngleItems.h
//! @brief     Defines class BeamAngleItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef BEAMANGLEITEMS_H
#define BEAMANGLEITEMS_H

#include "BeamDistributionItem.h"

class BA_CORE_API_ BeamAzimuthalAngleItem : public BeamDistributionItem
{
public:
    BeamAzimuthalAngleItem();

    double azimuthalAngle() const;

protected:
    virtual std::unique_ptr<IDistribution1D> createDistribution1D() const override;
};

class BA_CORE_API_ BeamInclinationAngleItem : public BeamDistributionItem
{
public:
    BeamInclinationAngleItem();

    double inclinationAngle() const;

protected:
    virtual std::unique_ptr<IDistribution1D> createDistribution1D() const override;
};

#endif // BEAMANGLEITEMS_H
