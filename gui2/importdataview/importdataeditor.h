// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITOR_H
#define DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITOR_H

#include <QWidget>
#include "darefl_export.h"
#include <string>

namespace DaRefl {

class ExperimentalDataModel;
struct GraphImportData;
class DataViewModel;
class DataSelectionModel;
class ImportDataEditorActions;
class ImportDataEditorToolBar;
class DataSelectorWidget;
class GraphCanvasWidget;
class CanvasItem;

//! Main editor to import user data.

class DAREFLCORE_EXPORT ImportDataEditor : public QWidget {
    Q_OBJECT

public:
    ImportDataEditor(ExperimentalDataModel* model, QWidget* parent = nullptr);

private:
    void setupConnections();
    void invokeImportDialog();

    std::pair<std::vector<std::string>, int> canvasInfo() const;
    void onImportDialogAccept(const std::vector<GraphImportData>& graph_data, CanvasItem* canvas);
    DataSelectionModel* selectionModel() const;

    ExperimentalDataModel* m_dataModel{nullptr};
    DataViewModel* m_viewModel{nullptr};
    ImportDataEditorActions* m_editorActions{nullptr};
    ImportDataEditorToolBar* m_editorToolBar{nullptr};
    DataSelectorWidget* m_dataSelectorWidget{nullptr};
    GraphCanvasWidget* m_graphCanvasWidget{nullptr};
};

} // namespace DaRefl

#endif // DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITOR_H
