#ifndef FITPROXYMODEL_H
#define FITPROXYMODEL_H


#include <QAbstractItemModel>

class FitModel;
class ParameterizedItem;

class BA_CORE_API_ FitProxyModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit FitProxyModel(QObject *parent = 0);
    ~FitProxyModel(){}

    // overriden methods
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    //end if overriden methods

    void setFitModel(FitModel *fitModel);
    FitModel *getFitModel()
        { return m_fitModel; }


private:
    FitModel *m_fitModel;

};




#endif
