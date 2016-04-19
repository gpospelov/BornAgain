// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DetectorItems.h
//! @brief     Declares classes DetectorItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DETECTOR_ITEMS_H
#define DETECTOR_ITEMS_H

#include "SessionItem.h"
#include "SphericalDetectorItem.h"
#include "RectangularDetectorItem.h"

class MaskContainerItem;

//! DetectorItem, holds masks and either rectangular or spherical detector as sub item
class BA_CORE_API_ DetectorItem : public SessionItem
{

public:
    static const QString P_DETECTOR;
    static const QString T_MASKS;
    explicit DetectorItem();
    virtual ~DetectorItem(){}

    MaskContainerItem *getMaskContainerItem() const;


};



#endif
