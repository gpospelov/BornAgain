//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/layereditor/layereditorwidget.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/layereditor/layereditorwidget.h"
#include "gui2/layereditor/customlayertreeeditorfactory.h"
#include "gui2/layereditor/layerselectionmodel.h"
#include "gui2/layereditor/layertreeview.h"
#include "gui2/layereditor/layerviewmodel.h"
#include "gui2/model/applicationmodels.h"
#include "gui2/model/sampleitems.h"
#include "gui2/model/samplemodel.h"
#include "mvvm/viewmodel/viewmodeldelegate.h"
#include <QVBoxLayout>

namespace gui2 {

LayerEditorWidget::LayerEditorWidget(QWidget* parent)
    : QWidget(parent)
    , m_layerView(new LayerTreeView)
    , m_delegate(std::make_unique<ModelView::ViewModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_layerView);
    setLayout(layout);
    m_layerView->setItemDelegate(m_delegate.get());
}

LayerEditorWidget::~LayerEditorWidget() = default;

void LayerEditorWidget::setModels(ApplicationModels* models)
{
    m_viewModel = std::make_unique<LayerViewModel>(models->sampleModel());
    m_selectionModel = new LayerSelectionModel(m_viewModel.get(), this);

    m_delegate->setEditorFactory(std::make_unique<CustomLayerTreeEditorFactory>(models));
    m_viewModel->setRootSessionItem(models->sampleModel()->topItem<MultiLayerItem>());
    m_layerView->setModel(m_viewModel.get());
    m_layerView->setSelectionModel(m_selectionModel);
}

LayerSelectionModel* LayerEditorWidget::selectionModel() const
{
    return m_selectionModel;
}

} // namespace gui2
