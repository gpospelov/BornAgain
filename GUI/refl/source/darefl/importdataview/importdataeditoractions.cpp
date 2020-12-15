// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/importdataview/dataselectionmodel.h>
#include <darefl/importdataview/graphimportdata.h>
#include <darefl/importdataview/importdataeditoractions.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>
#include <mvvm/interfaces/undostackinterface.h>
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/itemutils.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/plottableitems.h>
#include <mvvm/viewmodel/viewmodelutils.h>

namespace
{
template <typename T> std::vector<T*> itemsFromIndexList(const QModelIndexList& indices)
{
    return ModelView::Utils::CastedItems<T>(ModelView::Utils::UniqueItemsFromIndex(indices));
}

} // namespace

namespace DaRefl
{

ImportDataEditorActions::ImportDataEditorActions(ExperimentalDataModel* model, QObject* parent)
    : QObject(parent), m_dataModel(model)
{
}

void ImportDataEditorActions::setSelectionModel(DataSelectionModel* selection_model)
{
    if (m_selectionModel)
        disconnect(m_selectionModel, &DataSelectionModel::selectionChanged, this,
                   &ImportDataEditorActions::onSelectionChanged);

    m_selectionModel = selection_model;

    if (m_selectionModel)
        connect(m_selectionModel, &DataSelectionModel::selectionChanged, this,
                &ImportDataEditorActions::onSelectionChanged);
}

bool ImportDataEditorActions::isUndoEnabled() const
{
    return m_dataModel->undoStack() != nullptr;
}

//! Create new canvas and append it to the end of canvas container.

void ImportDataEditorActions::onAddCanvas()
{
    m_dataModel->addCanvas();
}

//! Merge selected canvases. All graphs will appear below canvas selected first.

void ImportDataEditorActions::onMergeCanvases()
{
    if (isUndoEnabled())
        undoStack()->beginMacro("onMergeCanvases");

    m_dataModel->mergeCanvases(m_selectionModel->selectedCanvas());

    if (isUndoEnabled())
        undoStack()->endMacro();
}

//! Delete currently selected items.

void ImportDataEditorActions::onDeleteItem()
{
    if (isUndoEnabled())
        undoStack()->beginMacro("onDeleteItem");

    for (auto canvas : m_selectionModel->selectedCanvas())
        m_dataModel->removeCanvas(*canvas);

    for (auto graph : m_selectionModel->selectedGraphs())
        m_dataModel->removeGraph(*graph);

    if (isUndoEnabled())
        undoStack()->endMacro();
}

void ImportDataEditorActions::onUndo()
{
    if (!isUndoEnabled())
        return;

    m_dataModel->undoStack()->undo();
}

void ImportDataEditorActions::onRedo()
{
    if (!isUndoEnabled())
        return;

    m_dataModel->undoStack()->redo();
}

void ImportDataEditorActions::onImportDialogRequest()
{
    if (isUndoEnabled())
        undoStack()->beginMacro("onImportDialogRequest");

    invokeImportDialogRequest();

    if (isUndoEnabled())
        undoStack()->endMacro();
}

//! Processes changed selection. Will change line style of selected graph from
//! solid to dashed line.

void ImportDataEditorActions::onSelectionChanged(const QItemSelection& selected,
                                                 const QItemSelection& deselected)
{
    auto selected_graphs = itemsFromIndexList<ModelView::GraphItem>(selected.indexes());
    for (auto graph : selected_graphs)
        graph->penItem()->setSelected(true);

    auto deselected_graphs = itemsFromIndexList<ModelView::GraphItem>(deselected.indexes());
    for (auto graph : deselected_graphs)
        graph->penItem()->setSelected(false);
}

ModelView::UndoStackInterface* ImportDataEditorActions::undoStack() const
{
    return m_dataModel->undoStack();
}

} // namespace DaRefl
