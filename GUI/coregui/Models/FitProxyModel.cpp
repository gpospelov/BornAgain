#include "FitProxyModel.h"
#include "FitModel.h"
#include "ParameterizedItem.h"


FitProxyModel::FitProxyModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}

void FitProxyModel::setFitModel(FitModel *fitModel)
{
    m_fitModel = fitModel;
}

QVariant FitProxyModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

int FitProxyModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return 0;
    }
    return 0;
}

int FitProxyModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QModelIndex FitProxyModel::index(int row, int column,
                                const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex FitProxyModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

