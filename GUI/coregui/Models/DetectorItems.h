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

class MaskContainerItem;

class BA_CORE_API_ DetectorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_DETECTOR;
    explicit DetectorItem(ParameterizedItem *parent=0);
    virtual ~DetectorItem(){}

    MaskContainerItem *getMaskContainerItem() const;
};

class SphericalDetectorItem : public ParameterizedItem
{
public:
    static const QString P_PHI_AXIS;
    static const QString P_ALPHA_AXIS;
    static const QString P_RESOLUTION_FUNCTION;
    explicit SphericalDetectorItem(ParameterizedItem *parent=0);
    virtual ~SphericalDetectorItem(){}
};


#endif
