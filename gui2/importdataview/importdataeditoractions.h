//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/importdataview/importdataeditoractions.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_IMPORTDATAVIEW_IMPORTDATAEDITORACTIONS_H
#define BORNAGAIN_GUI2_IMPORTDATAVIEW_IMPORTDATAEDITORACTIONS_H

#include "darefl_export.h"
#include <QObject>

class QItemSelection;

namespace ModelView {
class UndoStackInterface;
}

namespace gui2 {

class ExperimentalDataModel;
class DataSelectionModel;

//! Actions for ImportDataEditor.

class DAREFLCORE_EXPORT ImportDataEditorActions : public QObject {
    Q_OBJECT

public:
    ImportDataEditorActions(ExperimentalDataModel* model, QObject* parent = nullptr);

    void setSelectionModel(DataSelectionModel* selection_model);

    bool isUndoEnabled() const;

signals:
    void invokeImportDialogRequest();

public slots:
    void onAddCanvas();
    void onMergeCanvases();
    void onDeleteItem();
    void onUndo();
    void onRedo();
    void onImportDialogRequest();

private slots:
    void onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
    ModelView::UndoStackInterface* undoStack() const;

    ExperimentalDataModel* m_dataModel{nullptr};
    DataSelectionModel* m_selectionModel{nullptr};
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_IMPORTDATAVIEW_IMPORTDATAEDITORACTIONS_H
