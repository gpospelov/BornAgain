//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/materialeditor/materialselectionmodel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALSELECTIONMODEL_H
#define BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALSELECTIONMODEL_H

#include "darefl_export.h"
#include <QItemSelectionModel>
#include <vector>

namespace ModelView {
class ViewModel;
class SessionItem;
} // namespace ModelView

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALSELECTIONMODEL_H
