// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitParameterAbsModel.h
//! @brief     Declares class FitParameterAbsModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERABSMODEL_H
#define FITPARAMETERABSMODEL_H

#include "WinDllMacros.h"
#include <QAbstractItemModel>

class JobModel;
class FitParameterContainerItem;
class SessionItem;

//! The FitParameterProxyModel adopt original JobModel to show items from FitParameterContainer
//! in 5 column tree view.

class BA_CORE_API_ FitParameterAbsModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit FitParameterAbsModel(FitParameterContainerItem *fitParContainer, QObject *parent = 0);

    enum EColumn {ITEM_NAME, ITEM_USE, ITEM_MIN, ITEM_START, ITEM_MAX, MAX_COLUMNS}; // NEW column usage


    Qt::ItemFlags flags(const QModelIndex & index) const Q_DECL_OVERRIDE;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    QModelIndex indexOfItem(SessionItem *item) const;
    SessionItem *itemForIndex(const QModelIndex &index) const;

private slots:
    void onSourceDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight, const QVector<int> & roles);
    void onSourceRowsInserted(const QModelIndex & parent, int first, int last);
    void onSourceBeginRemoveRows(const QModelIndex & parent, int first, int last);

private:
    void connectModel(QAbstractItemModel *sourceModel, bool isConnect = true);

    FitParameterContainerItem *m_root_item;
    QMap<int, QString> m_columnNames;
};


#endif
