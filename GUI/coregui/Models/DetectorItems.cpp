// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DetectorItems.cpp
//! @brief     Implements classes DetectorItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "DetectorItems.h"
#include "MaskItems.h"

const QString DetectorItem::P_DETECTOR = "DetectorType";
const QString DetectorItem::T_MASKS = "Mask tag";

DetectorItem::DetectorItem()
    : SessionItem(Constants::DetectorType)
{
    addGroupProperty(P_DETECTOR, Constants::DetectorGroup);
    registerTag(T_MASKS, 0, -1, QStringList() << Constants::MaskContainerType);
    setDefaultTag(T_MASKS);
    setGroupProperty(P_DETECTOR, Constants::SphericalDetectorType);
    mapper()->setOnPropertyChange(
                [this] (const QString &name)
    {
        if(name == P_DETECTOR) {
            if(SessionItem *maskContainer = maskContainerItem()) {
                SessionItem *item = takeRow(rowOfChild(maskContainer));
                Q_ASSERT(item == maskContainer);
                delete item;
            }

        }
    });
}

MaskContainerItem *DetectorItem::maskContainerItem() const
{
    foreach(SessionItem *item, childItems()) {
        if(MaskContainerItem *container = dynamic_cast<MaskContainerItem *>(item)) {
            return container;
        }
    }
    return 0;
}

