// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ModelMapper.cpp
//! @brief     Implements class ModelMapper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SessionModel.h"

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

void ModelMapper::setOnValueChange(std::function<void(void)> f, const void *caller)
{
    m_onValueChange.push_back(call_t(f, caller));
}

void ModelMapper::setOnPropertyChange(std::function<void(QString)> f, const void *caller)
{
    m_onPropertyChange.push_back(call_str_t(f, caller));
}

void ModelMapper::setOnChildPropertyChange(std::function<void (SessionItem *, QString)> f, const void *caller)
{
    m_onChildPropertyChange.push_back(call_item_str_t(f, caller));
}

void ModelMapper::setOnParentChange(std::function<void (SessionItem *)> f, const void *caller)
{
    m_onParentChange.push_back(call_item_t(f, caller));
}

void ModelMapper::setOnChildrenChange(std::function<void(SessionItem *)> f, const void *caller)
{
    m_onChildrenChange.push_back(call_item_t(f, caller));
}

void ModelMapper::setOnSiblingsChange(std::function<void ()> f, const void *caller)
{
    m_onSiblingsChange.push_back(call_t(f, caller));
}

void ModelMapper::setOnAnyChildChange(std::function<void (SessionItem *)> f, const void *caller)
{
    m_onAnyChildChange.push_back(call_item_t(f, caller));
}

void ModelMapper::setOnItemDestroy(std::function<void (SessionItem *)> f, const void *caller)
{
    m_onItemDestroy.push_back(call_item_t(f, caller));
}

//! Cancells all subscribtion of given caller
void ModelMapper::unsubscribe(const void *caller)
{
    clean_container(m_onValueChange, caller);
    clean_container(m_onPropertyChange, caller);
    clean_container(m_onChildPropertyChange, caller);
    clean_container(m_onParentChange, caller);
    clean_container(m_onChildrenChange, caller);
    clean_container(m_onSiblingsChange, caller);
    clean_container(m_onAnyChildChange, caller);
    clean_container(m_onItemDestroy, caller);
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
        disconnect(m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)),
                this, SLOT(onRowRemoved(QModelIndex,int,int)));
    }

    m_model = model;

    if (m_model) {
        connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                   this, SLOT(onDataChanged(QModelIndex,QModelIndex,QVector<int>)));
        connect(m_model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                   this, SLOT(onRowsInserted(QModelIndex,int,int)));
        connect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
                this, SLOT(onBeginRemoveRows(QModelIndex,int,int)));
        connect(m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)),
                this, SLOT(onRowRemoved(QModelIndex,int,int)));
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

void ModelMapper::callOnValueChange()
{
    if (m_active && m_onValueChange.size() > 0) {
        for (auto f : m_onValueChange) {
            f.first();
        }
    }
//    if(m_active) emit valueChange();
}

void ModelMapper::callOnPropertyChange(const QString &name)
{
    if (m_active && m_onPropertyChange.size() > 0) {
        for (auto f : m_onPropertyChange) {
            f.first(name);
        }
    }
//    if(m_active) emit propertyChange(name);
}

void ModelMapper::callOnChildPropertyChange(SessionItem *item, const QString &name)
{
    if (m_active && m_onChildPropertyChange.size() > 0) {
        for (auto f : m_onChildPropertyChange) {
            f.first(item, name);
        }
    }
//    if(m_active) emit childPropertyChange(item, name);
}

void ModelMapper::callOnParentChange(SessionItem *new_parent)
{
    if (m_active && m_onParentChange.size() > 0) {
        for (auto f : m_onParentChange) {
            f.first(new_parent);
        }
    }
//    if(m_active) emit parentChange(new_parent);
}

void ModelMapper::callOnChildrenChange(SessionItem *item)
{
    if (m_active && m_onChildrenChange.size() > 0) {
        for (auto f : m_onChildrenChange) {
            f.first(item);
        }
    }
//    if(m_active) emit childrenChange(item);
}

void ModelMapper::callOnSiblingsChange()
{
    if (m_active && m_onSiblingsChange.size() > 0) {
        for (auto f : m_onSiblingsChange) {
            f.first();
        }
    }
//    if(m_active) emit siblingsChange();
}

void ModelMapper::callOnAnyChildChange(SessionItem *item)
{
    if (m_active && m_onAnyChildChange.size() > 0) {
        for (auto f : m_onAnyChildChange) {
            f.first(item);
        }
    }
//    if(m_active) emit anyChildChange(item);
}

//! Notifies subscribers if an item owning given mapper is about to be destroyed
void ModelMapper::callOnItemDestroy()
{
    if (m_active && m_onItemDestroy.size() > 0) {
        for (auto f : m_onItemDestroy) {
            f.first(m_item);
        }
    }
//    if(m_active) emit itemDestroy(new_parent);
}

void ModelMapper::clearMapper()
{
    m_item = 0;
    setModel(0);
    m_onValueChange.clear();
    m_onPropertyChange.clear();
    m_onChildPropertyChange.clear();
    m_onParentChange.clear();
    m_onChildrenChange.clear();
    m_onSiblingsChange.clear();
    m_onAnyChildChange.clear();
    m_onItemDestroy.clear();
}

void ModelMapper::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                const QVector<int> &/*roles*/)
{
    Q_ASSERT(m_item);

    if (topLeft.parent() != bottomRight.parent())
        return; // range must be from the same parent

    SessionItem *item = m_model->itemForIndex(topLeft);

    int nestling = nestlingDepth(item);
    if (nestling == 0) {
        callOnValueChange();
    }
    if (nestling == 1) {
        // something happened with our children
        if (SessionItem *item = m_model->itemForIndex(topLeft)) {
            // only care f
            const QString tag = m_item->tagFromItem(item);
            if (!tag.isEmpty()) {
                callOnPropertyChange(tag);
            }
        }
    }
    if (nestling > 1) {
        if (SessionItem *parent = item->parent()) {
            const QString tag = parent->tagFromItem(item);
            if (!tag.isEmpty()) {
                callOnChildPropertyChange(parent, tag);
            }
        }
    }
    if (nestling > 0) {
        callOnAnyChildChange(item);
    }
}

void ModelMapper::onRowsInserted(const QModelIndex &parent, int first, int /*last*/)
{
    Q_ASSERT(m_item);

    SessionItem *newChild = m_model->itemForIndex(parent.child(first, 0));

    int nestling = nestlingDepth(newChild);

    if (newChild) {
        if (m_item == newChild) {
            callOnParentChange(m_model->itemForIndex(parent));
        }
    }
    if (nestling == 1) {

        callOnChildrenChange(newChild);

        // inform siblings about the change
        // FIXME SessionItems with invalid parent index (i.e. IView's located on top of graphics scene like ParticleView) should be also notified to update the label
//        if(SessionItem *parent = newChild->parent()) {
//            QVector<SessionItem *> items = parent->getChildrenOfType(newChild->modelType());
//            foreach(SessionItem *sibling, items) {
//                if(m_item == sibling) callOnSiblingsChange();
//            }
//        }
    }

    if(SessionItem *parent = newChild->parent()) {
        QVector<SessionItem *> items = parent->getChildrenOfType(newChild->modelType());
        foreach(SessionItem *sibling, items) {
            if(m_item == sibling)
                callOnSiblingsChange();
        }
    }


    if (nestling > 0) {
        callOnAnyChildChange(newChild);
    }
}

void ModelMapper::onBeginRemoveRows(const QModelIndex &parent, int first, int /*last*/)
{
    Q_ASSERT(m_item);
    SessionItem *oldChild = m_model->itemForIndex(parent.child(first, 0));

    int nestling = nestlingDepth(m_model->itemForIndex(parent));

    if (oldChild) {
        if (m_item == oldChild) {
            callOnParentChange(0);
        }
        if (nestling == 0) {

            callOnChildrenChange(0);

            // inform siblings about the change
//            if(SessionItem *parent = oldChild->parent()) {
//                QVector<SessionItem *> items = parent->getChildrenOfType(oldChild->modelType());
//                foreach(SessionItem *sibling, items) {
//                    if(m_item == sibling) callOnSiblingsChange();
//                }
//            }
        }

//        if(SessionItem *parent = oldChild->parent()) {
//            QVector<SessionItem *> items = parent->getChildrenOfType(oldChild->modelType());
//            foreach(SessionItem *sibling, items) {
//                if(m_item == sibling)
//                    callOnSiblingsChange();
//            }
//        }


    }

    if (m_item == oldChild) {
        m_aboutToDelete = parent.child(first, 0);
    }
}

void ModelMapper::onRowRemoved(const QModelIndex &parent, int first, int /*last*/)
{
    int nestling = nestlingDepth(m_model->itemForIndex(parent));

    if (nestling >= 0 || m_model->itemForIndex(parent) == m_item->parent()) {
        callOnAnyChildChange(nullptr);
        callOnSiblingsChange();

    }

    if(m_aboutToDelete.isValid() && m_aboutToDelete == parent.child(first, 0)) {
        clearMapper();

    }
}
