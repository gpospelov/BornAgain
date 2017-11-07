// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComponentProxyModel.cpp
//! @brief     Implements class ComponentProxyModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentProxyModel.h"
#include "SessionModel.h"

ComponentProxyModel::ComponentProxyModel(QObject* parent)
    : QAbstractProxyModel(parent)
    , m_model(nullptr)
{

}

void ComponentProxyModel::setSessionModel(SessionModel* model)
{
    m_model = model;
}

QModelIndex ComponentProxyModel::mapToSource(const QModelIndex& proxyIndex) const
{
    Q_UNUSED(proxyIndex);
    return QModelIndex();
}

QModelIndex ComponentProxyModel::mapFromSource(const QModelIndex& sourceIndex) const
{
    Q_UNUSED(sourceIndex);
    return QModelIndex();
}

QModelIndex ComponentProxyModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return QModelIndex();
}

QModelIndex ComponentProxyModel::parent(const QModelIndex& child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int ComponentProxyModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 0;
}

int ComponentProxyModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 0;
}

