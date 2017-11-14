// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComponentProxyStrategy.cpp
//! @brief     Implements class ComponentProxyStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentProxyStrategy.h"
#include "ComponentProxyModel.h"
#include "SessionModel.h"
#include "SessionItem.h"
#include "ModelPath.h"
#include "GroupItem.h"

void ComponentProxyStrategy::onDataChanged(SessionModel* source, ComponentProxyModel* proxy)
{
    buildModelMap(source, proxy);
    proxy->layoutChanged();
}

void ComponentProxyStrategy::processSourceIndex(const QModelIndex& index)
{
    QPersistentModelIndex sourceIndex = QPersistentModelIndex(index);

    SessionItem* item = m_source->itemForIndex(index);

    if (isNewRootItem(item)) {
        processRootItem(item, sourceIndex);

    } else if (isGroupChildren(item)) {
        processGroupItem(item, sourceIndex);

    } else {
        processDefaultItem(item, sourceIndex);
    }
}

//! Returns true if item should become new root item.
//! This is used when we want to show single item (Layer, Particle) on top of the tree.

bool ComponentProxyStrategy::isNewRootItem(SessionItem* item)
{
    return item->index() == m_sourceRootIndex;
}

//! Makes SessionItem to be come the only one item in a tree.

void ComponentProxyStrategy::processRootItem(SessionItem* item,
                                             const QPersistentModelIndex& sourceIndex)
{
    const int nrows = 0; // invisible root item will contain only single item
    QPersistentModelIndex proxyIndex = createProxyIndex(nrows, sourceIndex.column(), item);
    m_sourceToProxy.insert(sourceIndex, proxyIndex);
    m_proxySourceParent.insert(proxyIndex, QModelIndex()); // new parent will be root
}

bool ComponentProxyStrategy::isGroupChildren(SessionItem* item)
{
    if (item->parent() && item->parent()->modelType() == Constants::GroupItemType)
        return true;

    if (const SessionItem* ancestor = ModelPath::ancestor(item, Constants::GroupItemType)) {
        if (ancestor != item)
            return true;
    }

    return false;
}

void ComponentProxyStrategy::processGroupItem(SessionItem* item,
                                              const QPersistentModelIndex& sourceIndex)
{
    if (const SessionItem* ancestor = ModelPath::ancestor(item, Constants::GroupItemType)) {
        if (ancestor == item)
            return;

        auto groupItem = dynamic_cast<const GroupItem*>(ancestor);
        if (item->parent() == groupItem->currentItem()) {
            QPersistentModelIndex proxyIndex
                = createProxyIndex(sourceIndex.row(), sourceIndex.column(), sourceIndex.internalPointer());

            m_sourceToProxy.insert(sourceIndex, proxyIndex);
            m_proxySourceParent.insert(proxyIndex, groupItem->index());
        }

    }
}

void ComponentProxyStrategy::processDefaultItem(SessionItem* item,
                                                const QPersistentModelIndex& sourceIndex)
{
    QPersistentModelIndex proxyIndex
        = createProxyIndex(sourceIndex.row(), sourceIndex.column(), item);

    m_sourceToProxy.insert(sourceIndex, proxyIndex);

    QPersistentModelIndex sourceParent;
    if (sourceIndex.parent().isValid())
        sourceParent = sourceIndex.parent();

    m_proxySourceParent.insert(proxyIndex, sourceParent);
}
