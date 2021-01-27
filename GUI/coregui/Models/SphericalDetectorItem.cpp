//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/SphericalDetectorItem.cpp
//! @brief     Implements class SphericalDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/SphericalDetectorItem.h"
#include "Base/Const/Units.h"
#include "Device/Detector/SphericalDetector.h"
#include "GUI/coregui/Models/AxesItems.h"

const QString SphericalDetectorItem::P_PHI_AXIS = "Phi axis";
const QString SphericalDetectorItem::P_ALPHA_AXIS = "Alpha axis";

SphericalDetectorItem::SphericalDetectorItem() : DetectorItem("SphericalDetector")
{
    auto phiAxis = addProperty<BasicAxisItem>(P_PHI_AXIS);
    phiAxis->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    phiAxis->setLowerBound(-1.0);
    phiAxis->setUpperBound(1.0);

    phiAxis->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of phi-axis bins");
    phiAxis->getItem(BasicAxisItem::P_MIN_DEG)->setToolTip("Low edge of first phi-bin (in deg)");
    phiAxis->getItem(BasicAxisItem::P_MAX_DEG)->setToolTip("Upper edge of last phi-bin (in deg)");

    auto alphaAxis = addProperty<BasicAxisItem>(P_ALPHA_AXIS);
    alphaAxis->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    alphaAxis->setLowerBound(0.0);
    alphaAxis->setUpperBound(2.0);

    alphaAxis->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of alpha-axis bins");
    alphaAxis->getItem(BasicAxisItem::P_MIN_DEG)
        ->setToolTip("Low edge of first alpha-bin (in deg)");
    alphaAxis->getItem(BasicAxisItem::P_MAX_DEG)
        ->setToolTip("Upper edge of last alpha-bin (in deg)");

    register_resolution_function();
}

std::unique_ptr<IDetector2D> SphericalDetectorItem::createDomainDetector() const
{
    int n_x = phiAxisItem()->binCount();
    double x_min = Units::deg2rad(phiAxisItem()->lowerBound());
    double x_max = Units::deg2rad(phiAxisItem()->upperBound());

    int n_y = alphaAxisItem()->binCount();
    double y_min = Units::deg2rad(alphaAxisItem()->lowerBound());
    double y_max = Units::deg2rad(alphaAxisItem()->upperBound());

    return std::make_unique<SphericalDetector>(n_x, x_min, x_max, n_y, y_min, y_max);
}

int SphericalDetectorItem::xSize() const
{
    return phiAxisItem()->binCount();
}

int SphericalDetectorItem::ySize() const
{
    return alphaAxisItem()->binCount();
}

void SphericalDetectorItem::setXSize(int nx)
{
    phiAxisItem()->setBinCount(nx);
}

void SphericalDetectorItem::setYSize(int ny)
{
    alphaAxisItem()->setBinCount(ny);
}

const BasicAxisItem* SphericalDetectorItem::phiAxisItem() const
{
    return item<BasicAxisItem>(P_PHI_AXIS);
}

BasicAxisItem* SphericalDetectorItem::phiAxisItem()
{
    return item<BasicAxisItem>(P_PHI_AXIS);
}

const BasicAxisItem* SphericalDetectorItem::alphaAxisItem() const
{
    return item<BasicAxisItem>(P_ALPHA_AXIS);
}

BasicAxisItem* SphericalDetectorItem::alphaAxisItem()
{
    return item<BasicAxisItem>(P_ALPHA_AXIS);
}

double SphericalDetectorItem::axesToDomainUnitsFactor() const
{
    return Units::deg;
}
