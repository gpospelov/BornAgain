#ifndef SAMPLETUNINGWIDGET_H
#define SAMPLETUNINGWIDGET_H

#include <QWidget>
#include <QTreeView>
#include <QAction>
#include <QSignalMapper>
#include <QTableWidget>
#include <QStandardItemModel>


class SampleTuningDelegate;
class ParameterizedItem;
class SampleModel;
class InstrumentModel;


//! TestView window to try things in mainwindow
class SampleTuningWidget : public QWidget
{
    Q_OBJECT

public:
    SampleTuningWidget(SampleModel *sampleModel, InstrumentModel *instrumentModel, QWidget *parent = 0);
    void updateTreeView();


private:
    //QStandardItemModel *getItemModelFromSessionModel();
    // QStandardItemModel *getTestItemModel();
    QStandardItem *iterateSessionModel(const QModelIndex &parentIndex = QModelIndex(), QStandardItem *parentItem = NULL);
    void insertRowIntoItem(QStandardItem *parentItem, QStandardItem *childTitleItem, QStandardItem *childValueItem = NULL);
    void insertRowIntoItem(QStandardItem *parentItem, QString title, QVariant value, ParameterizedItem *parameterizedItem);

    QStandardItemModel *createParameterModel();

    QStandardItemModel *m_parameterModel;
    QTreeView *m_treeView;
    SampleTuningDelegate *m_delegate;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
};


#endif
