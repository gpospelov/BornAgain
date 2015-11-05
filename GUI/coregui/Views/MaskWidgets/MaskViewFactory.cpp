// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskViewFactory.h
//! @brief     Implements class MaskViewFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskViewFactory.h"
#include "item_constants.h"
#include "IMaskView.h"
#include "GUIHelpers.h"
#include "RectangleView.h"
#include "ParameterizedItem.h"

IMaskView *MaskViewFactory::createMaskView(ParameterizedItem *item,
                                           ISceneAdaptor *adaptor)
{
    IMaskView *result(0);
    QString model_type = item->modelType();
    if(model_type == Constants::RectangleMaskType) {
        result = new RectangleView();
    }
    else {
        throw GUIHelpers::Error("MaskViewFactory::createSampleView() -> Error! "
                                "Can't create a view for " + model_type);
    }

    result->setParameterizedItem(item);
    result->setSceneAdaptor(adaptor);
    return result;
}
