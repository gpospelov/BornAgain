// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskViewFactory.cpp
//! @brief     Implements class MaskViewFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaskViewFactory.h"
#include "EllipseView.h"
#include "GUIHelpers.h"
#include "IMaskView.h"
#include "IntensityDataView.h"
#include "LineViews.h"
#include "MaskAllView.h"
#include "MaskContainerView.h"
#include "PolygonPointView.h"
#include "PolygonView.h"
#include "RectangleView.h"
#include "RegionOfInterestView.h"
#include "SessionItem.h"
#include "item_constants.h"

IMaskView *MaskViewFactory::createMaskView(SessionItem *item,
                                           ISceneAdaptor *adaptor)
{
    IMaskView *result(0);
    QString model_type = item->modelType();

    if(model_type == Constants::MaskContainerType) {
        result = new MaskContainerView();
    }

    else if(model_type == Constants::RectangleMaskType) {
        result = new RectangleView();
    }

    else if(model_type == Constants::PolygonMaskType) {
        result = new PolygonView();
    }

    else if(model_type == Constants::PolygonPointType) {
        result = new PolygonPointView();
    }

    else if(model_type == Constants::VerticalLineMaskType) {
        result = new VerticalLineView();
    }

    else if(model_type == Constants::HorizontalLineMaskType) {
        result = new HorizontalLineView();
    }

    else if(model_type == Constants::EllipseMaskType) {
        result = new EllipseView();
    }

    else if(model_type == Constants::MaskAllType) {
        result = new MaskAllView();
    }

    else if(model_type == Constants::RegionOfInterestType) {
        result = new RegionOfInterestView();
    }


    else {
        throw GUIHelpers::Error("MaskViewFactory::createSampleView() -> Error! "
                                "Can't create a view for " + model_type);
    }

    result->setParameterizedItem(item);
    result->setSceneAdaptor(adaptor);

    return result;
}
