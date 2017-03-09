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
#include "DetectorItems.h"
#include "SessionModel.h"

const QString DetectorContainerItem::P_DETECTOR = "DetectorType";
const QString DetectorContainerItem::T_MASKS = "Mask tag";

DetectorContainerItem::DetectorContainerItem()
    : SessionItem(Constants::DetectorContainerType)
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

void DetectorContainerItem::clearMasks()
{
    if (auto maskContainer = maskContainerItem())
        delete takeRow(rowOfChild(maskContainer));
}

DetectorItem* DetectorContainerItem::detectorItem() const
{
    DetectorItem* detectorItem = dynamic_cast<DetectorItem*>(
                getGroupItem(P_DETECTOR));
    Q_ASSERT(detectorItem);
    return detectorItem;
}

MaskContainerItem *DetectorContainerItem::maskContainerItem() const
{
    foreach(SessionItem *item, childItems()) {
        if(MaskContainerItem *container = dynamic_cast<MaskContainerItem *>(item)) {
            return container;
        }
    }
    return 0;
}

void DetectorContainerItem::createMaskContainer()
{
    if (!maskContainerItem())
        model()->insertNewItem( Constants::MaskContainerType, this->index());
}

void DetectorContainerItem::importMasks(MaskContainerItem* maskContainer)
{
    clearMasks();

    if(maskContainer)
        model()->copyParameterizedItem(maskContainer, this, DetectorContainerItem::T_MASKS);
}

// --------------------------------------------------------------------------------------------- //

const QString DetectorItem::T_MASKS = "Masks";

DetectorItem::DetectorItem(const QString& modelType)
    : SessionItem(modelType)
{
    registerTag(T_MASKS, 0, -1, QStringList() << Constants::MaskContainerType);
    setDefaultTag(T_MASKS);
}

void DetectorItem::clearMasks()
{
    if (auto maskContainer = maskContainerItem())
        delete takeRow(rowOfChild(maskContainer));
}

MaskContainerItem* DetectorItem::maskContainerItem() const
{
    return dynamic_cast<MaskContainerItem *>(getItem(T_MASKS));
}

void DetectorItem::createMaskContainer()
{
    if (!maskContainerItem())
        model()->insertNewItem(Constants::MaskContainerType, this->index());
}

void DetectorItem::importMasks(MaskContainerItem* maskContainer)
{
    clearMasks();

    if(maskContainer)
        model()->copyParameterizedItem(maskContainer, this, T_MASKS);
}
