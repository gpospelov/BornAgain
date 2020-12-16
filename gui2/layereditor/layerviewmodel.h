// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_LAYERVIEWMODEL_H
#define DAREFL_LAYEREDITOR_LAYERVIEWMODEL_H

#include "darefl_export.h"
#include "mvvm/viewmodel/viewmodel.h"

namespace ModelView {
class SessionModel;
} // namespace ModelView

namespace DaRefl {

//! View model to display content of MultiLayerItem in table like views.

class DAREFLCORE_EXPORT LayerViewModel : public ModelView::ViewModel {
    Q_OBJECT

public:
    LayerViewModel(ModelView::SessionModel* model, QObject* parent = nullptr);
};

} // namespace DaRefl

#endif // DAREFL_LAYEREDITOR_LAYERVIEWMODEL_H
