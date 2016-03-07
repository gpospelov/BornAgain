// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TestItem.cpp
//! @brief     Implements class TestItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ModelMapper.h"
#include "SessionModel.h"
#include "SessionItem.h"

#include <QModelIndex>

ModelMapper::ModelMapper(QObject *parent)
    : QObject(parent)
    , m_active {true}
    , m_model(0)
    , m_item(0)
{
}

void ModelMapper::setItem(SessionItem *item)
{
    if (item) {
        m_item = item;
        setModel(item->model());
    }
}

void ModelMapper::setOnPropertyChange(std::function<void (QString)> f)
{
    m_onPropertyChange.push_back(f);
}

void ModelMapper::setOnChildPropertyChange(std::function<void (SessionItem *, QString)> f)
{
    m_onChildPropertyChange.push_back(f);
}

void ModelMapper::setOnParentChange(std::function<void (SessionItem *)> f)
{
    m_onParentChange.push_back(f);
}

void ModelMapper::setOnChildrenChange(std::function<void ()> f)
{
    m_onChildrenChange.push_back(f);
}

void ModelMapper::setModel(SessionModel *model)
{
    if (m_model) {
        disconnect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                   this, SLOT(onDataChanged(QModelIndex,QModelIndex,QVector<int>)));
        disconnect(m_model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                   this, SLOT(onRowsInserted(QModelIndex,int,int)));
        disconnect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
                this, SLOT(onBeginRemoveRows(QModelIndex,int,int)));
    }
    if (model) {
        m_model = model;
        connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                   this, SLOT(onDataChanged(QModelIndex,QModelIndex,QVector<int>)));
        connect(m_model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                   this, SLOT(onRowsInserted(QModelIndex,int,int)));
        connect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
                this, SLOT(onBeginRemoveRows(QModelIndex,int,int)));
    }
}

int ModelMapper::nestlingDepth(SessionItem *item, int level)
{
    if (item == nullptr || item == m_model->rootItem())
        return -1;
    if (item == m_item)
        return level;
    return nestlingDepth(item->parent(), level + 1);

}

void ModelMapper::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                const QVector<int> &roles)
{
    if (topLeft.parent() != bottomRight.parent())
        return; // range must be from the same parent
    SessionItem *item = m_model->itemForIndex(topLeft);
    int nestling = nestlingDepth(item);
    if (nestling > 0 && nestling < 2) {
        // something happened with our property or group item
        if (SessionItem *item = m_model->itemForIndex(topLeft)) {
            if (m_item->isRegisteredTag(item->itemName())) {
                // some property changed
                if (m_active && m_onPropertyChange.size() > 0) {
                    for (auto f : m_onPropertyChange) {
                        f(item->itemName());
                    }
                }
            }
        }
    }
    if (nestling > 1) {
        if (SessionItem *parent = item->parent()) {
            if (parent->isRegisteredTag(item->itemName())) {
                if (m_active && m_onChildPropertyChange.size() > 0) {
                    for (auto f : m_onChildPropertyChange) {
                        f(parent, item->itemName());
                    }
                }
            }
        }
    }
}

void ModelMapper::onRowsInserted(const QModelIndex &parent, int first, int last)
{
    if (parent.isValid()) {
        if (SessionItem *newChild = m_model->itemForIndex(parent.child(first, 0))) {
            if (m_item == newChild) {
                if (m_active && m_onParentChange.size() > 0) {
                    for (auto f : m_onParentChange) {
                        f(m_model->itemForIndex(parent));
                    }
                }

                if (m_active && m_onChildrenChange.size() > 0) {
                    for (auto f : m_onChildrenChange) {
                        f();
                    }
                }
            }
        }
    }
}

void ModelMapper::onBeginRemoveRows(const QModelIndex &parent, int first, int last)
{
    if (parent.isValid()) {
        if (SessionItem *newChild = m_model->itemForIndex(parent.child(first, 0))) {
            if (m_item == newChild) {
                if (m_active && m_onParentChange.size() > 0) {
                    for (auto f : m_onParentChange) {
                        f(nullptr);
                    }
                }
                if (m_active && m_onChildrenChange.size() > 0) {
                    for (auto f : m_onChildrenChange) {
                        f();
                    }
                }
            }
        }
    }
}
