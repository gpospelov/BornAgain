//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/importdataview/dataselectorwidget.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/importdataview/dataselectorwidget.h"
#include "gui2/importdataview/dataselectionmodel.h"
#include "gui2/importdataview/dataviewmodel.h"
#include "gui2/model/experimentaldataitems.h"
#include "mvvm/standarditems/graphitem.h"
#include "mvvm/widgets/collapsiblelistwidget.h"
#include "mvvm/widgets/standardtreeviews.h"
#include "mvvm/widgets/widgetutils.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSplitter>
#include <QTreeView>
#include <QVBoxLayout>

namespace gui2 {

DataSelectorWidget::DataSelectorWidget(DataViewModel* view_model, QWidget* parent)
    : QWidget(parent)
    , m_viewModel(view_model)
    , m_selectionModel(new DataSelectionModel(m_viewModel, this))
    , m_selectorTree(new QTreeView)
    , m_canvasPropertyEditor(new ModelView::PropertyTreeView)
    , m_graphPropertyEditor(new ModelView::PropertyTreeView)
    , m_collapsibleWidget(new ModelView::CollapsibleListWidget)
{
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

DataSelectionModel* DataSelectorWidget::selectionModel() const
{
    return m_selectionModel;
}

void DataSelectorWidget::onSelectionChanged()
{
    m_canvasPropertyEditor->setItem(m_selectionModel->activeCanvas());
    m_graphPropertyEditor->setItem(m_selectionModel->selectedGraph());

    selectionChanged(); // emmit further
}

} // namespace gui2
