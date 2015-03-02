// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamAngleItem.h
//! @brief     Defines class BeamAngleItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BEAMANGLEITEM_H
#define BEAMANGLEITEM_H

#include "WinDllMacros.h"
#include "BeamDistributionItem.h"

class BA_CORE_API_ BeamAzimuthalAngleItem : public BeamDistributionItem
{
    Q_OBJECT
public:
    explicit BeamAzimuthalAngleItem(ParameterizedItem *parent=0);
    ~BeamAzimuthalAngleItem(){}
};

class BA_CORE_API_ BeamInclinationAngleItem : public BeamDistributionItem
{
    Q_OBJECT
public:
    explicit BeamInclinationAngleItem(ParameterizedItem *parent=0);
    ~BeamInclinationAngleItem(){}
};

#endif
