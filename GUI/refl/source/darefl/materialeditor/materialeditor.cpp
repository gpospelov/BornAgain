// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/materialeditor/materialeditor.h>
#include <darefl/materialeditor/materialeditoractions.h>
#include <darefl/materialeditor/materialeditortoolbar.h>
#include <darefl/materialeditor/materialeditorwidget.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/materialmodel.h>

namespace DaRefl
{

MaterialEditor::MaterialEditor(QWidget* parent)
    : QWidget(parent)
    , m_actions(new MaterialEditorActions(this))
    , m_editorWidget(new MaterialEditorWidget)
    , m_toolBar(new MaterialEditorToolBar(m_actions))
{
    setWindowTitle("Material editor");
    auto layout = new QVBoxLayout;
    layout->addWidget(m_toolBar);
    layout->addWidget(m_editorWidget);
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}

//! Set the mododel for the different items
void MaterialEditor::setModels(ApplicationModels* models)
{
    m_editorWidget->setModels(models);
    m_actions->setModel(models->materialModel());
    m_actions->setMaterialSelectionModel(m_editorWidget->selectionModel());
}

QSize MaterialEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize MaterialEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

MaterialEditor::~MaterialEditor() = default;

} // namespace DaRefl
