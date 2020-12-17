//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/materialeditor/materialeditoractions.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALEDITORACTIONS_H
#define BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALEDITORACTIONS_H

#include "darefl_export.h"
#include <QObject>
#include <memory>

namespace gui2 {

class MaterialModel;
class MaterialSelectionModel;

//! Handles user actions applied to material table.
//! Belongs to MaterialEditor.

class DAREFLCORE_EXPORT MaterialEditorActions : public QObject {
    Q_OBJECT

public:
    MaterialEditorActions(QObject* parent = nullptr);
    ~MaterialEditorActions();

    void setModel(MaterialModel* model);

    void onAddMaterial();
    void onCloneMaterial();
    void onRemoveMaterial();
    void onMoveUp();
    void onMoveDown();
    void onExport();
    void onImport();

    void setMaterialSelectionModel(MaterialSelectionModel* selection_model);

private:
    struct MaterialEditorActionsImpl;
    std::unique_ptr<MaterialEditorActionsImpl> p_impl;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALEDITORACTIONS_H
