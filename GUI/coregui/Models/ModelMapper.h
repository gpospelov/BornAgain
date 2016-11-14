// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ModelMapper.h
//! @brief     Defines class ModelMapper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MODELMAPPER_H
#define MODELMAPPER_H

#include "WinDllMacros.h"
#include <QModelIndex>
#include <functional>

class SessionModel;
class SessionItem;


class BA_CORE_API_ ModelMapper : public QObject
{
    Q_OBJECT
public:
    ModelMapper(QObject *parent = 0);

    void setItem(SessionItem* item);

    void setOnValueChange(std::function<void(void)> f, const void *caller=0);

    void setOnPropertyChange(std::function<void(QString)> f, const void *caller=0);

    void setOnChildPropertyChange(std::function<void(SessionItem*,QString)> f, const void *caller=0);

    void setOnParentChange(std::function<void(SessionItem*)> f, const void *caller=0);

    void setOnChildrenChange(std::function<void(SessionItem*)> f, const void *caller=0);

    void setOnSiblingsChange(std::function<void(void)> f, const void *caller=0);

    void setOnAnyChildChange(std::function<void(SessionItem*)> f, const void *caller=0);

    void setActive(bool state) {m_active = state;}

    void setOnItemDestroy(std::function<void(SessionItem*)> f, const void *caller=0);

    void unsubscribe(const void *caller);

    void callOnItemDestroy();

signals:
    void valueChange();
    void propertyChange(const QString &name);
    void childPropertyChange(SessionItem *item, const QString &name);
    void parentChange(SessionItem *item);
    void childrenChange(SessionItem *item);
    void siblingsChange();
    void anyChildChange(SessionItem *item);
    void itemDestroy(SessionItem *item);

public slots:
    void onDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight,
                       const QVector<int> & roles = QVector<int> ());

    void onRowsInserted(const QModelIndex & parent, int first, int last);

    void onBeginRemoveRows(const QModelIndex & parent, int first, int last);

    void onRowRemoved(const QModelIndex & parent, int first, int last);

private:
    //! removes all callbacks related to given caller
    template<class U> void clean_container(U& v, const void *caller);

    void setModel(SessionModel *model);
    int nestlingDepth(SessionItem* item, int level = 0);

    void callOnValueChange();
    void callOnPropertyChange(const QString &name);
    void callOnChildPropertyChange(SessionItem *item, const QString &name);
    void callOnParentChange(SessionItem *new_parent);
    void callOnChildrenChange(SessionItem *item);
    void callOnSiblingsChange();
    void callOnAnyChildChange(SessionItem *item);

    void clearMapper();

    bool m_active;
    SessionModel *m_model;
    SessionItem *m_item;

    using call_t = std::pair<std::function<void(void)>, const void *>;
    using call_str_t = std::pair<std::function<void(QString)>, const void *>;
    using call_item_t = std::pair<std::function<void(SessionItem *)>, const void *>;
    using call_item_str_t = std::pair<std::function<void(SessionItem*,QString)>, const void *>;

    std::vector<call_t> m_onValueChange;
    std::vector<call_str_t> m_onPropertyChange;
    std::vector<call_item_str_t> m_onChildPropertyChange;
    std::vector<call_item_t> m_onParentChange;
    std::vector<call_item_t> m_onChildrenChange;
    std::vector<call_t> m_onSiblingsChange;
    std::vector<call_item_t> m_onAnyChildChange;
    std::vector<call_item_t> m_onItemDestroy;
    QModelIndex m_aboutToDelete;
};


template<class U>
inline void ModelMapper::clean_container(U& v, const void *caller) {
    v.erase(std::remove_if(v.begin(), v.end(),
        [caller](typename U::value_type const &x) -> bool { return (x.second == caller ? true : false); }),
            v.end());
}


#endif // MODELMAPPER_H
