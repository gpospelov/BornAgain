// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitModel.h
//! @brief     Defines class FitModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITMODEL_H
#define FITMODEL_H

#include "SessionModel.h"
#include "GUIHelpers.h"

#include <QDebug>
#include <QModelIndex>
#include <QVariant>
#include <QStringList>
#include <QMimeData>
#include <QItemSelection>

class BA_CORE_API_ FitModel : public SessionModel
{
    Q_OBJECT

public:

    enum AcceptableFitModelNames { FitParameterModel,
                                   ProxySampleModel,
                                   ProxyInstrumentModel,
                                   testModel };

    //'columns' parameter needed is needed because the left and right side have different num of cols
    explicit FitModel(int columns, AcceptableFitModelNames modelName = testModel, QObject *parent = 0);
    ~FitModel() {}

    //overwritten methods from SessionModel
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    //for drag and drop
    Qt::DropActions supportedDropActions() const;
    //QStringList mimeTypes() const;
    QMimeData* mimeData(const QModelIndexList &indices) const;
    bool canDropMimeData(const QMimeData *data,
        Qt::DropAction action, int row, int column, const QModelIndex &parent) const;

    bool dropMimeData(const QMimeData *data,
         Qt::DropAction action, int row, int column, const QModelIndex &parent);


    //overwritten methods from QAbstractItemModel
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    bool insertColumns(int column, int count, const QModelIndex & parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeColumns(int column, int count, const QModelIndex & parent = QModelIndex()) Q_DECL_OVERRIDE;

    ParameterizedItem* searchByNameGUID(QString name, QString GUID, QModelIndex parentIndex = QModelIndex(), bool found = false);

private:
    //stores the value of the parameter
    QString parameter;
    //stores the string of ancestors that parameter derived from in sample model
    QString ancestors;
    //stores the immediate parent that the item migrated from
    QString immediate_predecessor;

    int m_columns;
    AcceptableFitModelNames m_modelName;

    static const int MaxCompression = 9;
};

#endif
