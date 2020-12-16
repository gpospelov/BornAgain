// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_LAYERVIEWMODELCONTROLLER_H
#define DAREFL_LAYEREDITOR_LAYERVIEWMODELCONTROLLER_H

#include <darefl/darefl_export.h>
#include "mvvm/viewmodel/viewmodelcontroller.h"

namespace ModelView {
class ViewModel;
} // namespace ModelView

namespace DaRefl {

//! Controller for LayerViewModel to show MultiLayerItem in a tree with custom layout.
//! Will iterate through all top level items and creates rows with layer properties.

class DAREFLCORE_EXPORT LayerViewModelController : public ModelView::ViewModelController {
public:
    LayerViewModelController(ModelView::SessionModel* model, ModelView::ViewModel* view_model);
};

} // namespace DaRefl

#endif // DAREFL_LAYEREDITOR_LAYERVIEWMODELCONTROLLER_H
