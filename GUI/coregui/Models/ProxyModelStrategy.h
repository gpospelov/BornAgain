// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ProxyModelStrategy.h
//! @brief     Defines class ProxyModelStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROXYMODELSTRATEGY_H
#define PROXYMODELSTRATEGY_H

#include "WinDllMacros.h"
#include <QPersistentModelIndex>

class QAbstractItemModel;
class ComponentProxyModel;

//! Base class for proxy strategies in ComponentProxyModel.

class BA_CORE_API_ ProxyModelStrategy
{
public:
    using map_t = QMap<QPersistentModelIndex, QPersistentModelIndex>;

    virtual ~ProxyModelStrategy() = default;
    virtual void buildModelMap(QAbstractItemModel* source, ComponentProxyModel* proxy) = 0;

    const map_t& sourceToProxy();
    const map_t& proxySourceParent();

protected:
    QModelIndex createIndex(ComponentProxyModel* proxy, int nrow, int ncol, void* adata);

    //!< Mapping of proxy model indices to indices in source model
    QMap<QPersistentModelIndex, QPersistentModelIndex> m_sourceToProxy;
    //!< Mapping of proxy model indices to indices of parent in source model
    QMap<QPersistentModelIndex, QPersistentModelIndex> m_proxySourceParent;
};

//! Strategy for ComponentProxyModel which makes it identical to source model.

class BA_CORE_API_ IndentityProxyStrategy : public ProxyModelStrategy
{
public:
    void buildModelMap(QAbstractItemModel* source, ComponentProxyModel* proxy);
};

#endif  // ProxyModelStrategy
