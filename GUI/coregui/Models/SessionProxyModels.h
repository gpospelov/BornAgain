// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SessionProxyModels.h
//! @brief     Defines classes related to SessionModel proxies
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SESSIONPROXYMODELS_H
#define SESSIONPROXYMODELS_H

#include "SessionModel.h"
#include <QObject>
#include <QIdentityProxyModel>
#include <QAbstractProxyModel>
#include <QModelIndex>

class SessionCompactModel : public QIdentityProxyModel
{
    Q_OBJECT
public:
    SessionCompactModel(QObject *parent = 0);
    void setSourceModel(QAbstractItemModel *source);
    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex& child) const;
    int rowCount(const QModelIndex& parent) const;
private:
    SessionModel *m_source;
};


class SessionTestModel : public QAbstractProxyModel
{
public:
    SessionTestModel(QObject *parent = 0);
    void setSourceModel(QAbstractItemModel *source);

    QModelIndex mapFromSource(const QModelIndex& sourceIndex) const;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;

    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex& child) const;
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;

private:
    SessionModel *m_source;

};

#endif
