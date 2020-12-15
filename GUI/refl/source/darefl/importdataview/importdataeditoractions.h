// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORACTIONS_H
#define DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORACTIONS_H

#include <QObject>
#include <darefl/darefl_export.h>

class QItemSelection;

namespace ModelView {
class UndoStackInterface;
}

namespace DaRefl {

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

} // namespace DaRefl

#endif // DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORACTIONS_H
