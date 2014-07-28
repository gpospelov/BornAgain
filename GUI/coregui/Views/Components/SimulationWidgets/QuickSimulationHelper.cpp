#include "QuickSimulationHelper.h"
#include "Simulation.h"
#include "Instrument.h"
#include "MultiLayer.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "DomainObjectBuilder.h"
#include <QDebug>
#include <iostream>


Simulation *QuickSimulationHelper::getSimulation(SampleModel *sampleModel, const QString &sample_name, InstrumentModel *instrumentModel, const QString &instrument_name)
{
    qDebug() << "QuickSimulationHelper::getSimulation() " << sample_name << instrument_name;

    Simulation *result = new Simulation;

    MultiLayer *multilayer = getMultiLayer(sampleModel, sample_name);
    Q_ASSERT(multilayer);

    Instrument *instrument = getInstrument(instrumentModel, instrument_name);
    Q_ASSERT(instrument);

    result->setSample(*multilayer);
    result->setInstrument(*instrument);

    delete multilayer;
    delete instrument;

    return result;
}


Instrument *QuickSimulationHelper::getInstrument(InstrumentModel *instrumentModel, const QString &instrument_name)
{
    qDebug() << "QuickSimulationHelper::getInstrument()";
    Q_ASSERT(instrumentModel);
    QModelIndex parentIndex;
    for( int i_row = 0; i_row < instrumentModel->rowCount( parentIndex); ++i_row) {
         QModelIndex itemIndex = instrumentModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = instrumentModel->itemForIndex(itemIndex)){
             qDebug() << "      MainWindow::updateInstruments()" << item->itemName() << item->modelType();
             if(item->modelType() == Constants::InstrumentType && item->itemName() == instrument_name) {
                 DomainObjectBuilder builder;
                 Instrument *instrument = builder.buildInstrument(*item);
                 //std::cout << *instrument << std::endl;
                 return instrument;
             }
         }
    }

    return 0;
}


MultiLayer *QuickSimulationHelper::getMultiLayer(SampleModel *sampleModel, const QString &sample_name)
{
    qDebug() << "QuickSimulationHelper::getMultiLayer()";
    Q_ASSERT(sampleModel);
    QModelIndex parentIndex;
    for( int i_row = 0; i_row < sampleModel->rowCount( parentIndex); ++i_row) {
         QModelIndex itemIndex = sampleModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = sampleModel->itemForIndex(itemIndex)){
             if(item->modelType() == Constants::MultiLayerType && item->itemName() == sample_name) {
                 DomainObjectBuilder builder;
                 MultiLayer *multilayer = builder.buildMultiLayer(*item);
                 //multilayer->printSampleTree();
                 return multilayer;
             }
         }
    }
    return 0;
}
