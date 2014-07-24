#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QWidget>
#include <QTreeView>
#include <QAction>
#include <QSignalMapper>

#include "qstandarditemmodel.h"
#include <QTableWidget>
#include "SessionModel.h"


class TestViewDelegate;
class ParameterizedItem;

//! TestView window to try things in mainwindow
class TestView : public QWidget
{
    Q_OBJECT

public:
    TestView(SessionModel *sampleModel, QWidget *parent = 0);
    void updateTreeView();


private:
    QTreeView *m_treeView;
    TestViewDelegate *m_delegate;
    QTableWidget *m_tableWidget;
    SessionModel *m_sampleModel;
    QStandardItemModel *getItemModelFromSessionModel();
    QStandardItemModel *getTestItemModel();
    QStandardItem *iterateSessionModel(const QModelIndex &parentIndex = QModelIndex(), QStandardItem *parentItem = NULL);
    void insertRowIntoItem(QStandardItem *parentItem, QStandardItem *childTitleItem, QStandardItem *childValueItem = NULL);
    void insertRowIntoItem(QStandardItem *parentItem, QString title, QVariant value, ParameterizedItem *parameterizedItem);
    QStandardItemModel *m_itemModel;
    void updateItemModel();


};


#endif
