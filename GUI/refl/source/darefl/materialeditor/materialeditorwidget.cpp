// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <darefl/materialeditor/materialeditorwidget.h>
#include <darefl/materialeditor/materialselectionmodel.h>
#include <darefl/materialeditor/materialtableview.h>
#include <darefl/materialeditor/materialtreeview.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/materialitems.h>
#include <darefl/model/materialmodel.h>
#include <mvvm/factories/viewmodelfactory.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>

namespace DaRefl {

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

} // namespace DaRefl
