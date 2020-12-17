//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/layereditor/layerviewmodelcontroller.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_LAYEREDITOR_LAYERVIEWMODELCONTROLLER_H
#define BORNAGAIN_GUI2_LAYEREDITOR_LAYERVIEWMODELCONTROLLER_H

#include "darefl_export.h"
#include "mvvm/viewmodel/viewmodelcontroller.h"

namespace ModelView {
class ViewModel;
} // namespace ModelView

namespace gui2 {

//! Controller for LayerViewModel to show MultiLayerItem in a tree with custom layout.
//! Will iterate through all top level items and creates rows with layer properties.

class DAREFLCORE_EXPORT LayerViewModelController : public ModelView::ViewModelController {
public:
    LayerViewModelController(ModelView::SessionModel* model, ModelView::ViewModel* view_model);
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_LAYEREDITOR_LAYERVIEWMODELCONTROLLER_H
