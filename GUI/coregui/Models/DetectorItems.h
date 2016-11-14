// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DetectorItems.h
//! @brief     Defines classes DetectorItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DETECTORITEMS_H
#define DETECTORITEMS_H

#include "RectangularDetectorItem.h"
#include "SphericalDetectorItem.h"

class MaskContainerItem;

//! DetectorItem, holds masks and either rectangular or spherical detector as sub item
class BA_CORE_API_ DetectorItem : public SessionItem
{
public:
    static const QString P_DETECTOR;
    static const QString T_MASKS;
    explicit DetectorItem();
    virtual ~DetectorItem(){}

    MaskContainerItem *maskContainerItem() const;
};

#endif // DETECTORITEMS_H
