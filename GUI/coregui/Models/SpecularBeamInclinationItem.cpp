// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SpecularBeamInclinationItem.cpp
//! @brief     Implements class SpecularBeamInclinationItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/PointwiseAxisItem.h"
#include "Core/Parametrization/Units.h"

namespace
{
void setupDistributionMean(SessionItem* distribution);
void setAxisPresentationDefaults(SessionItem* axis_item, const QString& type);
} // namespace

const QString SpecularBeamInclinationItem::P_ALPHA_AXIS = "Alpha axis";

SpecularBeamInclinationItem::SpecularBeamInclinationItem()
    : BeamDistributionItem(Constants::SpecularBeamInclinationType, m_show_mean)
{
    register_distribution_group(Constants::SymmetricDistributionGroup);
    setupAxisGroup();
    setupDistributionMean(getGroupItem(P_DISTRIBUTION));

    initDistributionItem(m_show_mean);
}

SpecularBeamInclinationItem::~SpecularBeamInclinationItem() = default;

double SpecularBeamInclinationItem::scaleFactor() const
{
    return Units::degree;
}

void SpecularBeamInclinationItem::updateFileName(const QString& filename)
{
    auto& group_item = item<GroupItem>(P_ALPHA_AXIS);
    auto axis_item = group_item.getChildOfType(Constants::PointwiseAxisType);
    axis_item->setItemValue(PointwiseAxisItem::P_FILE_NAME, filename);
}

void SpecularBeamInclinationItem::setupAxisGroup()
{
    auto group_item =
        dynamic_cast<GroupItem*>(this->addGroupProperty(P_ALPHA_AXIS, Constants::AxesGroup));

    // Both underlying axis items are created, since it
    // strongly simplifies their representation and state
    // handling (no signal emulation required).
    // Basic axis item is the default one.

    group_item->setCurrentType(Constants::PointwiseAxisType);
    setAxisPresentationDefaults(group_item->currentItem(), group_item->currentType());

    group_item->setCurrentType(Constants::BasicAxisType);
    setAxisPresentationDefaults(group_item->currentItem(), group_item->currentType());

    group_item->setToolTip("Axis type selected");
    group_item->setDisplayName("Axis type");
    group_item->setEnabled(false);
    group_item->mapper()->setOnValueChange(
        [group_item]() {
            if (group_item->currentItem()->modelType() == Constants::PointwiseAxisType)
                group_item->setEnabled(true);
        },
        this);
}

namespace
{
void setupDistributionMean(SessionItem* distribution)
{
    Q_ASSERT(distribution);

    SessionItem* valueItem = distribution->getItem(DistributionNoneItem::P_MEAN);
    Q_ASSERT(valueItem);

    valueItem->setLimits(RealLimits::limited(-90.0, 90.0));
    valueItem->setDecimals(3);
    valueItem->setValue(0.0);
}

void setAxisPresentationDefaults(SessionItem* axis_item, const QString& type)
{
    axis_item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    axis_item->setItemValue(BasicAxisItem::P_TITLE, "alpha_i");
    axis_item->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of points in scan");
    axis_item->getItem(BasicAxisItem::P_MIN)->setToolTip("Starting value [deg]");
    axis_item->getItem(BasicAxisItem::P_MAX)->setToolTip("Ending value [deg]");
    axis_item->getItem(BasicAxisItem::P_MIN)->setLimits(RealLimits::limited(0., 90.));
    axis_item->getItem(BasicAxisItem::P_MAX)->setLimits(RealLimits::limited(0., 90.));

    if (type == Constants::BasicAxisType) {
        axis_item->setItemValue(BasicAxisItem::P_MIN, 0.0);
        axis_item->setItemValue(BasicAxisItem::P_MAX, 3.0);
        axis_item->setItemValue(BasicAxisItem::P_NBINS, 500);
    } else if (type == Constants::PointwiseAxisType) {
        axis_item->getItem(BasicAxisItem::P_MIN)->setEnabled(false);
        axis_item->getItem(BasicAxisItem::P_MAX)->setEnabled(false);
        axis_item->getItem(BasicAxisItem::P_NBINS)->setEnabled(false);
    }
}
} // namespace
