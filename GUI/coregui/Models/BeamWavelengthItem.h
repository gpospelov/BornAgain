// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamWavelengthItem.h
//! @brief     Defines class BeamWavelengthItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BEAMWAVELENGTHITEM_H
#define BEAMWAVELENGTHITEM_H

#include "WinDllMacros.h"
#include "BeamDistributionItem.h"

class BA_CORE_API_ BeamWavelengthItem : public BeamDistributionItem
{

public:
    explicit BeamWavelengthItem();
    virtual ~BeamWavelengthItem(){}
};

#endif
