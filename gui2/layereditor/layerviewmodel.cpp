// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/layereditor/layerviewmodel.h"
#include "gui2/layereditor/layerviewmodelcontroller.h"

using namespace ModelView;

namespace gui2 {

LayerViewModel::LayerViewModel(SessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<LayerViewModelController>(model, this), parent) {}

} // namespace gui2
