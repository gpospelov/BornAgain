// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/GUIExamplesFactory.cpp
//! @brief     Implements class GUIExamplesFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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
    // temporary for testing
    //result["example08"] = "beam_divergence";
    result["example08"] = "detector_resolution";
    return result;
}

QMap<QString, QString> GUIExamplesFactory::m_name_to_registry = init_NameToRegistry();

bool GUIExamplesFactory::isValidExampleName(const QString &name)
{
    return m_name_to_registry.contains(name);
}

//! Populate sample model with
ParameterizedItem *GUIExamplesFactory::createSampleItems(const QString &name, SampleModel *sampleModel)
{
    QString exampleName = m_name_to_registry[name];
    SimulationRegistry registry;
    boost::scoped_ptr<Simulation> simulation(registry.createSimulation(exampleName.toStdString()));
    Q_ASSERT(simulation.get());

    GUIObjectBuilder guiBuilder;
    return guiBuilder.populateSampleModel(sampleModel, *simulation, name);
}

ParameterizedItem *GUIExamplesFactory::createInstrumentItems(const QString &name, InstrumentModel *instrumentModel)
{
    QString exampleName = m_name_to_registry[name];
    SimulationRegistry registry;
    boost::scoped_ptr<Simulation> simulation(registry.createSimulation(exampleName.toStdString()));
    Q_ASSERT(simulation.get());

    QString instrumentName = name + "_instrument";
    GUIObjectBuilder guiBuilder;
    return guiBuilder.populateInstrumentModel(instrumentModel, *simulation, instrumentName);
}
