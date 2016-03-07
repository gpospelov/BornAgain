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
#include "ModelMapper.h"
#include <QDebug>

const QString DetectorItem::P_DETECTOR = "DetectorType";
const QString DetectorItem::T_MASKS = "Mask tag";

DetectorItem::DetectorItem()
    : ParameterizedItem(Constants::DetectorType)
{
    registerGroupProperty(P_DETECTOR, Constants::DetectorGroup);
    registerTag(T_MASKS, 0, -1, QStringList() << Constants::MaskContainerType);
    setDefaultTag(T_MASKS);
    setGroupProperty(P_DETECTOR, Constants::SphericalDetectorType);
    mapper()->setOnPropertyChange(
                [this] (const QString &name)
    {
        if(name == P_DETECTOR) {
            if(ParameterizedItem *maskContainer = getMaskContainerItem()) {
                ParameterizedItem *item = takeChildItem(rowOfChild(maskContainer));
                Q_ASSERT(item == maskContainer);
                delete item;
            }

        }
    });
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

