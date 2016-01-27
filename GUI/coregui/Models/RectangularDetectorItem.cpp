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

namespace {
const double default_detector_width = 20.0;
const double default_detector_height = 20.0;
const double default_detector_distance = 1000.0;
}

const QString RectangularDetectorItem::P_X_AXIS = "X axis";
const QString RectangularDetectorItem::P_Y_AXIS = "Y axis";
const QString RectangularDetectorItem::P_RESOLUTION_FUNCTION = "Type";
const QString RectangularDetectorItem::P_ALIGNMENT = "Alignment";
const QString RectangularDetectorItem::P_NORMAL = "Normal vector";
const QString RectangularDetectorItem::P_DIRECTION = "Direction vector";
const QString RectangularDetectorItem::P_UV = "uv";
const QString RectangularDetectorItem::P_UV_DPOS = "uv of direct beam";
const QString RectangularDetectorItem::P_DISTANCE = "Distance";

RectangularDetectorItem::RectangularDetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::RectangularDetectorType, parent)
    , m_is_constructed(false)
{
    registerGroupProperty(P_X_AXIS, Constants::BasicAxisType);
    getSubItems()[P_X_AXIS]->getPropertyAttribute(BasicAxisItem::P_TITLE).setHidden();
    getSubItems()[P_X_AXIS]->getPropertyAttribute(BasicAxisItem::P_MIN).setHidden();

    getSubItems()[P_X_AXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, default_detector_width);
    getSubItems()[P_X_AXIS]->getPropertyAttribute(BasicAxisItem::P_MAX).setLabel("Width")
        .setToolTip("Width of the detector in mm");

    registerGroupProperty(P_Y_AXIS, Constants::BasicAxisType);
    getSubItems()[P_Y_AXIS]->getPropertyAttribute(BasicAxisItem::P_TITLE).setHidden();
    getSubItems()[P_Y_AXIS]->getPropertyAttribute(BasicAxisItem::P_MIN).setHidden();
    getSubItems()[P_Y_AXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, default_detector_height);
    getSubItems()[P_Y_AXIS]->getPropertyAttribute(BasicAxisItem::P_MAX).setLabel("Height")
        .setToolTip("Height of the detector in mm");

    registerGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionGroup);
    setGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionNoneType);


    ComboProperty alignment;

    alignment << Constants::ALIGNMENT_GENERIC << Constants::ALIGNMENT_TO_DIRECT_BEAM
              << Constants::ALIGNMENT_TO_SAMPLE << Constants::ALIGNMENT_TO_REFLECTED_BEAM
              << Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS;
    alignment.setValue(Constants::ALIGNMENT_TO_DIRECT_BEAM);
    registerProperty(P_ALIGNMENT, alignment.getVariant());

    registerGroupProperty(P_NORMAL, Constants::VectorType);
    registerGroupProperty(P_DIRECTION, Constants::VectorType);

    registerGroupProperty(P_UV, Constants::VectorType);
    getSubItems()[P_UV]->getPropertyAttribute(VectorItem::P_X).setLabel("u0");
    getSubItems()[P_UV]->getPropertyAttribute(VectorItem::P_Y).setLabel("v0");
    getSubItems()[P_UV]->getPropertyAttribute(VectorItem::P_Z).setHidden();

    registerGroupProperty(P_UV_DPOS, Constants::VectorType);
    registerProperty(P_DISTANCE, default_detector_distance)
        .setToolTip("Distance in [mm] from sample origin to the detector plane");

    update_properties_appearance();
    m_is_constructed=true;
}

void RectangularDetectorItem::onPropertyChange(const QString &name)
{
    if(name == P_ALIGNMENT && m_is_constructed) update_properties_appearance();
    ParameterizedItem::onPropertyChange(name);
}

//! updates property tooltips and visibility flags, depending from type of alignment selected
void RectangularDetectorItem::update_properties_appearance()
{
    ComboProperty alignment = getRegisteredProperty(P_ALIGNMENT).value<ComboProperty>();
    QStringList prop_list;
    prop_list << P_NORMAL << P_DIRECTION << P_UV << P_UV_DPOS << P_DISTANCE;
    foreach(auto prop, prop_list) {
        getPropertyAttribute(prop).setHidden();
    }

    if (alignment.getValue() == Constants::ALIGNMENT_GENERIC) {
        getPropertyAttribute(P_NORMAL).setVisible();
        getPropertyAttribute(P_DIRECTION).setVisible();
        getPropertyAttribute(P_UV).setVisible();

        getSubItems()[P_UV]->getPropertyAttribute(VectorItem::P_X)
            .setToolTip("x-coordinate of point of intersection of normal vector and detector plane, \n"
                        "in local detector coordinates");
        getSubItems()[P_UV]->getPropertyAttribute(VectorItem::P_Y)
            .setToolTip("y-coordinate of point of intersection of normal vector and detector plane, \n"
                        "in local detector coordinates");


    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_DIRECT_BEAM) {
        getPropertyAttribute(P_DISTANCE).setVisible();
        getPropertyAttribute(P_UV).setVisible();

        getSubItems()[P_UV]->getPropertyAttribute(VectorItem::P_X)
            .setToolTip("x-coordinate of point where direct beam hit the detector, \n"
                        "in local detector coordinates [mm]");
        getSubItems()[P_UV]->getPropertyAttribute(VectorItem::P_Y)
            .setToolTip("y-coordinate of point where direct beam hit the detector, \n"
                        "in local detector coordinates [mm]");


    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_SAMPLE) {
        getPropertyAttribute(P_DISTANCE).setVisible();
        getPropertyAttribute(P_UV).setVisible();
    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM) {
        getPropertyAttribute(P_DISTANCE).setVisible();
        getPropertyAttribute(P_UV).setVisible();
    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS) {
        getPropertyAttribute(P_DISTANCE).setVisible();
        getPropertyAttribute(P_UV_DPOS).setVisible();
    }
}


