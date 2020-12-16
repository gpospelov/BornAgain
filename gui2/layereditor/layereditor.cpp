// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include "gui2/layereditor/layereditor.h"
#include "gui2/layereditor/layereditoractions.h"
#include "gui2/layereditor/layereditortoolbar.h"
#include "gui2/layereditor/layereditorwidget.h"
#include "gui2/layereditor/layerselectionmodel.h"
#include "gui2/mainwindow/styleutils.h"
#include "gui2/model/applicationmodels.h"

namespace DaRefl {

LayerEditor::LayerEditor(QWidget* parent)
    : QWidget(parent)
    , m_actions(new LayerEditorActions(this))
    , m_editorWidget(new LayerEditorWidget(this))
    , m_toolBar(new LayerEditorToolBar(m_actions)) {
    setWindowTitle("Layer editor");
    auto layout = new QVBoxLayout;
    layout->addWidget(m_toolBar);
    layout->addWidget(m_editorWidget);
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}

//! Set the mododel for the different items
void LayerEditor::setModels(ApplicationModels* models) {
    m_actions->setModel(models->sampleModel());
    m_editorWidget->setModels(models);

    connect(m_editorWidget->selectionModel(), &LayerSelectionModel::selectionChanged, this,
            &LayerEditor::selectionChanged);

    m_actions->setSelectionModel(m_editorWidget->selectionModel());
}

QSize LayerEditor::sizeHint() const {
    return StyleUtils::DockSizeHint();
}

QSize LayerEditor::minimumSizeHint() const {
    return StyleUtils::DockMinimumSizeHint();
}

void LayerEditor::selectionChanged() {
    dynamic_cast<LayerEditorToolBar*>(m_toolBar)->updateToolButtonStates(
        m_editorWidget->selectionModel()->firstSelected(),
        m_editorWidget->selectionModel()->lastSelected());
}

LayerEditor::~LayerEditor() = default;

} // namespace DaRefl
