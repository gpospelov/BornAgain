// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_LAYEREDITOR_LAYERSELECTIONMODEL_H
#define BORNAGAIN_GUI2_LAYEREDITOR_LAYERSELECTIONMODEL_H

#include "darefl_export.h"
#include <QItemSelectionModel>
#include <vector>

namespace ModelView {
class ViewModel;
class SessionItem;
} // namespace ModelView

namespace gui2 {

class LayerEditorActions;

//! Custom selection model for layer view model (AbstractViewModel).

class DAREFLCORE_EXPORT LayerSelectionModel : public QItemSelectionModel {
    Q_OBJECT

public:
    LayerSelectionModel(ModelView::ViewModel* view_model, QObject* parent = nullptr);
    ~LayerSelectionModel() = default;

    void selectItems(std::vector<ModelView::SessionItem*> items);
    void selectItem(ModelView::SessionItem* item);
    bool firstSelected() const;
    bool lastSelected() const;

    std::vector<ModelView::SessionItem*> selectedItems() const;

    const ModelView::ViewModel* viewModel() const;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_LAYEREDITOR_LAYERSELECTIONMODEL_H
