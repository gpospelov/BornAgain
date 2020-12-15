// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QAction>
#include <darefl/importdataview/importdataeditoractions.h>
#include <darefl/importdataview/importdataeditortoolbal.h>
#include <darefl/mainwindow/styleutils.h>

namespace DaRefl
{

ImportDataEditorToolBar::ImportDataEditorToolBar(ImportDataEditorActions* editorActions,
                                                 QWidget* parent)
    : QToolBar(parent), m_editorActions(editorActions)
{
    StyleUtils::SetToolBarStyleTextBesides(this);

    auto action = new QAction("Import", this);
    action->setToolTip("Opens the data import dialog.");
    action->setIcon(QIcon(":/icons/import.svg"));
    connect(action, &QAction::triggered, this,
            [this]() { m_editorActions->onImportDialogRequest(); });
    addAction(action);

    addSeparator();

    auto add_canvas_action = new QAction("Add canvas", this);
    add_canvas_action->setToolTip(
        "Creates an empty canvas and appends it to the list.\n"
        "Canvas can hold multiple graphs, graphs can be moved between canvas.");
    add_canvas_action->setIcon(QIcon(":/icons/plus-box-outline.svg"));
    connect(add_canvas_action, &QAction::triggered, [this]() { m_editorActions->onAddCanvas(); });
    addAction(add_canvas_action);

    auto merge_canvases_action = new QAction("Merge", this);
    merge_canvases_action->setToolTip("Merge several selected canvases into one.\n"
                                      "All graphs will appear on a single canvas.");
    merge_canvases_action->setIcon(QIcon(":/icons/set-merge.svg"));
    connect(merge_canvases_action, &QAction::triggered,
            [this]() { m_editorActions->onMergeCanvases(); });
    addAction(merge_canvases_action);

    auto delete_action = new QAction("Remove", this);
    delete_action->setToolTip("Remove the currently selected item,\n"
                              "single graph or canvas with whole content.");
    delete_action->setIcon(QIcon(":/icons/beaker-remove-outline.svg"));
    connect(delete_action, &QAction::triggered, [this]() { m_editorActions->onDeleteItem(); });
    addAction(delete_action);

    addSeparator();

    auto undo_action = new QAction("Undo", this);
    undo_action->setToolTip("Undo the action last performed.");
    undo_action->setIcon(QIcon(":/icons/undo.svg"));
    undo_action->setEnabled(editorActions->isUndoEnabled());
    connect(undo_action, &QAction::triggered, [this]() { m_editorActions->onUndo(); });
    addAction(undo_action);

    auto redo_action = new QAction("Redo", this);
    redo_action->setToolTip("Redo the action just performed.");
    redo_action->setIcon(QIcon(":/icons/redo.svg"));
    redo_action->setEnabled(editorActions->isUndoEnabled());
    connect(redo_action, &QAction::triggered, [this]() { m_editorActions->onRedo(); });
    addAction(redo_action);

    auto empty = new QWidget(this);
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addWidget(empty);

    auto reset_graph_action = new QAction("Replot", this);
    reset_graph_action->setToolTip("Set plot axes to default range");
    reset_graph_action->setIcon(QIcon(":/icons/aspect-ratio.svg"));
    connect(reset_graph_action, &QAction::triggered, this,
            &ImportDataEditorToolBar::updateViewportRequest);
    addAction(reset_graph_action);
}

} // namespace DaRefl
