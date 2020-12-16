// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QTreeView>
#include <QVBoxLayout>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/instrumentitems.h>
#include <darefl/model/instrumentmodel.h>
#include <darefl/quicksimeditor/custombeampropertyeditorfactory.h>
#include <darefl/quicksimeditor/instrumentpropertyeditor.h>
#include "mvvm/viewmodel/viewmodeldelegate.h"
#include "mvvm/widgets/propertytreeview.h"

using namespace ModelView;

namespace DaRefl {

InstrumentPropertyEditor::InstrumentPropertyEditor(QWidget* parent)
    : QWidget(parent)
    , m_beamPropertyEditor(new ModelView::PropertyTreeView)

{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_beamPropertyEditor);
}

InstrumentPropertyEditor::~InstrumentPropertyEditor() = default;

void InstrumentPropertyEditor::setModels(ApplicationModels* models) {
    auto instrument = models->instrumentModel()->topItem<SpecularInstrumentItem>();

    auto delegate = std::make_unique<ViewModelDelegate>();
    delegate->setEditorFactory(std::make_unique<CustomBeamPropertyEditorFactory>(models));
    m_beamPropertyEditor->setViewModelDelegate(std::move(delegate));

    m_beamPropertyEditor->setItem(
        instrument->item<SpecularBeamItem>(SpecularInstrumentItem::P_BEAM));

    m_beamPropertyEditor->treeView()->setRootIsDecorated(true);
    m_beamPropertyEditor->treeView()->expandAll();
}

QSize InstrumentPropertyEditor::sizeHint() const {
    return StyleUtils::DockSizeHint();
}

QSize InstrumentPropertyEditor::minimumSizeHint() const {
    return StyleUtils::DockMinimumSizeHint();
}

} // namespace DaRefl
