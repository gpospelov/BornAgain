// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GUIExamplesFactory.cpp
//! @brief     Implements class GUIExamplesFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIExamplesFactory.h"
#include "GUIObjectBuilder.h"
#include "MultiLayer.h"
#include "SampleBuilderFactory.h"
#include <memory>

//! Defines correspondance between example name and real name of simulation from SimulationFactory
QMap<QString, QString > init_NameToRegistry()
{
    QMap<QString, QString > result;
    result["example01"] = "CylindersAndPrismsBuilder";
    result["example02"] = "RadialParaCrystalBuilder";
    result["example03"] = "HexParaCrystalBuilder";
    result["example04"] = "CoreShellParticleBuilder";
    result["example05"] = "MultiLayerWithRoughnessBuilder";
    result["example06"] = "SquareLatticeBuilder";
    result["example07"] = "RotatedPyramidsBuilder";
    result["example08"] = "CylindersWithSizeDistributionBuilder";
    result["example09"] = "ParticleCompositionBuilder";

    // temporary for testing
    //result["example09"] = "MultipleLayoutBuilder";
    //result["example09"] = "TwoTypesCylindersDistributionBuilder";
    //result["example09"] = "RectParaCrystalBuilder";
    //result["example09"] = "SizeDistributionLMAModelBuilder";
    //result["example09"] = "CylindersInSSCABuilder";
    //result["example09"] = "TransformBoxBuilder";
    //result["example09"] = "BoxCompositionRotateZandYBuilder";
    //result["example09"] = "CoreShellBoxRotateZandYBuilder";
    //result["example09"] = "BoxStackCompositionBuilder";
    //result["example09"] = "CylindersWithSizeDistributionBuilder";
    //result["example09"] = "LargeCylindersInDWBABuilder";
    //result["example09"] = "SlicedCompositionBuilder";
    //result["example09"] = "RotatedPyramidsDistributionBuilder";
    //result["example09"] = "SpheresWithLimitsDistributionBuilder";
    result["example09"] = "ConesWithLimitsDistributionBuilder";
    return result;
}

QMap<QString, QString> GUIExamplesFactory::m_name_to_registry = init_NameToRegistry();

bool GUIExamplesFactory::isValidExampleName(const QString &name)
{
    return m_name_to_registry.contains(name);
}

//! Populate sample model with
SessionItem *GUIExamplesFactory::createSampleItems(const QString &name, SampleModel *sampleModel)
{
    QString exampleName = m_name_to_registry[name];

    SampleBuilderFactory factory;
    const std::unique_ptr<ISample> sample(factory.createSample(exampleName.toStdString()));

    GUIObjectBuilder guiBuilder;
    return guiBuilder.populateSampleModel(sampleModel, *sample.get(), name);
}

//SessionItem *GUIExamplesFactory::createInstrumentItems(const QString &name, InstrumentModel *instrumentModel)
//{
//    QString exampleName = m_name_to_registry[name];
//    SimulationFactory registry;
//    const std::unique_ptr<GISASSimulation> P_simulation(registry.createSimulation(exampleName.toStdString()));
//    Q_ASSERT(P_simulation.get());

//    QString instrumentName = name + "_instrument";
//    GUIObjectBuilder guiBuilder;
//    return guiBuilder.populateInstrumentModel(instrumentModel, *P_simulation, instrumentName);
//}
