// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ProxyModelStrategy.cpp
//! @brief     Implements class ProxyModelStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ProxyModelStrategy.h"
#include "ModelUtils.h"
#include "ComponentProxyModel.h"
#include "SessionModel.h"
#include "SessionItem.h"
#include "ModelPath.h"
#include "GroupItem.h"

void ProxyModelStrategy::buildModelMap(SessionModel* source, ComponentProxyModel* proxy)
{
    m_sourceToProxy.clear();
    m_proxySourceParent.clear();

    ModelUtils::iterate(m_sourceRootIndex, source, [=](const QModelIndex& index) {
        processSourceIndex(source, proxy, index);
    });
}

void ProxyModelStrategy::onDataChanged(SessionModel* source, ComponentProxyModel* proxy)
{
    Q_UNUSED(source);
    Q_UNUSED(proxy);
    // we do not expect here change of model layout
}

const ProxyModelStrategy::map_t& ProxyModelStrategy::sourceToProxy() { return m_sourceToProxy; }

const ProxyModelStrategy::map_t& ProxyModelStrategy::proxySourceParent()
{
    return m_proxySourceParent;
}

void ProxyModelStrategy::setRootIndex(const QModelIndex& sourceRootIndex)
{
    m_sourceRootIndex = sourceRootIndex;
}

//! Method to ask proxy to create an index using friendship of ProxyModelStrategy
//! and ComponentProxyModel.

QModelIndex ProxyModelStrategy::createProxyIndex(ComponentProxyModel* proxy, int nrow, int ncol,
                                                 void* adata)
{
    return proxy->createIndex(nrow, ncol, adata);
}

//! Builds one-to-one mapping for source and proxy.

void IndentityProxyStrategy::processSourceIndex(SessionModel* model, ComponentProxyModel* proxy,
                                                const QModelIndex& index)
{
    Q_UNUSED(model);

    QPersistentModelIndex proxyIndex
        = createProxyIndex(proxy, index.row(), index.column(), index.internalPointer());
    m_sourceToProxy.insert(QPersistentModelIndex(index), proxyIndex);

    QPersistentModelIndex sourceParent;
    if (index.parent().isValid())
        sourceParent = index.parent();

    m_proxySourceParent.insert(proxyIndex, sourceParent);
}

void ComponentProxyStrategy::onDataChanged(SessionModel* source, ComponentProxyModel* proxy)
{
    buildModelMap(source, proxy);
    proxy->layoutChanged();
}

void ComponentProxyStrategy::processSourceIndex(SessionModel* model, ComponentProxyModel* proxy,
                                                const QModelIndex& index)
{
    QPersistentModelIndex sourceIndex = QPersistentModelIndex(index);
    QPersistentModelIndex proxyIndex
        = createProxyIndex(proxy, index.row(), index.column(), index.internalPointer());

    SessionItem* item = model->itemForIndex(index);

    if (item->index() == m_sourceRootIndex) {
        // if index is desired new source
        proxyIndex = createProxyIndex(proxy, 0, index.column(), index.internalPointer());
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
