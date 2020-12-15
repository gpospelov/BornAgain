// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/layereditor/layerviewmodel.h>
#include <darefl/layereditor/layerviewmodelcontroller.h>

using namespace ModelView;

namespace DaRefl
{

LayerViewModel::LayerViewModel(SessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<LayerViewModelController>(model, this), parent)
{
}

} // namespace DaRefl
