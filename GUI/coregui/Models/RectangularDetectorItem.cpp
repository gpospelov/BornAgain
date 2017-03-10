// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RectangularDetectorItem.cpp
//! @brief     Implements class RectangularDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RectangularDetectorItem.h"
#include "AxesItems.h"
#include "ComboProperty.h"
#include "GUIHelpers.h"
#include "RectangularDetector.h"
#include "ResolutionFunctionItems.h"
#include "VectorItem.h"

namespace {
const double default_detector_width = 20.0;
const double default_detector_height = 20.0;
const double default_detector_distance = 1000.0;
const QString tooltip_u0="u-coordinate of point of intersection of normal vector "
                         "and detector plane, \n in local detector coordinates";
const QString tooltip_v0="v-coordinate of point of intersection of normal vector "
                         "and detector plane, \n in local detector coordinates";

const QString tooltip_dbeam_u0="u-coordinate of point where direct beam hits the detector, \n"
                               "in local detector coordinates [mm]";
const QString tooltip_dbeam_v0="v-coordinate of point where direct beam hits the detector, \n"
                               "in local detector coordinates [mm]";

const QString tooltip_refbeam_u0="u-coordinate of point where reflected beam hits the detector, \n"
                               "in local detector coordinates [mm]";
const QString tooltip_refbeam_v0="v-coordinate of point where reflected beam hits the detector, \n"
                               "in local detector coordinates [mm]";


const QString tooltip_samplex_u0="u-coordinate of point where sample x-axis crosses the detector, \n"
                               "in local detector coordinates [mm]";
const QString tooltip_samplex_v0="v-coordinate of point where sample x-axis crosses the detector, \n"
                               "in local detector coordinates [mm]";

ComboProperty alignmentCombo()
{
    ComboProperty result;
    result << Constants::ALIGNMENT_GENERIC << Constants::ALIGNMENT_TO_DIRECT_BEAM
           << Constants::ALIGNMENT_TO_SAMPLE << Constants::ALIGNMENT_TO_REFLECTED_BEAM
           << Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS;
    result.setValue(Constants::ALIGNMENT_TO_DIRECT_BEAM);
    return result;
}
}

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
    : DetectorItem(Constants::RectangularDetectorType)
    , m_is_constructed(false)
{
    // axes parameters
    SessionItem* item = addGroupProperty(P_X_AXIS, Constants::BasicAxisType);
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->getItem(BasicAxisItem::P_MIN)->setVisible(false);
    item->setItemValue(BasicAxisItem::P_MAX, default_detector_width);
    item->getItem(BasicAxisItem::P_MAX)->setDisplayName(QStringLiteral("Width"));
    item->getItem(BasicAxisItem::P_MAX)->setToolTip(QStringLiteral("Width of the detector in mm"));

    item = addGroupProperty(P_Y_AXIS, Constants::BasicAxisType);
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->getItem(BasicAxisItem::P_MIN)->setVisible(false);
    item->setItemValue(BasicAxisItem::P_MAX, default_detector_height);
    item->getItem(BasicAxisItem::P_MAX)->setDisplayName(QStringLiteral("Height"));
    item->getItem(BasicAxisItem::P_MAX)->setToolTip(QStringLiteral("Height of the detector in mm"));

    // alignment selector
    addProperty(P_ALIGNMENT, alignmentCombo().getVariant());

    // alignment parameters
    item = addGroupProperty(P_NORMAL, Constants::VectorType);
    item->setItemValue(VectorItem::P_X, default_detector_distance);

    // direction
    item = addGroupProperty(P_DIRECTION, Constants::VectorType);
    item->setItemValue(VectorItem::P_Y, -1.0);

    addProperty(P_U0, default_detector_width / 2.)
        ->setToolTip(tooltip_u0)
        .setLimits(RealLimits::limitless());
    addProperty(P_V0, 0.0)->setToolTip(tooltip_v0).setLimits(RealLimits::limitless());
    addProperty(P_DBEAM_U0, default_detector_width / 2.)
        ->setToolTip(tooltip_dbeam_u0)
        .setLimits(RealLimits::limitless());
    addProperty(P_DBEAM_V0, 0.0)->setToolTip(tooltip_dbeam_v0).setLimits(RealLimits::limitless());

    addProperty(P_DISTANCE, default_detector_distance)
        ->setToolTip(
            QStringLiteral("Distance in [mm] from the sample origin to the detector plane"));

    update_properties_appearance();
    m_is_constructed = true;

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_ALIGNMENT && m_is_constructed)
            update_properties_appearance();
    });
}

void RectangularDetectorItem::setDetectorAlignment(const QString& alignment)
{
    ComboProperty combo_property
        = getItemValue(RectangularDetectorItem::P_ALIGNMENT).value<ComboProperty>();

    if (!combo_property.getValues().contains(alignment))
        throw GUIHelpers::Error(
            "RectangularDetectorItem::setDetectorAlignment -> Unexpected alignment");

    combo_property.setValue(alignment);
    setItemValue(RectangularDetectorItem::P_ALIGNMENT, combo_property.getVariant());
}

void RectangularDetectorItem::setSize(int nx, int ny)
{
    getItem(RectangularDetectorItem::P_X_AXIS)->setItemValue(BasicAxisItem::P_NBINS, nx);
    getItem(RectangularDetectorItem::P_Y_AXIS)->setItemValue(BasicAxisItem::P_NBINS, ny);
}

std::unique_ptr<IDetector2D> RectangularDetectorItem::createDomainDetector() const
{
    // basic axes parameters
    auto& x_axis = item<BasicAxisItem>(RectangularDetectorItem::P_X_AXIS);
    int n_x = x_axis.getItemValue(BasicAxisItem::P_NBINS).toInt();
    double width = x_axis.getItemValue(BasicAxisItem::P_MAX).toDouble();

    auto& y_axis = item<BasicAxisItem>(RectangularDetectorItem::P_Y_AXIS);
    int n_y = y_axis.getItemValue(BasicAxisItem::P_NBINS).toInt();
    double height = y_axis.getItemValue(BasicAxisItem::P_MAX).toDouble();

    std::unique_ptr<RectangularDetector> result(new RectangularDetector(n_x, width, n_y, height));

    // distance and alighnment
    double u0 = getItemValue(P_U0).toDouble();
    double v0 = getItemValue(P_V0).toDouble();
    double dbeam_u0 = getItemValue(P_DBEAM_U0).toDouble();
    double dbeam_v0 = getItemValue(P_DBEAM_V0).toDouble();
    double distance = getItemValue(P_DISTANCE).toDouble();

    ComboProperty alignment = getItemValue(P_ALIGNMENT).value<ComboProperty>();

    if (alignment.getValue() == Constants::ALIGNMENT_GENERIC) {
        result->setPosition(normalVector(), u0, v0, directionVector());

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_DIRECT_BEAM) {
        result->setPerpendicularToDirectBeam(distance, dbeam_u0, dbeam_v0);

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_SAMPLE) {
        result->setPerpendicularToSampleX(distance, u0, v0);

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM) {
        result->setPerpendicularToReflectedBeam(distance, u0, v0);

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS) {
        result->setPerpendicularToReflectedBeam(distance);
        result->setDirectBeamPosition(dbeam_u0, dbeam_v0);
    }

    return std::move(result);
}

//! updates property tooltips and visibility flags, depending from type of alignment selected
void RectangularDetectorItem::update_properties_appearance()
{
    // hiding all alignment properties
    ComboProperty alignment = getItemValue(P_ALIGNMENT).value<ComboProperty>();
    QStringList prop_list;
    prop_list << P_NORMAL << P_DIRECTION << P_U0 << P_V0 << P_DBEAM_U0 << P_DBEAM_V0 << P_DISTANCE;
    foreach (auto prop, prop_list)
        getItem(prop)->setVisible(false);

    // enabling some properties back, depending from detector alignment mode
    if (alignment.getValue() == Constants::ALIGNMENT_GENERIC) {
        getItem(P_NORMAL)->setVisible(true);
        getItem(P_DIRECTION)->setVisible(true);
        getItem(P_U0)->setVisible(true);
        getItem(P_U0)->setToolTip(tooltip_u0);
        getItem(P_V0)->setVisible(true);
        getItem(P_V0)->setToolTip(tooltip_v0);

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_SAMPLE) {
        getItem(P_DISTANCE)->setVisible(true);
        getItem(P_U0)->setVisible(true);
        getItem(P_U0)->setToolTip(tooltip_samplex_u0);
        getItem(P_V0)->setVisible(true);
        getItem(P_V0)->setToolTip(tooltip_samplex_v0);

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_DIRECT_BEAM) {
        getItem(P_DISTANCE)->setVisible(true);
        getItem(P_DBEAM_U0)->setVisible(true);
        getItem(P_DBEAM_V0)->setVisible(true);

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM) {
        getItem(P_DISTANCE)->setVisible(true);
        getItem(P_U0)->setVisible(true);
        getItem(P_U0)->setToolTip(tooltip_refbeam_u0);
        getItem(P_V0)->setVisible(true);
        getItem(P_V0)->setToolTip(tooltip_refbeam_v0);

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS) {
        getItem(P_DISTANCE)->setVisible(true);
        getItem(P_DBEAM_U0)->setVisible(true);
        getItem(P_DBEAM_V0)->setVisible(true);
    }
}

kvector_t RectangularDetectorItem::normalVector() const
{
    return item<VectorItem>(RectangularDetectorItem::P_NORMAL).getVector();
}

kvector_t RectangularDetectorItem::directionVector() const
{
    return item<VectorItem>(RectangularDetectorItem::P_DIRECTION).getVector();
}
