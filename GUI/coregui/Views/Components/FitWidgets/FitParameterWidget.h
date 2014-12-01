#ifndef FITPARAMETERWIDGET_H
#define FITPARAMETERWIDGET_H

#include <QWidget>
#include <QTreeView>
#include <QAction>
#include <QTableWidget>

#include "FitProxyModel.h"
#include "FitModel.h"

class FitModel;



class BA_CORE_API_ FitParameterWidget : public QWidget
{
    Q_OBJECT

public:
    FitParameterWidget(FitProxyModel *fitProxyModel, QWidget *parent = 0);

private:
    FitModel *m_fitModel;
    QStandardItemModel *m_parameterModel;
    QTreeView *m_treeView;
    FitProxyModel *m_fitProxyModel;


    QStandardItemModel *createParameterModel(FitModel *fitModel);
    QStandardItemModel *iterateSessionModel(FitModel *fitModel, const QModelIndex &parentIndex = QModelIndex(), QStandardItemModel *parentItem = 0);
    void insertRowIntoItem(QStandardItemModel *parentItem, QString title, QVariant value, QVariant min, QVariant max, QVariant isUse);


    void initFitModel();
};

#endif
