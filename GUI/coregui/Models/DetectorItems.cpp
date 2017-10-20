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

namespace {
const QString res_func_group_label = "Type";
const QString analyzer_direction_tooltip = "Direction of the polarization analysis";
const QString analyzer_efficiency_tooltip = "Efficiency of the polarization analysis";
const QString analyzer_transmission_tooltip = "Total transmission of the polarization analysis";
}

const QString DetectorItem::T_MASKS = "Masks";
const QString DetectorItem::P_RESOLUTION_FUNCTION = "ResolutionFunctions";
const QString DetectorItem::P_ANALYZER_DIRECTION = "Analyzer direction";
const QString DetectorItem::P_ANALYZER_EFFICIENCY = "Analyzer efficiency";
const QString DetectorItem::P_ANALYZER_TOTAL_TRANSMISSION = "Total transmission";

DetectorItem::DetectorItem(const QString& modelType) : SessionItem(modelType)
{
    registerTag(T_MASKS, 0, -1, QStringList() << Constants::MaskContainerType);
    setDefaultTag(T_MASKS);

    addGroupProperty(P_ANALYZER_DIRECTION, Constants::VectorType)->setToolTip(
                analyzer_direction_tooltip);
    addProperty(P_ANALYZER_EFFICIENCY, 0.0)->setToolTip(analyzer_efficiency_tooltip);
    addProperty(P_ANALYZER_TOTAL_TRANSMISSION, 1.0)->setToolTip(analyzer_transmission_tooltip);

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_RESOLUTION_FUNCTION)
            update_resolution_function_tooltips();
    });
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
    auto item = addGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionGroup);
    item->setDisplayName(res_func_group_label);
    item->setToolTip("Detector resolution function");
}

void DetectorItem::update_resolution_function_tooltips()
{
    auto& resfuncItem = groupItem<ResolutionFunctionItem>(DetectorItem::P_RESOLUTION_FUNCTION);

    if(resfuncItem.modelType() == Constants::ResolutionFunction2DGaussianType) {
        QString units = modelType() == Constants::SphericalDetectorType ? "deg" : "mm";

        resfuncItem.getItem(ResolutionFunction2DGaussianItem::P_SIGMA_X)
                ->setToolTip("Resolution along horizontal axis (in "+units+")");
        resfuncItem.getItem(ResolutionFunction2DGaussianItem::P_SIGMA_Y)
                ->setToolTip("Resolution along vertical axis (in "+units+")");
    }
}

std::unique_ptr<IResolutionFunction2D> DetectorItem::createResolutionFunction() const
{
    auto& resfuncItem = groupItem<ResolutionFunctionItem>(DetectorItem::P_RESOLUTION_FUNCTION);
    return resfuncItem.createResolutionFunction(axesToDomainUnitsFactor());
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
