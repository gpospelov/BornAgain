// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitParameterProxyModel.h
//! @brief     Declares class FitParameterProxyModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERPROXYMODEL_H
#define FITPARAMETERPROXYMODEL_H

#include "WinDllMacros.h"
#include <QAbstractProxyModel>

//class SessionItem;
//class JobModel;
class JobModel;
class FitParameterContainerItem;
class SessionItem;

//! The FitParameterProxyModel adopt original JobModel to show items from FitParameterContainer
//! in 5 column tree view.

class BA_CORE_API_ FitParameterProxyModel : public QAbstractProxyModel
{
    Q_OBJECT

public:
//    explicit FitParameterProxyModel(JobModel *jobModel, FitParameterContainerItem *fitParContainer, QObject *parent = 0);
    explicit FitParameterProxyModel(FitParameterContainerItem *fitParContainer, QObject *parent = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const ;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;

    SessionItem *itemForIndex(const QModelIndex &index) const;

private:
    JobModel *jobModel() const;

//    JobModel *m_jobModel;
    FitParameterContainerItem *m_parContainer;
//    JobItem *m_jobItem;
    QMap<int, QString> m_columnNames;
};



#endif
