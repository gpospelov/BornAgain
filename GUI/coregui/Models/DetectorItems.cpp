// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DetectorItem.cpp
//! @brief     Implements class DetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DetectorItems.h"
#include "ComboProperty.h"
#include "AngleProperty.h"
#include "MaskItems.h"
#include "AxesItems.h"
#include "VectorItem.h"
#include <QDebug>

const QString DetectorItem::P_DETECTOR = "Detector";

DetectorItem::DetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::DetectorType, parent)
{
    registerGroupProperty(P_DETECTOR, Constants::DetectorGroup);
    addToValidChildren(Constants::MaskContainerType);
    setGroupProperty(P_DETECTOR, Constants::SphericalDetectorType);
}

MaskContainerItem *DetectorItem::getMaskContainerItem() const
{
    foreach(ParameterizedItem *item, childItems()) {
        if(MaskContainerItem *container = dynamic_cast<MaskContainerItem *>(item)) {
            return container;
        }
    }
    return 0;
}

// -------------------------------------------------------------------------- //

const QString SphericalDetectorItem::P_PHI_AXIS = "Phi axis";
const QString SphericalDetectorItem::P_ALPHA_AXIS = "Alpha axis";
const QString SphericalDetectorItem::P_RESOLUTION_FUNCTION = "Type";

SphericalDetectorItem::SphericalDetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::SphericalDetectorType, parent)
{
    registerGroupProperty(P_PHI_AXIS, Constants::BasicAxisType);
    getSubItems()[P_PHI_AXIS]->getPropertyAttribute(BasicAxisItem::P_TITLE).setHidden();
    getSubItems()[P_PHI_AXIS]->setRegisteredProperty(BasicAxisItem::P_MIN, -1.0);
    getSubItems()[P_PHI_AXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, 1.0);

    registerGroupProperty(P_ALPHA_AXIS, Constants::BasicAxisType);
    getSubItems()[P_ALPHA_AXIS]->getPropertyAttribute(BasicAxisItem::P_TITLE).setHidden();
    getSubItems()[P_ALPHA_AXIS]->setRegisteredProperty(BasicAxisItem::P_MIN, 0.0);
    getSubItems()[P_ALPHA_AXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, 2.0);

    registerGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionGroup);
    setGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionNoneType);
}


// -------------------------------------------------------------------------- //

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
{
    registerGroupProperty(P_X_AXIS, Constants::BasicAxisType);
    getSubItems()[P_X_AXIS]->getPropertyAttribute(BasicAxisItem::P_TITLE).setHidden();
    getSubItems()[P_X_AXIS]->getPropertyAttribute(BasicAxisItem::P_MIN).setHidden();

    getSubItems()[P_X_AXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, 1.0);
    getSubItems()[P_X_AXIS]->getPropertyAttribute(BasicAxisItem::P_MAX).setLabel("width");

    registerGroupProperty(P_Y_AXIS, Constants::BasicAxisType);
    getSubItems()[P_Y_AXIS]->getPropertyAttribute(BasicAxisItem::P_TITLE).setHidden();
    getSubItems()[P_Y_AXIS]->getPropertyAttribute(BasicAxisItem::P_MIN).setHidden();
    getSubItems()[P_Y_AXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, 2.0);
    getSubItems()[P_Y_AXIS]->getPropertyAttribute(BasicAxisItem::P_MAX).setLabel("height");

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
    getSubItems()[P_UV]->getPropertyAttribute(VectorItem::P_X).setLabel("u0").setToolTip("xxxx");
    getSubItems()[P_UV]->getPropertyAttribute(VectorItem::P_Y).setLabel("v0");
    getSubItems()[P_UV]->getPropertyAttribute(VectorItem::P_Z).setHidden();

    registerGroupProperty(P_UV_DPOS, Constants::VectorType);
    registerProperty(P_DISTANCE, 1000.0);

    set_properties_appearance();
}

void RectangularDetectorItem::set_properties_appearance()
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

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_DIRECT_BEAM) {
        getPropertyAttribute(P_DISTANCE).setVisible();
        getPropertyAttribute(P_UV).setVisible();
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


