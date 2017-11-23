// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentTreeView.cpp
//! @brief     Implements class ComponentTreeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentTreeView.h"
#include "ComponentProxyModel.h"
#include "StyleUtils.h"
#include "SessionModelDelegate.h"
#include "SessionModel.h"
#include <QTreeView>
#include <QBoxLayout>
#include <QStandardItemModel>

ComponentTreeView::ComponentTreeView(QWidget* parent)
    : ComponentView(parent)
    , m_tree(new QTreeView)
    , m_delegate(new SessionModelDelegate(this))
    , m_proxyModel(new ComponentProxyModel(this))
    , m_placeHolderModel(new QStandardItemModel)
    , m_show_root_item(false)
{
    auto layout = new QVBoxLayout;

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_tree);

    setLayout(layout);

    QStringList labels = {"Name", "Value"};
    m_placeHolderModel->setHorizontalHeaderLabels(labels);

    StyleUtils::setPropertyStyle(m_tree);
    m_tree->setRootIsDecorated(false);
    m_tree->setModel(m_placeHolderModel);
    m_tree->setItemDelegate(m_delegate);
    m_tree->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

void ComponentTreeView::setItem(SessionItem* item)
{
    setItemIntern(item, m_show_root_item);
}

//! Sets item to show in the tree together with its properties and group properties.
//! @param item: Item to show in a tree.
//! @param show_root_item: Tree will starts from item itself, if true.

void ComponentTreeView::setItemIntern(SessionItem* item, bool show_root_item)
{
    if (!item) {
        setModel(nullptr);
        return;
    }
    setModel(item->model());
    setRootIndex(item->index(), show_root_item);
    m_tree->expandAll();
}

void ComponentTreeView::clearEditor()
{
    m_tree->setModel(m_placeHolderModel);
}

void ComponentTreeView::setModel(SessionModel* model)
{
    m_proxyModel->setSessionModel(model);
    if (model)
        m_tree->setModel(m_proxyModel);
    else
        m_tree->setModel(m_placeHolderModel);
}

void ComponentTreeView::setRootIndex(const QModelIndex& index, bool show_root_item)
{
    if (QWidget* editor = m_tree->indexWidget(m_tree->currentIndex()))
        m_delegate->closeEditor(editor, QAbstractItemDelegate::NoHint);
    Q_ASSERT(m_proxyModel);
    m_proxyModel->setRootIndex(index);
    if (!show_root_item)
        m_tree->setRootIndex(m_proxyModel->mapFromSource(index));
}

QTreeView* ComponentTreeView::treeView()
{
    return m_tree;
}

void ComponentTreeView::setHeaderHidden(bool hide)
{
    m_tree->setHeaderHidden(hide);
}

void ComponentTreeView::setShowRootItem(bool show)
{
    m_show_root_item = show;
}

