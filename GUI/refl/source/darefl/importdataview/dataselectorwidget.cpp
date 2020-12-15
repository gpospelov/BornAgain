// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QHBoxLayout>
#include <QLabel>
#include <QSplitter>
#include <QTreeView>
#include <QVBoxLayout>
#include <darefl/importdataview/dataselectionmodel.h>
#include <darefl/importdataview/dataselectorwidget.h>
#include <darefl/importdataview/dataviewmodel.h>
#include <darefl/model/experimentaldataitems.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/widgets/collapsiblelistwidget.h>
#include <mvvm/widgets/standardtreeviews.h>
#include <mvvm/widgets/widgetutils.h>

namespace DaRefl {

DataSelectorWidget::DataSelectorWidget(DataViewModel* view_model, QWidget* parent)
    : QWidget(parent)
    , m_viewModel(view_model)
    , m_selectionModel(new DataSelectionModel(m_viewModel, this))
    , m_selectorTree(new QTreeView)
    , m_canvasPropertyEditor(new ModelView::PropertyTreeView)
    , m_graphPropertyEditor(new ModelView::PropertyTreeView)
    , m_collapsibleWidget(new ModelView::CollapsibleListWidget) {
    auto layout = new QVBoxLayout(this);

    m_collapsibleWidget->addWidget(m_selectorTree, "Canvas list");
    m_collapsibleWidget->addWidget(m_canvasPropertyEditor, "Canvas properties",
                                   /*set_collapsed*/ true);
    m_collapsibleWidget->addWidget(m_graphPropertyEditor, "Graph properties",
                                   /*set_collapsed*/ true);

    layout->addWidget(m_collapsibleWidget);

    m_selectorTree->setModel(m_viewModel);
    m_selectorTree->setSelectionModel(m_selectionModel);
    m_selectorTree->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_selectorTree->setDragDropMode(QAbstractItemView::InternalMove);
    m_selectorTree->setDragEnabled(true);

    connect(selectionModel(), &DataSelectionModel::selectionChanged, this,
            &DataSelectorWidget::onSelectionChanged);
}

DataSelectionModel* DataSelectorWidget::selectionModel() const {
    return m_selectionModel;
}

void DataSelectorWidget::onSelectionChanged() {
    m_canvasPropertyEditor->setItem(m_selectionModel->activeCanvas());
    m_graphPropertyEditor->setItem(m_selectionModel->selectedGraph());

    selectionChanged(); // emmit further
}

} // namespace DaRefl
