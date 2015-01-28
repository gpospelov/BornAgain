// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DomainSimulationBuilder.cpp
//! @brief     Implements class DomainSimulationBuilder
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DomainSimulationBuilder.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "Instrument.h"
#include "MultiLayer.h"
#include "DomainObjectBuilder.h"
#include <QDebug>

//! Creates domain simulation from sample and instrument models for given names of MultiLayer and Instrument
Simulation *DomainSimulationBuilder::getSimulation(SampleModel *sampleModel, const QString &sample_name, InstrumentModel *instrumentModel, const QString &instrument_name)
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


//! Creates domain simulation from sample and instrument models. First sample and first instrument in models will be used, if there are more than one
Simulation *DomainSimulationBuilder::getSimulation(SampleModel *sampleModel, InstrumentModel *instrumentModel)
{
    return getSimulation(sampleModel, QString(), instrumentModel, QString());
}


//! Creates domain instrument from InstrumentModel and given instrument name. If name is empty, then uses first instrument in the model.
Instrument *DomainSimulationBuilder::getInstrument(InstrumentModel *instrumentModel, const QString &instrument_name)
{
    qDebug() << "QuickSimulationHelper::getInstrument()";

    Instrument *result(0);

    QMap<QString, ParameterizedItem *> instrumentMap = instrumentModel->getInstrumentMap();

    if(instrumentMap.size()) {
        ParameterizedItem *instrumentItem(0);
        if(instrument_name.isEmpty()) {
            instrumentItem = instrumentMap.first();
        } else {
            instrumentItem = instrumentMap[instrument_name];
        }

        Q_ASSERT(instrumentItem);
        DomainObjectBuilder builder;
        result = builder.buildInstrument(*instrumentItem);
    }

    return result;
}


//! Creates domain MultiLayer from SampleModel and given MultiLayer name. If name is empty, then uses first MultiLayer in the model.
MultiLayer *DomainSimulationBuilder::getMultiLayer(SampleModel *sampleModel, const QString &sample_name)
{
    qDebug() << "QuickSimulationHelper::getMultiLayer()";

    MultiLayer *result(0);

    QMap<QString, ParameterizedItem *> sampleMap = sampleModel->getSampleMap();

    if(sampleMap.size()) {
        ParameterizedItem *sampleItem(0);
        if(sample_name.isEmpty()) {
            sampleItem = sampleMap.first();
        } else {
            sampleItem = sampleMap[sample_name];
        }

        Q_ASSERT(sampleItem);
        DomainObjectBuilder builder;
        result = builder.buildMultiLayer(*sampleItem);
    }

    return result;
}

