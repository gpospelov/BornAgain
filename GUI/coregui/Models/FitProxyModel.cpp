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

int FitProxyModel::rowCount(const QModelIndex &parentIndex) const
{
    if(parentIndex.isValid())
    {
        return 0;
    }

    int counter = 0;

    if(m_fitModel)
    {
        for( int i_row = 0; i_row < m_fitModel->rowCount( parentIndex ); ++i_row) {
            QModelIndex itemIndex = m_fitModel->index( i_row, 0, parentIndex );

            if (ParameterizedItem *item = m_fitModel->itemForIndex(itemIndex)){

                counter++;
            }
        }
    }

    return counter;
}

int FitProxyModel::columnCount(const QModelIndex &parentIndex) const
{
    if(!parentIndex.isValid())
    {
        return 5;
    }

    return 0;
}

QModelIndex FitProxyModel::index(int row, int column,
                                 const QModelIndex &parentIndex) const
{
    ParameterizedItem *parent_item = m_fitModel->itemForIndex(parentIndex);
    if (ParameterizedItem *item = parent_item->childAt(row)) {
        return createIndex(row, column, item);
    }
    return QModelIndex();
}

QModelIndex FitProxyModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}



