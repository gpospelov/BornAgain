//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/importdataview/importdataeditor.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_IMPORTDATAVIEW_IMPORTDATAEDITOR_H
#define BORNAGAIN_GUI2_IMPORTDATAVIEW_IMPORTDATAEDITOR_H

#include "darefl_export.h"
#include <QWidget>
#include <string>

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_IMPORTDATAVIEW_IMPORTDATAEDITOR_H
