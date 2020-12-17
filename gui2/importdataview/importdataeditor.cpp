//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/importdataview/importdataeditor.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/importdataview/importdataeditor.h"
#include "gui2/dataloader/dataloaderdialog.h"
#include "gui2/importdataview/dataselectionmodel.h"
#include "gui2/importdataview/dataselectorwidget.h"
#include "gui2/importdataview/dataviewmodel.h"
#include "gui2/importdataview/graphcanvaswidget.h"
#include "gui2/importdataview/importdataeditoractions.h"
#include "gui2/importdataview/importdataeditortoolbal.h"
#include "gui2/model/experimentaldataitems.h"
#include "gui2/model/experimentaldatamodel.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/utils/containerutils.h"
#include <QSplitter>
#include <QVBoxLayout>

using namespace ModelView;

namespace gui2 {

ImportDataEditor::ImportDataEditor(ExperimentalDataModel* model, QWidget* parent)
    : QWidget(parent)
    , m_dataModel(model)
    , m_viewModel(new DataViewModel(model, this))
    , m_editorActions(new ImportDataEditorActions(m_dataModel, this))
    , m_editorToolBar(new ImportDataEditorToolBar(m_editorActions, this))
    , m_dataSelectorWidget(new DataSelectorWidget(m_viewModel))
    , m_graphCanvasWidget(new GraphCanvasWidget) {
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto splitter = new QSplitter;
    splitter->addWidget(m_dataSelectorWidget);
    splitter->addWidget(m_graphCanvasWidget);
    splitter->setSizes(QList<int>() << 150 << 300);

    layout->addWidget(m_editorToolBar);
    layout->addWidget(splitter);

    m_editorActions->setSelectionModel(m_dataSelectorWidget->selectionModel());
    m_viewModel->setRootSessionItem(model->canvasContainer());

    setupConnections();
}

void ImportDataEditor::setupConnections() {
    // connect toolbar  with this editor
    connect(m_editorToolBar, &ImportDataEditorToolBar::updateViewportRequest,
            [this]() { m_graphCanvasWidget->updateViewport(); });

    // connect selection model with this
    auto on_selection_changed = [this]() {
        m_graphCanvasWidget->setItem(selectionModel()->activeCanvas());
    };
    connect(m_dataSelectorWidget, &DataSelectorWidget::selectionChanged, on_selection_changed);

    // connect actions
    connect(m_editorActions, &ImportDataEditorActions::invokeImportDialogRequest, this,
            &ImportDataEditor::invokeImportDialog);
}

//! Invoke the data load dialog and connect its state.

void ImportDataEditor::invokeImportDialog() {
    DataLoaderDialog dialog(this);

    auto [names, index] = canvasInfo();
    dialog.setTargetCanvas(names, index);
    dialog.invokeFileSelectorDialog();
    if (dialog.fileNames().empty())
        return;

    if (dialog.exec() == QDialog::Accepted) {
        auto canvases = Utils::FindItems<CanvasItem>(m_dataModel);
        CanvasItem* target =
            dialog.targetCanvasIndex() >= 0 ? canvases[dialog.targetCanvasIndex()] : nullptr;

        onImportDialogAccept(dialog.graphImportData(), target);
    }
}

//! Returns vector of canvas display name together with index of currently selected canvas.

std::pair<std::vector<std::string>, int> ImportDataEditor::canvasInfo() const {
    std::vector<std::string> names;
    auto canvases = Utils::FindItems<CanvasItem>(m_dataModel);
    auto current_canvas = selectionModel()->activeCanvas();
    std::transform(canvases.begin(), canvases.end(), std::back_inserter(names),
                   [](auto x) { return x->displayName(); });
    return std::make_pair(names, ModelView::Utils::IndexOfItem(canvases, current_canvas));
}

void ImportDataEditor::onImportDialogAccept(const std::vector<GraphImportData>& graph_data,
                                            CanvasItem* canvas) {
    if (!canvas)
        canvas = m_dataModel->addCanvas();
    for (auto& data : graph_data)
        m_dataModel->addGraph(data, *canvas);
    selectionModel()->selectItem(canvas);
}

DataSelectionModel* ImportDataEditor::selectionModel() const {
    return m_dataSelectorWidget->selectionModel();
}

} // namespace gui2
