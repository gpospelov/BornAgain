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

#include "SphericalDetectorItem.h"
#include "AxesItems.h"
#include "SphericalDetector.h"
#include "Units.h"

const QString SphericalDetectorItem::P_PHI_AXIS = "Phi axis";
const QString SphericalDetectorItem::P_ALPHA_AXIS = "Alpha axis";

SphericalDetectorItem::SphericalDetectorItem()
    : DetectorItem(Constants::SphericalDetectorType)
{
    SessionItem* item = addGroupProperty(P_PHI_AXIS, Constants::BasicAxisType);
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->setItemValue(BasicAxisItem::P_MIN, -1.0);
    item->setItemValue(BasicAxisItem::P_MAX, 1.0);

    item->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of phi-axis bins");
    item->getItem(BasicAxisItem::P_MIN)->setToolTip("Low edge of first phi-bin (in deg)");
    item->getItem(BasicAxisItem::P_MAX)->setToolTip("Upper edge of last phi-bin (in deg)");

    item = addGroupProperty(P_ALPHA_AXIS, Constants::BasicAxisType);
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item->setItemValue(BasicAxisItem::P_MAX, 2.0);

    item->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of alpha-axis bins");
    item->getItem(BasicAxisItem::P_MIN)->setToolTip("Low edge of first alpha-bin (in deg)");
    item->getItem(BasicAxisItem::P_MAX)->setToolTip("Upper edge of last alpha-bin (in deg)");

    register_resolution_function();
}

std::unique_ptr<IDetector2D> SphericalDetectorItem::createDomainDetector() const
{
    std::unique_ptr<SphericalDetector> result(new SphericalDetector());

    auto x_axis = dynamic_cast<BasicAxisItem*>(getItem(SphericalDetectorItem::P_PHI_AXIS));
    Q_ASSERT(x_axis);
    int n_x = x_axis->getItemValue(BasicAxisItem::P_NBINS).toInt();
    double x_min = Units::deg2rad(x_axis->getItemValue(BasicAxisItem::P_MIN).toDouble());
    double x_max = Units::deg2rad(x_axis->getItemValue(BasicAxisItem::P_MAX).toDouble());

    auto y_axis = dynamic_cast<BasicAxisItem*>(getItem(SphericalDetectorItem::P_ALPHA_AXIS));
    Q_ASSERT(y_axis);
    int n_y = y_axis->getItemValue(BasicAxisItem::P_NBINS).toInt();
    double y_min = Units::deg2rad(y_axis->getItemValue(BasicAxisItem::P_MIN).toDouble());
    double y_max = Units::deg2rad(y_axis->getItemValue(BasicAxisItem::P_MAX).toDouble());

    result->setDetectorParameters(n_x, x_min, x_max, n_y, y_min, y_max);

    return std::move(result);
}

void SphericalDetectorItem::setSize(int nx, int ny)
{
    getItem(SphericalDetectorItem::P_PHI_AXIS)->setItemValue(BasicAxisItem::P_NBINS, nx);
    getItem(SphericalDetectorItem::P_ALPHA_AXIS)->setItemValue(BasicAxisItem::P_NBINS, ny);
}

double SphericalDetectorItem::axesToDomainUnitsFactor() const
{
    return Units::degree;
}
