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

void ProxyModelStrategy::buildModelMap(SessionModel* source, ComponentProxyModel* proxy)
{
    m_sourceToProxy.clear();
    m_proxySourceParent.clear();

    ModelUtils::iterate(m_sourceRootIndex, source, [=](const QModelIndex& index) {
        processSourceIndex(source, proxy, index);
    });

    // kind of hack since we have to visit col=1 which has QModelIndex() parent
    if (m_sourceRootIndex.isValid())
        processSourceIndex(source, proxy, m_sourceRootIndex.sibling(m_sourceRootIndex.row(), 1));
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
