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

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;


private:
//    QModelIndex indexOfItem(SessionItem *item) const;
    SessionItem *itemForIndex(const QModelIndex &index) const;

    FitParameterContainerItem *m_root_item;
    QMap<int, QString> m_columnNames;
};


#endif
