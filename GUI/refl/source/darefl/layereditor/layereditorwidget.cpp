// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <darefl/layereditor/customlayertreeeditorfactory.h>
#include <darefl/layereditor/layereditorwidget.h>
#include <darefl/layereditor/layerselectionmodel.h>
#include <darefl/layereditor/layertreeview.h>
#include <darefl/layereditor/layerviewmodel.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/sampleitems.h>
#include <darefl/model/samplemodel.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>

namespace DaRefl {

LayerEditorWidget::LayerEditorWidget(QWidget* parent)
    : QWidget(parent)
    , m_layerView(new LayerTreeView)
    , m_delegate(std::make_unique<ModelView::ViewModelDelegate>()) {
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_layerView);
    setLayout(layout);
    m_layerView->setItemDelegate(m_delegate.get());
}

LayerEditorWidget::~LayerEditorWidget() = default;

void LayerEditorWidget::setModels(ApplicationModels* models) {
    m_viewModel = std::make_unique<LayerViewModel>(models->sampleModel());
    m_selectionModel = new LayerSelectionModel(m_viewModel.get(), this);

    m_delegate->setEditorFactory(std::make_unique<CustomLayerTreeEditorFactory>(models));
    m_viewModel->setRootSessionItem(models->sampleModel()->topItem<MultiLayerItem>());
    m_layerView->setModel(m_viewModel.get());
    m_layerView->setSelectionModel(m_selectionModel);
}

LayerSelectionModel* LayerEditorWidget::selectionModel() const {
    return m_selectionModel;
}

} // namespace DaRefl
