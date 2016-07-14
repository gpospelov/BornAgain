// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SphericalDetectorItem.cpp
//! @brief     Implements class SphericalDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "Units.h"
#include "SphericalDetectorItem.h"
#include "AxesItems.h"
#include "SphericalDetector.h"
#include "ResolutionFunctionItems.h"

const QString SphericalDetectorItem::P_PHI_AXIS = "Phi axis";
const QString SphericalDetectorItem::P_ALPHA_AXIS = "Alpha axis";
const QString SphericalDetectorItem::P_RESOLUTION_FUNCTION = "Type";

SphericalDetectorItem::SphericalDetectorItem()
    : SessionItem(Constants::SphericalDetectorType)
{
    SessionItem *item = addGroupProperty(P_PHI_AXIS, Constants::BasicAxisType);
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->setItemValue(BasicAxisItem::P_MIN, -1.0);
    item->setItemValue(BasicAxisItem::P_MAX, 1.0);

    item = addGroupProperty(P_ALPHA_AXIS, Constants::BasicAxisType);
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item->setItemValue(BasicAxisItem::P_MAX, 2.0);

    addGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionGroup);
    setGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionNoneType);
}

std::unique_ptr<IDetector2D> SphericalDetectorItem::createDetector() const
{
    std::unique_ptr<SphericalDetector> result(new SphericalDetector());

    auto x_axis = dynamic_cast<BasicAxisItem *>(
        getItem(SphericalDetectorItem::P_PHI_AXIS));
    Q_ASSERT(x_axis);
    int n_x = x_axis->getItemValue(BasicAxisItem::P_NBINS).toInt();
    double x_min
        = Units::deg2rad(x_axis->getItemValue(BasicAxisItem::P_MIN).toDouble());
    double x_max
        = Units::deg2rad(x_axis->getItemValue(BasicAxisItem::P_MAX).toDouble());

    auto y_axis = dynamic_cast<BasicAxisItem *>(
        getItem(SphericalDetectorItem::P_ALPHA_AXIS));
    Q_ASSERT(y_axis);
    int n_y = y_axis->getItemValue(BasicAxisItem::P_NBINS).toInt();
    double y_min
        = Units::deg2rad(y_axis->getItemValue(BasicAxisItem::P_MIN).toDouble());
    double y_max
        = Units::deg2rad(y_axis->getItemValue(BasicAxisItem::P_MAX).toDouble());

    result->setDetectorParameters(n_x, x_min, x_max, n_y, y_min, y_max);

    return std::move(result);
}

std::unique_ptr<IResolutionFunction2D> SphericalDetectorItem::createResolutionFunction()
{
    // setting up resolution function
    auto resfuncItem = dynamic_cast<ResolutionFunctionItem *>(
        getGroupItem(P_RESOLUTION_FUNCTION));
    Q_ASSERT(resfuncItem);

    std::unique_ptr<IResolutionFunction2D> result(resfuncItem->createResolutionFunction(Units::degree));

    return std::move(result);
}
