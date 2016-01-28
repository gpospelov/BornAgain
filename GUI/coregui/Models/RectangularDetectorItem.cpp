// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/RectangularDetectorItem.cpp
//! @brief     Implements class RectangularDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RectangularDetectorItem.h"
#include "AxesItems.h"
#include "VectorItem.h"
#include "ComboProperty.h"
#include "RectangularDetector.h"
#include "ResolutionFunctionItems.h"


namespace {
const double default_detector_width = 20.0;
const double default_detector_height = 20.0;
const double default_detector_distance = 1000.0;
const QString tooltip_u0="x-coordinate of point of intersection of normal vector "
                         "and detector plane, \n in local detector coordinates";
const QString tooltip_v0="y-coordinate of point of intersection of normal vector "
                         "and detector plane, \n in local detector coordinates";

const QString tooltip_dbeam_u0="x-coordinate of point where direct beam hit the detector, \n"
                               "in local detector coordinates [mm]";
const QString tooltip_dbeam_v0="y-coordinate of point where direct beam hit the detector, \n"
                               "in local detector coordinates [mm]";

const QString tooltip_refbeam_u0="x-coordinate of point where reflected beam hit the detector, \n"
                               "in local detector coordinates [mm]";
const QString tooltip_refbeam_v0="y-coordinate of point where reflected beam hit the detector, \n"
                               "in local detector coordinates [mm]";


const QString tooltip_samplex_u0="x-coordinate of point where sample x-axis crosses the detector, \n"
                               "in local detector coordinates [mm]";
const QString tooltip_samplex_v0="y-coordinate of point where sample x-axis crosses the detector, \n"
                               "in local detector coordinates [mm]";

}

const QString RectangularDetectorItem::P_X_AXIS = "X axis";
const QString RectangularDetectorItem::P_Y_AXIS = "Y axis";
const QString RectangularDetectorItem::P_RESOLUTION_FUNCTION = "Type";
const QString RectangularDetectorItem::P_ALIGNMENT = "Alignment";
const QString RectangularDetectorItem::P_NORMAL = "Normal vector";
const QString RectangularDetectorItem::P_DIRECTION = "Direction vector";
const QString RectangularDetectorItem::P_U0 = "u0";
const QString RectangularDetectorItem::P_V0 = "v0";
const QString RectangularDetectorItem::P_DBEAM_U0 = "u0 (dbeam)";
const QString RectangularDetectorItem::P_DBEAM_V0 = "v0 (dbeam)";
const QString RectangularDetectorItem::P_DISTANCE = "Distance";

RectangularDetectorItem::RectangularDetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::RectangularDetectorType, parent)
    , m_is_constructed(false)
{
    // axes parameters
    registerGroupProperty(P_X_AXIS, Constants::BasicAxisType);
    getSubItems()[P_X_AXIS]->getPropertyAttribute(BasicAxisItem::P_TITLE).setHidden();
    getSubItems()[P_X_AXIS]->getPropertyAttribute(BasicAxisItem::P_MIN).setHidden();

    getSubItems()[P_X_AXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, default_detector_width);
    getSubItems()[P_X_AXIS]->getPropertyAttribute(BasicAxisItem::P_MAX)
        .setLabel(QStringLiteral("Width"))
        .setToolTip(QStringLiteral("Width of the detector in mm"));

    registerGroupProperty(P_Y_AXIS, Constants::BasicAxisType);
    getSubItems()[P_Y_AXIS]->getPropertyAttribute(BasicAxisItem::P_TITLE).setHidden();
    getSubItems()[P_Y_AXIS]->getPropertyAttribute(BasicAxisItem::P_MIN).setHidden();
    getSubItems()[P_Y_AXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, default_detector_height);
    getSubItems()[P_Y_AXIS]->getPropertyAttribute(BasicAxisItem::P_MAX)
        .setLabel(QStringLiteral("Height"))
        .setToolTip(QStringLiteral("Height of the detector in mm"));

    // resolution function
    registerGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionGroup);
    setGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionNoneType);

    // alignment selector
    ComboProperty alignment;

    alignment << Constants::ALIGNMENT_GENERIC << Constants::ALIGNMENT_TO_DIRECT_BEAM
              << Constants::ALIGNMENT_TO_SAMPLE << Constants::ALIGNMENT_TO_REFLECTED_BEAM
              << Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS;
    alignment.setValue(Constants::ALIGNMENT_TO_DIRECT_BEAM);
    registerProperty(P_ALIGNMENT, alignment.getVariant());

    // alignment parameters
    registerGroupProperty(P_NORMAL, Constants::VectorType);
    registerGroupProperty(P_DIRECTION, Constants::VectorType);

    registerProperty(P_U0, default_detector_width/2.).setToolTip(tooltip_u0);
    registerProperty(P_V0, 0.0).setToolTip(tooltip_v0);
    registerProperty(P_DBEAM_U0, default_detector_width/2.).setToolTip(tooltip_dbeam_u0);
    registerProperty(P_DBEAM_V0, 0.0).setToolTip(tooltip_dbeam_v0);

    registerProperty(P_DISTANCE, default_detector_distance)
        .setToolTip(QStringLiteral("Distance in [mm] from sample origin to the detector plane"));

    update_properties_appearance();
    m_is_constructed=true;
}

void RectangularDetectorItem::onPropertyChange(const QString &name)
{
    if(name == P_ALIGNMENT && m_is_constructed) update_properties_appearance();
    ParameterizedItem::onPropertyChange(name);
}

std::unique_ptr<IDetector2D> RectangularDetectorItem::createDetector() const
{
    // basic axes parameters
    auto x_axis = dynamic_cast<BasicAxisItem *>(
        getSubItems()[RectangularDetectorItem::P_X_AXIS]);
    Q_ASSERT(x_axis);
    int n_x = x_axis->getRegisteredProperty(BasicAxisItem::P_NBINS).toInt();
    double width
        = Units::deg2rad(x_axis->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble());

    auto y_axis = dynamic_cast<BasicAxisItem *>(
        getSubItems()[RectangularDetectorItem::P_Y_AXIS]);
    Q_ASSERT(y_axis);
    int n_y = y_axis->getRegisteredProperty(BasicAxisItem::P_NBINS).toInt();
    double height
        = Units::deg2rad(y_axis->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble());

    std::unique_ptr<RectangularDetector> result(new RectangularDetector(n_x, width, n_y, height));

    // distance and alighnment
    double distance = getRegisteredProperty(P_DISTANCE).toDouble();

    kvector_t normal = getNormalVector();
    kvector_t direction = getDirectionVector();




    ComboProperty alignment = getRegisteredProperty(P_ALIGNMENT).value<ComboProperty>();

    if (alignment.getValue() == Constants::ALIGNMENT_GENERIC) {

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_DIRECT_BEAM) {

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_SAMPLE) {

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM) {

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS) {

    }





    return std::move(result);

}

//! updates property tooltips and visibility flags, depending from type of alignment selected
void RectangularDetectorItem::update_properties_appearance()
{
    // hiding all alignment properties
    ComboProperty alignment = getRegisteredProperty(P_ALIGNMENT).value<ComboProperty>();
    QStringList prop_list;
    prop_list << P_NORMAL << P_DIRECTION << P_U0 << P_V0 << P_DBEAM_U0 << P_DBEAM_V0 << P_DISTANCE;
    foreach(auto prop, prop_list) {
        getPropertyAttribute(prop).setHidden();
    }

    // enabling some properties back, depending from detector alignment mode
    if (alignment.getValue() == Constants::ALIGNMENT_GENERIC) {
        getPropertyAttribute(P_NORMAL).setVisible();
        getPropertyAttribute(P_DIRECTION).setVisible();
        getPropertyAttribute(P_U0).setVisible().setToolTip(tooltip_u0);
        getPropertyAttribute(P_V0).setVisible().setToolTip(tooltip_v0);

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_DIRECT_BEAM) {
        getPropertyAttribute(P_DISTANCE).setVisible();
        getPropertyAttribute(P_DBEAM_U0).setVisible();
        getPropertyAttribute(P_DBEAM_V0).setVisible();

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_SAMPLE) {
        getPropertyAttribute(P_DISTANCE).setVisible();
        getPropertyAttribute(P_U0).setVisible().setToolTip(tooltip_samplex_u0);
        getPropertyAttribute(P_V0).setVisible().setToolTip(tooltip_samplex_v0);

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM) {
        getPropertyAttribute(P_DISTANCE).setVisible();
        getPropertyAttribute(P_U0).setVisible().setToolTip(tooltip_refbeam_u0);
        getPropertyAttribute(P_V0).setVisible().setToolTip(tooltip_refbeam_v0);

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS) {
        getPropertyAttribute(P_DISTANCE).setVisible();
        getPropertyAttribute(P_DBEAM_U0).setVisible();
        getPropertyAttribute(P_DBEAM_V0).setVisible();
    }
}

kvector_t RectangularDetectorItem::getNormalVector() const
{
    auto item = dynamic_cast<VectorItem *>(
        getSubItems()[RectangularDetectorItem::P_NORMAL]);
    Q_ASSERT(item);
    return item->getVector();
}

kvector_t RectangularDetectorItem::getDirectionVector() const
{
    auto item = dynamic_cast<VectorItem *>(
        getSubItems()[RectangularDetectorItem::P_DIRECTION]);
    Q_ASSERT(item);
    return item->getVector();
}


