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
#include "ParameterizedItem.h"

#include <QModelIndex>

ModelMapper::ModelMapper(QObject *parent)
    : QObject(parent)
    , m_model(0)
    , m_item(0)
{
    if (ParameterizedItem *item = dynamic_cast<ParameterizedItem *>(parent)) {
        setItem(item);
    }
}

void ModelMapper::setItem(ParameterizedItem *item)
{
    if (item) {
        m_item = item;
        setModel(item->model());
    }
}

void ModelMapper::setModel(SessionModel *model)
{
    if (m_model) {
        disconnect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                   this, SLOT(onDataChanged(QModelIndex,QModelIndex,QVector<int>)));
        disconnect(m_model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                   this, SLOT(onRowsInserted(QModelIndex,int,int)));
    }
    if (model) {
        m_model = model;
        connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                   this, SLOT(onDataChanged(QModelIndex,QModelIndex,QVector<int>)));
        connect(m_model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                   this, SLOT(onRowsInserted(QModelIndex,int,int)));
    }
}

int ModelMapper::nestlingDepth(ParameterizedItem *item, int level)
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
    ParameterizedItem *item = m_model->itemForIndex(topLeft);
    int nestling = nestlingDepth(item);
    if (nestling > 0 && nestling < 2) {
        // something happened with our property or group item
        if (ParameterizedItem *item = m_model->itemForIndex(topLeft)) {
            if (m_item->isRegisteredProperty(item->itemName())) {
                // some property changed
                if (m_onPropertyChange)
                    m_onPropertyChange(item->itemName());
            }
        }
    }
    if (nestling > 0) {
        if (ParameterizedItem *parent = item->parent()) {
            if (parent->isRegisteredProperty(item->itemName())) {
                if (m_onChildPropertyChange)
                    m_onChildPropertyChange(parent, item->itemName());
            }
        }
    }
}

void ModelMapper::onRowsInserted(const QModelIndex &parent, int first, int last)
{

}
