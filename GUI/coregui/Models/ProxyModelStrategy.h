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

class SessionModel;
class ComponentProxyModel;
class SessionItem;

//! Base class for proxy strategies in ComponentProxyModel.

class BA_CORE_API_ ProxyModelStrategy
{
public:
    using map_t = QMap<QPersistentModelIndex, QPersistentModelIndex>;

    virtual ~ProxyModelStrategy() = default;

    void buildModelMap(SessionModel* source, ComponentProxyModel* proxy);
    virtual void onDataChanged(SessionModel* source, ComponentProxyModel* proxy);

    const map_t& sourceToProxy();
    const map_t& proxySourceParent();

    void setRootIndex(const QModelIndex& sourceRootIndex);

protected:
    QModelIndex createProxyIndex(ComponentProxyModel* proxy, int nrow, int ncol, void* adata);
    virtual void processSourceIndex(SessionModel* model, ComponentProxyModel* proxy,
                                    const QModelIndex& index) = 0;

    //!< Mapping of proxy model indices to indices in source model
    QMap<QPersistentModelIndex, QPersistentModelIndex> m_sourceToProxy;
    //!< Mapping of proxy model indices to indices of parent in source model
    QMap<QPersistentModelIndex, QPersistentModelIndex> m_proxySourceParent;

    QModelIndex m_sourceRootIndex;
};

//! Strategy for ComponentProxyModel which makes it identical to source model.

class BA_CORE_API_ IndentityProxyStrategy : public ProxyModelStrategy
{
protected:
    void processSourceIndex(SessionModel* model, ComponentProxyModel* proxy,
                            const QModelIndex& index);
};

//! Strategy for ComponentProxyModel which hides extra level of GroupProperty.

class BA_CORE_API_ ComponentProxyStrategy : public ProxyModelStrategy
{
public:
    void onDataChanged(SessionModel* source, ComponentProxyModel* proxy);

protected:
    void processSourceIndex(SessionModel* model, ComponentProxyModel* proxy,
                            const QModelIndex& index);
private:
    bool isGroupChildren(SessionItem* item);
    void processGroupItem(SessionItem* item, const QPersistentModelIndex& sourceIndex,
                          const QPersistentModelIndex& proxyIndex);

};

#endif  // ProxyModelStrategy
