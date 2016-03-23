// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamAngleItems.h
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

#ifndef BEAMANGLEITEM_H
#define BEAMANGLEITEM_H

#include "WinDllMacros.h"
#include "BeamDistributionItem.h"

class BA_CORE_API_ BeamAzimuthalAngleItem : public BeamDistributionItem
{
public:
    explicit BeamAzimuthalAngleItem();
    virtual ~BeamAzimuthalAngleItem(){}
protected:
    virtual std::unique_ptr<IDistribution1D> createDistribution1D();
};

class BA_CORE_API_ BeamInclinationAngleItem : public BeamDistributionItem
{
public:
    explicit BeamInclinationAngleItem();
    virtual ~BeamInclinationAngleItem(){}
    virtual std::unique_ptr<IDistribution1D> createDistribution1D();
};

class BA_CORE_API_ BeamAngleHelper
{
public:
    static std::unique_ptr<IDistribution1D> creatAngleDistribution(
            DistributionItem *distributionItem);
};


#endif
