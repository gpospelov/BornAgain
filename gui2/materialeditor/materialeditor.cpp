//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/materialeditor/materialeditor.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/materialeditor/materialeditor.h"
#include "gui2/mainwindow/styleutils.h"
#include "gui2/materialeditor/materialeditoractions.h"
#include "gui2/materialeditor/materialeditortoolbar.h"
#include "gui2/materialeditor/materialeditorwidget.h"
#include "gui2/model/applicationmodels.h"
#include "gui2/model/materialmodel.h"
#include <QVBoxLayout>

namespace gui2 {

MaterialEditor::MaterialEditor(QWidget* parent)
    : QWidget(parent)
    , m_actions(new MaterialEditorActions(this))
    , m_editorWidget(new MaterialEditorWidget)
    , m_toolBar(new MaterialEditorToolBar(m_actions)) {
    setWindowTitle("Material editor");
    auto layout = new QVBoxLayout;
    layout->addWidget(m_toolBar);
    layout->addWidget(m_editorWidget);
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}

//! Set the mododel for the different items
void MaterialEditor::setModels(ApplicationModels* models) {
    m_editorWidget->setModels(models);
    m_actions->setModel(models->materialModel());
    m_actions->setMaterialSelectionModel(m_editorWidget->selectionModel());
}

QSize MaterialEditor::sizeHint() const {
    return StyleUtils::DockSizeHint();
}

QSize MaterialEditor::minimumSizeHint() const {
    return StyleUtils::DockMinimumSizeHint();
}

MaterialEditor::~MaterialEditor() = default;

} // namespace gui2
