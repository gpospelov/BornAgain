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

#include "SpecularBeamInclinationItem.h"
#include "AxesItems.h"
#include "Units.h"

namespace
{
void addAxisGroupProperty(SessionItem* parent, const QString& tag);
void setupDistributionMean(SessionItem* distribution);
}

const QString SpecularBeamInclinationItem::P_ALPHA_AXIS = "Alpha axis";

SpecularBeamInclinationItem::SpecularBeamInclinationItem()
    : BeamDistributionItem(Constants::BeamInclinationAxisType, m_show_mean)
{
    register_distribution_group();
    addAxisGroupProperty(this, P_ALPHA_AXIS);
    setupDistributionMean(getGroupItem(P_DISTRIBUTION));

    initDistributionItem(m_show_mean);
}

SpecularBeamInclinationItem::~SpecularBeamInclinationItem() = default;

double SpecularBeamInclinationItem::scaleFactor() const
{
    return Units::degree;
}

namespace
{
void addAxisGroupProperty(SessionItem* parent, const QString& tag)
{
    auto item = parent->addGroupProperty(tag, Constants::BasicAxisType);
    item->setToolTip("Inclination angle range [deg]");
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of points in scan");
    item->getItem(BasicAxisItem::P_MIN)->setToolTip("Starting value [deg]");
    item->getItem(BasicAxisItem::P_MAX)->setToolTip("Ending value [deg]");

    item->setItemValue(BasicAxisItem::P_TITLE, "alpha_i");
    item->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item->setItemValue(BasicAxisItem::P_MAX, 10.0);
}

void setupDistributionMean(SessionItem* distribution)
{
    Q_ASSERT(distribution);

    SessionItem* valueItem = distribution->getItem(DistributionNoneItem::P_VALUE);
    Q_ASSERT(valueItem);

    valueItem->setLimits(RealLimits::limited(-90.0, 90.0));
    valueItem->setDecimals(3);
    valueItem->setValue(0.0);
}
} // namespace
