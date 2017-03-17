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
#include "IDetector2D.h"
#include "ResolutionFunctionItems.h"
#include "ResolutionFunction2DGaussian.h"

const QString DetectorItem::T_MASKS = "Mask tag";
const QString DetectorItem::P_RESOLUTION_FUNCTION = "Type";

DetectorItem::DetectorItem(const QString& modelType) : SessionItem(modelType)
{
    registerTag(T_MASKS, 0, -1, QStringList() << Constants::MaskContainerType);
    setDefaultTag(T_MASKS);
}

std::unique_ptr<IDetector2D> DetectorItem::createDetector() const
{
    auto result = createDomainDetector();
    addMasksToDomain(result.get());

    if (auto resFunc = createResolutionFunction())
        result->setResolutionFunction(*resFunc);

    return result;
}

void DetectorItem::clearMasks()
{
    if (auto maskContainer = maskContainerItem())
        delete takeRow(rowOfChild(maskContainer));
}

MaskContainerItem* DetectorItem::maskContainerItem() const
{
    return dynamic_cast<MaskContainerItem*>(getItem(T_MASKS));
}

void DetectorItem::createMaskContainer()
{
    if (!maskContainerItem())
        model()->insertNewItem(Constants::MaskContainerType, this->index());
}

void DetectorItem::importMasks(MaskContainerItem* maskContainer)
{
    clearMasks();

    if (maskContainer)
        model()->copyParameterizedItem(maskContainer, this, T_MASKS);
}

void DetectorItem::register_resolution_function()
{
    addGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionGroup);
}

std::unique_ptr<IResolutionFunction2D> DetectorItem::createResolutionFunction() const
{
    auto resfuncItem
        = dynamic_cast<ResolutionFunctionItem*>(getGroupItem(DetectorItem::P_RESOLUTION_FUNCTION));
    Q_ASSERT(resfuncItem);

    return resfuncItem->createResolutionFunction(axesToDomainUnitsFactor());
}

void DetectorItem::addMasksToDomain(IDetector2D* detector) const
{
    auto maskContainer = maskContainerItem();

    if (!maskContainer)
        return;

    const double scale = axesToDomainUnitsFactor();

    for (int i_row = maskContainer->childItems().size(); i_row > 0; --i_row) {
        if (auto maskItem = dynamic_cast<MaskItem*>(maskContainer->childItems().at(i_row - 1))) {

            if (maskItem->modelType() == Constants::RegionOfInterestType) {
                double xlow = scale * maskItem->getItemValue(RectangleItem::P_XLOW).toDouble();
                double ylow = scale * maskItem->getItemValue(RectangleItem::P_YLOW).toDouble();
                double xup = scale * maskItem->getItemValue(RectangleItem::P_XUP).toDouble();
                double yup = scale * maskItem->getItemValue(RectangleItem::P_YUP).toDouble();
                detector->setRegionOfInterest(xlow, ylow, xup, yup);

            } else {
                std::unique_ptr<IShape2D> shape(maskItem->createShape(scale));
                bool mask_value = maskItem->getItemValue(MaskItem::P_MASK_VALUE).toBool();
                detector->addMask(*shape, mask_value);
            }
        }
    }
}
