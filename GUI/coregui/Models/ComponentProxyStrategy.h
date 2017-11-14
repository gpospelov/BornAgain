// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComponentProxyStrategy.h
//! @brief     Defines class ComponentProxyStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTPROXYSTRATEGY_H
#define COMPONENTPROXYSTRATEGY_H

#include "ProxyModelStrategy.h"

//! Strategy for ComponentProxyModel which hides extra level of GroupProperty.

class BA_CORE_API_ ComponentProxyStrategy : public ProxyModelStrategy
{
public:
    void onDataChanged(SessionModel* source, ComponentProxyModel* proxy);

protected:
    void processSourceIndex(const QModelIndex& index);
private:
    bool isGroupChildren(SessionItem* item);
    void processGroupItem(SessionItem* item, const QPersistentModelIndex& sourceIndex,
                          const QPersistentModelIndex& proxyIndex);
};

#endif  //  COMPONENTPROXYSTRATEGY_H
