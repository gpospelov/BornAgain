// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DetectorItem.cpp
//! @brief     Implements class DetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DetectorItems.h"
#include "AngleProperty.h"
#include "MaskItems.h"
#include <QDebug>

const QString DetectorItem::P_DETECTOR = "DetectorType";

DetectorItem::DetectorItem()
    : ParameterizedItem(Constants::DetectorType)
{
    registerGroupProperty(P_DETECTOR, Constants::DetectorGroup);
    addToValidChildren(Constants::MaskContainerType);
    setGroupProperty(P_DETECTOR, Constants::SphericalDetectorType);
}

MaskContainerItem *DetectorItem::getMaskContainerItem() const
{
    foreach(ParameterizedItem *item, childItems()) {
        if(MaskContainerItem *container = dynamic_cast<MaskContainerItem *>(item)) {
            return container;
        }
    }
    return 0;
}

void DetectorItem::onSubItemChanged(const QString &propertyName)
{
    if(propertyName == P_DETECTOR) {
        if(ParameterizedItem *maskContainer = getMaskContainerItem()) {
            ParameterizedItem *item = takeChildItem(rowOfChild(maskContainer));
            Q_ASSERT(item == maskContainer);
            delete item;
        }

    }
    ParameterizedItem::onSubItemChanged(propertyName);
}


