//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/materialeditor/materialeditorwidget.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/materialeditor/materialeditorwidget.h"
#include "gui2/materialeditor/materialselectionmodel.h"
#include "gui2/materialeditor/materialtableview.h"
#include "gui2/materialeditor/materialtreeview.h"
#include "gui2/model/applicationmodels.h"
#include "gui2/model/materialitems.h"
#include "gui2/model/materialmodel.h"
#include "mvvm/factories/viewmodelfactory.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/viewmodel/viewmodeldelegate.h"
#include <QVBoxLayout>

namespace gui2 {

MaterialEditorWidget::MaterialEditorWidget(QWidget* parent)
    : QWidget(parent)
    , m_materialView(new MaterialTreeView)
    , m_delegate(std::make_unique<ModelView::ViewModelDelegate>()) {
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_materialView);
    setLayout(layout);
    m_materialView->setItemDelegate(m_delegate.get());
}

MaterialEditorWidget::~MaterialEditorWidget() = default;

void MaterialEditorWidget::setModels(ApplicationModels* models) {
    m_materialModel = models->materialModel();
    m_viewModel = ModelView::Factory::CreatePropertyTableViewModel(m_materialModel);
    m_selectionModel = new MaterialSelectionModel(m_viewModel.get(), this);
    m_viewModel->setRootSessionItem(
        ModelView::Utils::TopItem<MaterialContainerItem>(m_materialModel));
    m_materialView->setModel(m_viewModel.get());
    m_materialView->setSelectionModel(m_selectionModel);
}

MaterialSelectionModel* MaterialEditorWidget::selectionModel() const {
    return m_selectionModel;
}

} // namespace gui2
