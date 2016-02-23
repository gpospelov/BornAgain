// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TestItem.h
//! @brief     Defines class TestItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MODELMAPPER_H
#define MODELMAPPER_H

#include "WinDllMacros.h"

#include <QObject>
#include <QVector>
#include <functional>

class QModelIndex;
class SessionModel;
class ParameterizedItem;


class BA_CORE_API_ ModelMapper : public QObject
{
    Q_OBJECT
public:
    ModelMapper(QObject *parent = 0);

    void setItem(ParameterizedItem* item);

    void setOnPropertyChange(std::function<void(QString)> f) {m_onPropertyChange = f;}

    void setOnChildPropertyChange(std::function<void(ParameterizedItem*,QString)> f)
    {m_onChildPropertyChange = f;}

public slots:
    void onDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight,
                       const QVector<int> & roles = QVector<int> ());

    void onRowsInserted(const QModelIndex & parent, int first, int last);

private:
    void setModel(SessionModel *model);
    int nestlingDepth(ParameterizedItem* item, int level = 0);

    SessionModel *m_model;
    ParameterizedItem *m_item;
    std::function<void(QString)> m_onPropertyChange;
    std::function<void(ParameterizedItem*,QString)> m_onChildPropertyChange;
};

#endif
