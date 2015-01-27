// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/GUIExamplesFactory.cpp
//! @brief     Implements class GUIExamplesFactory
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GUIExamplesFactory.h"
#include "GUIObjectBuilder.h"
#include "SampleBuilderFactory.h"
#include "SimulationRegistry.h"
#include "InstrumentModel.h"
#include "SampleModel.h"
#include "GUIHelpers.h"
#include "Simulation.h"
#include <boost/scoped_ptr.hpp>
#include <QDebug>

//! Defines correspondance between example name and real name of simulation from SimulationRegistry
QMap<QString, QString > init_NameToRegistry()
{
    QMap<QString, QString > result;
    result["example01"] = "gui_isgisaxs01";
    result["example02"] = "gui_isgisaxs04_1DDL";
    result["example03"] = "gui_isgisaxs04_2DDL";
    result["example04"] = "gui_isgisaxs11";
    result["example05"] = "LayerWithRoughness";
    result["example06"] = "gui_isgisaxs06a";
    result["example07"] = "gui_isgisaxs07";
    return result;
}

QMap<QString, QString> GUIExamplesFactory::m_name_to_registry = init_NameToRegistry();

bool GUIExamplesFactory::isValidExampleName(const QString &name)
{
    return m_name_to_registry.contains(name);
}


ParameterizedItem *GUIExamplesFactory::createSampleItems(const QString &name, SampleModel *sampleModel)
{
    if(sampleModel->getModelTag() != SessionXML::SampleModelTag ) {
        throw GUIHelpers::Error("GUIExamplesFactory::createSampleItems() -> Error. Not a SampleModelTag");
    }

    QString exampleName = m_name_to_registry[name];

    SimulationRegistry registry;
    boost::scoped_ptr<Simulation> simulation(registry.createItem(exampleName.toLatin1().data()));
    Q_ASSERT(simulation.get());

    boost::scoped_ptr<ISample> sample(simulation->getSampleBuilder()->buildSample());

    Q_ASSERT(sample.get());
    sample->setName(name.toUtf8().constData());
    //sample->printSampleTree();

    GUIObjectBuilder guiBuilder;
    return guiBuilder.populateSampleModel(sampleModel, sample.get());
    //return guiBuilder.getTopItem();
}

ParameterizedItem *GUIExamplesFactory::createInstrumentItems(const QString &name, InstrumentModel *instrumentModel)
{
    if(instrumentModel->getModelTag() != SessionXML::InstrumentModelTag ) {
        throw GUIHelpers::Error("GUIExamplesFactory::createInstrumentItems() -> Error. Not an InstrumentModelTag");
    }

    QString exampleName = m_name_to_registry[name];
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " GUIExamplesFactory::createInstrumentItems()" << name << exampleName;

    SimulationRegistry registry;
    boost::scoped_ptr<Simulation> simulation(registry.createItem(exampleName.toLatin1().data()));
    Q_ASSERT(simulation.get());

    boost::scoped_ptr<Instrument> instrument(new Instrument(simulation.get()->getInstrument()));
    QString instrumentName = name + "_instrument";
    instrument->setName(instrumentName.toUtf8().constData());

    //simulation->setName(name.toUtf8().constData());

    GUIObjectBuilder guiBuilder;
    return guiBuilder.populateInstrumentModel(instrumentModel, instrument.get());
}
