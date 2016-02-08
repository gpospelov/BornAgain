// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DetectorItem.h
//! @brief     Defines class DetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DETECTOR_ITEMS_H
#define DETECTOR_ITEMS_H

#include "ParameterizedItem.h"
#include "SphericalDetectorItem.h"
#include "RectangularDetectorItem.h"

class MaskContainerItem;

//! DetectorItem, holds masks and either rectangular or spherical detector as sub item
class BA_CORE_API_ DetectorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_DETECTOR;
    explicit DetectorItem(ParameterizedItem *parent=0);
    virtual ~DetectorItem(){}

    MaskContainerItem *getMaskContainerItem() const;

protected slots:
    virtual void onSubItemChanged(const QString &propertyName);

};



#endif
