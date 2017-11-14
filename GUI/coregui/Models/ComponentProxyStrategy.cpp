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
    QPersistentModelIndex proxyIndex
        = createProxyIndex(index.row(), index.column(), index.internalPointer());

    SessionItem* item = m_source->itemForIndex(index);

    if (item->index() == m_sourceRootIndex) {
        // if index is desired new source
        proxyIndex = createProxyIndex(0, index.column(), index.internalPointer());
        m_sourceToProxy.insert(sourceIndex, proxyIndex);
        m_proxySourceParent.insert(proxyIndex, QModelIndex()); // new parent will be root

    } else if (isGroupChildren(item)) {
        // do parent substitution here
        processGroupItem(item, sourceIndex, proxyIndex);
    } else {
        m_sourceToProxy.insert(sourceIndex, proxyIndex);

        QPersistentModelIndex sourceParent;
        if (index.parent().isValid())
            sourceParent = index.parent();

        m_proxySourceParent.insert(proxyIndex, sourceParent);
    }
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
                                              const QPersistentModelIndex& sourceIndex,
                                              const QPersistentModelIndex& proxyIndex)
{
    if (const SessionItem* ancestor = ModelPath::ancestor(item, Constants::GroupItemType)) {
        if (ancestor == item)
            return;

        auto groupItem = dynamic_cast<const GroupItem*>(ancestor);
        if (item->parent() == groupItem->currentItem()) {
            m_sourceToProxy.insert(sourceIndex, proxyIndex);
            m_proxySourceParent.insert(proxyIndex, groupItem->index());
        }

    }
}
