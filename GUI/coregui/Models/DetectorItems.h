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

#include "SessionItem.h"

class MaskContainerItem;
class IDetector2D;
class IResolutionFunction2D;

//! DetectorItem, holds masks and either rectangular or spherical detector as sub item
class BA_CORE_API_ DetectorContainerItem : public SessionItem
{
public:
    static const QString P_DETECTOR;
    static const QString T_MASKS;
    DetectorContainerItem();
    virtual ~DetectorContainerItem(){}

    void clearMasks();

    MaskContainerItem *maskContainerItem() const;
};

class BA_CORE_API_ DetectorItem : public SessionItem
{
public:
    static const QString T_MASKS;
    explicit DetectorItem(const QString& modelType);

    virtual std::unique_ptr<IDetector2D> createDetector() const = 0;
    virtual std::unique_ptr<IResolutionFunction2D> createResolutionFunction() = 0;

    virtual void setSize(int nx, int ny) = 0;
};


#endif // DETECTORITEMS_H
