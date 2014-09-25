#ifndef PARAMETERMODELBUILDER_H
#define PARAMETERMODELBUILDER_H

#include <QVariant>
#include <QString>
#include <QModelIndex>

class QModelIndex;
class SampleModel;
class InstrumentModel;
class QStandardItem;
class QStandardItemModel;
class ParameterizedItem;

//! The ParameterModelBuilder generates QStandardItemModel representing
//! tunable parameters of instrument and sample models.
//! Used by ModelTuningWidget.
class ParameterModelBuilder
{
public:

    static QStandardItemModel *createParameterModel(SampleModel *sampleModel, InstrumentModel *instrumentModel);

private:
    static QStandardItem *iterateSessionModel(SampleModel *sampleModel, const QModelIndex &parentIndex = QModelIndex(), QStandardItem *parentItem = 0);
    static QStandardItem *iterateInstrumentModel(InstrumentModel *instrumentModel);
    static void insertRowIntoItem(QStandardItem *parentItem, QStandardItem *childTitleItem, QStandardItem *childValueItem = 0);
    static void insertRowIntoItem(QStandardItem *parentItem, QString title, QVariant value, ParameterizedItem *parameterizedItem);
};


#endif

