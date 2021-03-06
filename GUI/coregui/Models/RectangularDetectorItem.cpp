//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/RectangularDetectorItem.cpp
//! @brief     Implements class RectangularDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/RectangularDetectorItem.h"
#include "Device/Detector/RectangularDetector.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/ResolutionFunctionItems.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace {
const double default_detector_width = 20.0;
const double default_detector_height = 20.0;
const double default_detector_distance = 1000.0;
const QString tooltip_u0 = "u-coordinate of point of intersection of normal vector "
                           "and detector plane, \n in local detector coordinates";
const QString tooltip_v0 = "v-coordinate of point of intersection of normal vector "
                           "and detector plane, \n in local detector coordinates";

const QString tooltip_dbeam_u0 = "u-coordinate of point where direct beam hits the detector, \n"
                                 "in local detector coordinates [mm]";
const QString tooltip_dbeam_v0 = "v-coordinate of point where direct beam hits the detector, \n"
                                 "in local detector coordinates [mm]";

const QString tooltip_refbeam_u0 =
    "u-coordinate of point where reflected beam hits the detector, \n"
    "in local detector coordinates [mm]";
const QString tooltip_refbeam_v0 =
    "v-coordinate of point where reflected beam hits the detector, \n"
    "in local detector coordinates [mm]";

const QString tooltip_samplex_u0 =
    "u-coordinate of point where sample x-axis crosses the detector, \n"
    "in local detector coordinates [mm]";
const QString tooltip_samplex_v0 =
    "v-coordinate of point where sample x-axis crosses the detector, \n"
    "in local detector coordinates [mm]";

ComboProperty alignmentCombo()
{
    ComboProperty result;
    result << "Generic"
           << "Perpendicular to direct beam"
           << "Perpendicular to sample x-axis"
           << "Perpendicular to reflected beam"
           << "Perpendicular to reflected beam (dpos)";
    result.setValue("Perpendicular to direct beam");
    return result;
}
} // namespace

const QString RectangularDetectorItem::P_X_AXIS = "X axis";
const QString RectangularDetectorItem::P_Y_AXIS = "Y axis";
const QString RectangularDetectorItem::P_ALIGNMENT = "Alignment";
const QString RectangularDetectorItem::P_NORMAL = "Normal vector";
const QString RectangularDetectorItem::P_DIRECTION = "Direction vector";
const QString RectangularDetectorItem::P_U0 = "u0";
const QString RectangularDetectorItem::P_V0 = "v0";
const QString RectangularDetectorItem::P_DBEAM_U0 = "u0 (dbeam)";
const QString RectangularDetectorItem::P_DBEAM_V0 = "v0 (dbeam)";
const QString RectangularDetectorItem::P_DISTANCE = "Distance";

RectangularDetectorItem::RectangularDetectorItem()
    : DetectorItem("RectangularDetector"), m_is_constructed(false)
{
    // axes parameters
    auto axisItem = addProperty<BasicAxisItem>(P_X_AXIS);
    axisItem->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    axisItem->getItem(BasicAxisItem::P_MIN_DEG)->setVisible(false);
    axisItem->setUpperBound(default_detector_width);
    axisItem->getItem(BasicAxisItem::P_MAX_DEG)->setDisplayName("Width [mm]");
    axisItem->getItem(BasicAxisItem::P_MAX_DEG)->setToolTip("Width of the detector in mm");

    axisItem = addProperty<BasicAxisItem>(P_Y_AXIS);
    axisItem->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    axisItem->getItem(BasicAxisItem::P_MIN_DEG)->setVisible(false);
    axisItem->setUpperBound(default_detector_height);
    axisItem->getItem(BasicAxisItem::P_MAX_DEG)->setDisplayName("Height [mm]");
    axisItem->getItem(BasicAxisItem::P_MAX_DEG)->setToolTip("Height of the detector in mm");

    // alignment selector
    addProperty(P_ALIGNMENT, alignmentCombo().variant());

    // alignment parameters
    auto normalItem = addProperty<VectorItem>(P_NORMAL);
    normalItem->setX(default_detector_distance);

    // direction
    auto directionItem = addProperty<VectorItem>(P_DIRECTION);
    directionItem->setY(-1.0);

    addProperty(P_U0, default_detector_width / 2.)
        ->setToolTip(tooltip_u0)
        .setLimits(RealLimits::limitless());
    addProperty(P_V0, 0.0)->setToolTip(tooltip_v0).setLimits(RealLimits::limitless());
    addProperty(P_DBEAM_U0, default_detector_width / 2.)
        ->setToolTip(tooltip_dbeam_u0)
        .setLimits(RealLimits::limitless());
    addProperty(P_DBEAM_V0, 0.0)->setToolTip(tooltip_dbeam_v0).setLimits(RealLimits::limitless());

    addProperty(P_DISTANCE, default_detector_distance)
        ->setToolTip("Distance in [mm] from the sample origin to the detector plane");

    register_resolution_function();

    update_properties_appearance();
    m_is_constructed = true;

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_ALIGNMENT && m_is_constructed)
            update_properties_appearance();
    });
}

void RectangularDetectorItem::setDetectorAlignment(const QString& alignment)
{
    ComboProperty combo_property =
        getItemValue(RectangularDetectorItem::P_ALIGNMENT).value<ComboProperty>();

    if (!combo_property.getValues().contains(alignment))
        throw GUIHelpers::Error(
            "RectangularDetectorItem::setDetectorAlignment -> Unexpected alignment");

    combo_property.setValue(alignment);
    setItemValue(RectangularDetectorItem::P_ALIGNMENT, combo_property.variant());
}

int RectangularDetectorItem::xSize() const
{
    return xAxisItem()->binCount();
}

int RectangularDetectorItem::ySize() const
{
    return yAxisItem()->binCount();
}

void RectangularDetectorItem::setXSize(int nx)
{
    xAxisItem()->setBinCount(nx);
}

void RectangularDetectorItem::setYSize(int ny)
{
    yAxisItem()->setBinCount(ny);
}

const BasicAxisItem* RectangularDetectorItem::xAxisItem() const
{
    return item<BasicAxisItem>(P_X_AXIS);
}

BasicAxisItem* RectangularDetectorItem::xAxisItem()
{
    return const_cast<BasicAxisItem*>(
        static_cast<const RectangularDetectorItem*>(this)->xAxisItem());
}

const BasicAxisItem* RectangularDetectorItem::yAxisItem() const
{
    return item<BasicAxisItem>(P_Y_AXIS);
}

BasicAxisItem* RectangularDetectorItem::yAxisItem()
{
    return const_cast<BasicAxisItem*>(
        static_cast<const RectangularDetectorItem*>(this)->yAxisItem());
}

std::unique_ptr<IDetector2D> RectangularDetectorItem::createDomainDetector() const
{
    // basic axes parameters
    size_t n_x = xAxisItem()->binCount();
    double width = xAxisItem()->upperBound();

    size_t n_y = yAxisItem()->binCount();
    double height = yAxisItem()->upperBound();

    auto result = std::make_unique<RectangularDetector>(n_x, width, n_y, height);

    // distance and alighnment
    double u0 = getItemValue(P_U0).toDouble();
    double v0 = getItemValue(P_V0).toDouble();
    double dbeam_u0 = getItemValue(P_DBEAM_U0).toDouble();
    double dbeam_v0 = getItemValue(P_DBEAM_V0).toDouble();
    double distance = getItemValue(P_DISTANCE).toDouble();

    ComboProperty alignment = getItemValue(P_ALIGNMENT).value<ComboProperty>();

    if (alignment.getValue() == "Generic") {
        result->setPosition(normalVector(), u0, v0, directionVector());
    } else if (alignment.getValue() == "Perpendicular to direct beam") {
        result->setPerpendicularToDirectBeam(distance, dbeam_u0, dbeam_v0);
    } else if (alignment.getValue() == "Perpendicular to sample x-axis") {
        result->setPerpendicularToSampleX(distance, u0, v0);
    } else if (alignment.getValue() == "Perpendicular to reflected beam") {
        result->setPerpendicularToReflectedBeam(distance, u0, v0);
    } else if (alignment.getValue() == "Perpendicular to reflected beam (dpos)") {
        result->setPerpendicularToReflectedBeam(distance);
        result->setDirectBeamPosition(dbeam_u0, dbeam_v0);
    }
    return std::unique_ptr<IDetector2D>(result.release());
}

//! updates property tooltips and visibility flags, depending from type of alignment selected
void RectangularDetectorItem::update_properties_appearance()
{
    // hiding all alignment properties
    ComboProperty alignment = getItemValue(P_ALIGNMENT).value<ComboProperty>();
    QStringList prop_list;
    prop_list << P_NORMAL << P_DIRECTION << P_U0 << P_V0 << P_DBEAM_U0 << P_DBEAM_V0 << P_DISTANCE;
    for (auto prop : prop_list)
        getItem(prop)->setVisible(false);

    // enabling some properties back, depending from detector alignment mode
    if (alignment.getValue() == "Generic") {
        getItem(P_NORMAL)->setVisible(true);
        getItem(P_DIRECTION)->setVisible(true);
        getItem(P_U0)->setVisible(true);
        getItem(P_U0)->setToolTip(tooltip_u0);
        getItem(P_V0)->setVisible(true);
        getItem(P_V0)->setToolTip(tooltip_v0);
    } else if (alignment.getValue() == "Perpendicular to sample x-axis") {
        getItem(P_DISTANCE)->setVisible(true);
        getItem(P_U0)->setVisible(true);
        getItem(P_U0)->setToolTip(tooltip_samplex_u0);
        getItem(P_V0)->setVisible(true);
        getItem(P_V0)->setToolTip(tooltip_samplex_v0);
    } else if (alignment.getValue() == "Perpendicular to direct beam") {
        getItem(P_DISTANCE)->setVisible(true);
        getItem(P_DBEAM_U0)->setVisible(true);
        getItem(P_DBEAM_V0)->setVisible(true);
    } else if (alignment.getValue() == "Perpendicular to reflected beam") {
        getItem(P_DISTANCE)->setVisible(true);
        getItem(P_U0)->setVisible(true);
        getItem(P_U0)->setToolTip(tooltip_refbeam_u0);
        getItem(P_V0)->setVisible(true);
        getItem(P_V0)->setToolTip(tooltip_refbeam_v0);
    } else if (alignment.getValue() == "Perpendicular to reflected beam (dpos)") {
        getItem(P_DISTANCE)->setVisible(true);
        getItem(P_DBEAM_U0)->setVisible(true);
        getItem(P_DBEAM_V0)->setVisible(true);
    }
}

kvector_t RectangularDetectorItem::normalVector() const
{
    return item<VectorItem>(RectangularDetectorItem::P_NORMAL)->getVector();
}

kvector_t RectangularDetectorItem::directionVector() const
{
    return item<VectorItem>(RectangularDetectorItem::P_DIRECTION)->getVector();
}
