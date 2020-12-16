// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MATERIALEDITOR_MATERIALSELECTIONMODEL_H
#define DAREFL_MATERIALEDITOR_MATERIALSELECTIONMODEL_H

#include <QItemSelectionModel>
#include "darefl_export.h"
#include <vector>

namespace ModelView {
class ViewModel;
class SessionItem;
} // namespace ModelView

namespace DaRefl {

class MaterialEditorActions;
class MaterialBaseItem;

//! Custom selection model for material view model (AbstractViewModel).
//! Reports clients about selected MaterialItem in material table and hides
//! QModelIndex related machinery.

class DAREFLCORE_EXPORT MaterialSelectionModel : public QItemSelectionModel {
    Q_OBJECT

public:
    MaterialSelectionModel(ModelView::ViewModel* view_model, QObject* parent = nullptr);
    ~MaterialSelectionModel() = default;

    void selectItem(ModelView::SessionItem* item);
    void selectItems(std::vector<ModelView::SessionItem*> items);

    std::vector<MaterialBaseItem*> selectedMaterials() const;

    const ModelView::ViewModel* viewModel() const;
};

} // namespace DaRefl

#endif // DAREFL_MATERIALEDITOR_MATERIALSELECTIONMODEL_H
