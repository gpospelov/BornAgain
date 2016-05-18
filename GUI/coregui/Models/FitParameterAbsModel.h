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

#ifndef FITPARAMETERABSMODEL_H
#define FITPARAMETERABSMODEL_H

#include "WinDllMacros.h"
#include <QAbstractItemModel>

class SessionModel;
class FitParameterContainerItem;
class SessionItem;

//! The FitParameterProxyModel adopt original JobModel to show items from FitParameterContainer
//! in 5 column tree view.
//! (It's not a true proxy model, it

class BA_CORE_API_ FitParameterProxyModel : public QAbstractItemModel
{
    Q_OBJECT

public:

    explicit FitParameterProxyModel(FitParameterContainerItem *fitParContainer, QObject *parent = 0);

    enum EColumn {PAR_NAME, PAR_TYPE, PAR_VALUE, PAR_MIN, PAR_MAX, MAX_COLUMNS};

    Qt::ItemFlags flags(const QModelIndex & index) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;

    QStringList mimeTypes() const Q_DECL_OVERRIDE;
    Qt::DropActions supportedDragActions() const;
    Qt::DropActions supportedDropActions() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                             const QModelIndex &parent) const Q_DECL_OVERRIDE;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                        const QModelIndex &parent)  Q_DECL_OVERRIDE;


    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;


    QModelIndex indexOfItem(SessionItem *item) const;
    SessionItem *itemForIndex(const QModelIndex &index) const;

    SessionModel *sourceModel() const;

    bool isValidSourceItem(SessionItem *item) const;

private slots:
    void onSourceDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight,
                             const QVector<int> & roles);
    void onSourceRowsRemoved(const QModelIndex & parent, int first, int last);
    void onSourceAboutToBeReset();

private:
    void connectModel(QAbstractItemModel *sourceModel, bool isConnect = true);
    void addColumn(EColumn id, const QString &name, const QString &tooltip);

    FitParameterContainerItem *m_root_item;
    QMap<int, QString> m_columnNames;
    QMap<int, QString> m_columnToolTips;
};

inline Qt::DropActions FitParameterProxyModel::supportedDragActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}

inline Qt::DropActions FitParameterProxyModel::supportedDropActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}


#endif
