// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUITranslationTest/GUITranslationTest.cpp
//! @brief     Includes GUI translation functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUITranslationTest.h"
#include "SimulationFactory.h"
#include "SampleBuilderFactory.h"
#include "GISASSimulation.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "GUIObjectBuilder.h"
#include "ApplicationModels.h"
#include "JobModel.h"
#include "DocumentModel.h"
#include "JobItem.h"
#include "ParameterTreeBuilder.h"
#include "ParameterTreeItems.h"
#include <QStack>
#include <QDebug>


GUITranslationTest::GUITranslationTest()
    : m_models(new ApplicationModels(0))
{
    SimulationFactory simFactory;
    m_simulation.reset(simFactory.createItem("BasicGISAS"));

    SampleBuilderFactory sampleFactory;
    m_simulation->setSample(*sampleFactory.createSample("CylindersAndPrismsBuilder"));
}

GUITranslationTest::~GUITranslationTest()
{

}

bool GUITranslationTest::runTest()
{
    processParameterTree();
    m_simulation->printParameters();
    return true;
}

void GUITranslationTest::processParameterTree()
{
    m_models->instrumentModel()->clear();
    // populating GUI models from domain
    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(m_models->sampleModel(), *m_simulation);
    guiBuilder.populateInstrumentModel(m_models->instrumentModel(), *m_simulation);
    guiBuilder.populateDocumentModel(m_models->documentModel(), *m_simulation);

    JobItem *jobItem = m_models->jobModel()->addJob(
                m_models->sampleModel()->multiLayerItem(),
                m_models->instrumentModel()->instrumentItem(),
                0,
                m_models->documentModel()->getSimulationOptionsItem());

    SessionItem *current = jobItem->getItem(JobItem::T_PARAMETER_TREE); // this is container
    QStack<SessionItem *> stack;
    stack.push(current);
    while (!stack.empty()) {
        current = stack.pop();
        if (current->modelType() == Constants::ParameterLabelType
                || current->modelType() == Constants::ParameterContainerType) {
            for (SessionItem *child : current->getItems()) {
                stack.push(child);
            }
        } else {
            if (ParameterItem *parItem = dynamic_cast<ParameterItem *>(current)) {
                qDebug() << "link" << parItem->getItemValue(ParameterItem::P_LINK).toString();
                qDebug() << "domain" << parItem->getItemValue(ParameterItem::P_DOMAIN).toString();
                qDebug() << "---";
            }
        }
    }

}
