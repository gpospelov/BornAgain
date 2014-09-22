#ifndef QUICKSIMULATIONHELPER_H
#define QUICKSIMULATIONHELPER_H

#include "WinDllMacros.h"
#include <QString>
#include <QModelIndex>

class Simulation;
class MultiLayer;
class Instrument;
class SampleModel;
class InstrumentModel;
class QStandardItem;
class QStandardItemModel;
class ParameterizedItem;
class QVariant;


//! The QuickSimulationBuilder class is a static class with various helper
//! functions for QuickSimulation widgets.
//! Provides generation of domain simulations out of GUI models during sample
//! and instrument real time tuning.
class BA_CORE_API_ QuickSimulationHelper
{
public:
    static Simulation *getSimulation(SampleModel *sampleModel, const QString &sample_name, InstrumentModel *instrumentModel, const QString &instrument_name);

    static Simulation *getSimulation(SampleModel *sampleModel, InstrumentModel *instrumentModel);

    static Instrument *getInstrument(InstrumentModel *instrumentModel, const QString &instrument_name = QString());

    static MultiLayer *getMultiLayer(SampleModel *sampleModel, const QString &sample_name = QString());

    static QStandardItemModel *createParameterModel(SampleModel *sampleModel, InstrumentModel *instrumentModel);

private:
    static QStandardItem *iterateSessionModel(SampleModel *sampleModel, const QModelIndex &parentIndex = QModelIndex(), QStandardItem *parentItem = 0);
    static QStandardItem *iterateInstrumentModel(InstrumentModel *instrumentModel);
    static void insertRowIntoItem(QStandardItem *parentItem, QStandardItem *childTitleItem, QStandardItem *childValueItem = 0);
    static void insertRowIntoItem(QStandardItem *parentItem, QString title, QVariant value, ParameterizedItem *parameterizedItem);

};


#endif
