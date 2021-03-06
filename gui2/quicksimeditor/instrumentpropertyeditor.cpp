//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/quicksimeditor/instrumentpropertyeditor.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/quicksimeditor/instrumentpropertyeditor.h"
#include "gui2/mainwindow/styleutils.h"
#include "gui2/model/applicationmodels.h"
#include "gui2/model/instrumentitems.h"
#include "gui2/model/instrumentmodel.h"
#include "gui2/quicksimeditor/custombeampropertyeditorfactory.h"
#include "mvvm/viewmodel/viewmodeldelegate.h"
#include "mvvm/widgets/propertytreeview.h"
#include <QTreeView>
#include <QVBoxLayout>

using namespace ModelView;

namespace gui2 {

InstrumentPropertyEditor::InstrumentPropertyEditor(QWidget* parent)
    : QWidget(parent), m_beamPropertyEditor(new ModelView::PropertyTreeView)

{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_beamPropertyEditor);
}

InstrumentPropertyEditor::~InstrumentPropertyEditor() = default;

void InstrumentPropertyEditor::setModels(ApplicationModels* models)
{
    auto instrument = models->instrumentModel()->topItem<SpecularInstrumentItem>();

    auto delegate = std::make_unique<ViewModelDelegate>();
    delegate->setEditorFactory(std::make_unique<CustomBeamPropertyEditorFactory>(models));
    m_beamPropertyEditor->setViewModelDelegate(std::move(delegate));

    m_beamPropertyEditor->setItem(
        instrument->item<SpecularBeamItem>(SpecularInstrumentItem::P_BEAM));

    m_beamPropertyEditor->treeView()->setRootIsDecorated(true);
    m_beamPropertyEditor->treeView()->expandAll();
}

QSize InstrumentPropertyEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize InstrumentPropertyEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

} // namespace gui2
