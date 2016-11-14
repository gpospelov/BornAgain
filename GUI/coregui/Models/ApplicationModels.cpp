// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ApplicationModels.cpp
//! @brief     Defines class holding all application models
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ApplicationModels.h"
#include "DocumentModel.h"
#include "GISASSimulation.h"
#include "GUIObjectBuilder.h"
#include "ISample.h"
#include "IconProvider.h"
#include "InstrumentModel.h"
#include "JobItem.h"
#include "JobModel.h"
#include "MaterialModel.h"
#include "MaterialSvc.h"
#include "MultiLayer.h"
#include "RealDataModel.h"
#include "SampleBuilderFactory.h"
#include "SampleModel.h"
#include "WarningMessageService.h"
#include "RealDataItem.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataItem.h"
#include "ImportDataAssistant.h"
#include "StandardSimulations.h"

ApplicationModels::ApplicationModels(QObject *parent)
    : QObject(parent)
    , m_documentModel(0)
    , m_materialModel(0)
    , m_materialSvc(0)
    , m_instrumentModel(0)
    , m_sampleModel(0)
    , m_realDataModel(0)
    , m_jobModel(0)
{
    createModels();
//    createTestSample();
//    createTestJob();

//    SessionItem *multilayer = m_sampleModel->insertNewItem(Constants::MultiLayerType);
//    SessionItem *layer = m_sampleModel->insertNewItem(Constants::LayerType, multilayer->index());

//    SampleModel * mmm = m_sampleModel->createCopy();

}

ApplicationModels::~ApplicationModels()
{
    delete m_materialSvc;
}

DocumentModel *ApplicationModels::documentModel()
{
    return m_documentModel;
}

MaterialModel *ApplicationModels::materialModel()
{
    return m_materialModel;
}

InstrumentModel *ApplicationModels::instrumentModel()
{
    return m_instrumentModel;
}

SampleModel *ApplicationModels::sampleModel()
{
    return m_sampleModel;
}

RealDataModel *ApplicationModels::realDataModel()
{
    return m_realDataModel;
}

JobModel *ApplicationModels::jobModel()
{
    return m_jobModel;
}

ObsoleteFitModel *ApplicationModels::fitModel()
{
    return 0;
}

//! reset all models to initial state
void ApplicationModels::resetModels()
{
    m_documentModel->clear();
    m_documentModel->insertNewItem(Constants::SimulationOptionsType);

    m_materialModel->clear();
    m_materialModel->addMaterial("Default", 1e-3, 1e-5);
    m_materialModel->addMaterial("Air", 0.0, 0.0);
    m_materialModel->addMaterial("Particle", 6e-4, 2e-8);
    m_materialModel->addMaterial("Substrate", 6e-6, 2e-8);

    m_sampleModel->clear();

    m_realDataModel->clear();

    m_jobModel->clear();

    m_instrumentModel->clear();
    SessionItem *instrument = m_instrumentModel->insertNewItem(Constants::InstrumentType);
    instrument->setItemName("Default GISAS");
    m_instrumentModel->insertNewItem(Constants::DetectorType, m_instrumentModel->indexOfItem(instrument));
    m_instrumentModel->insertNewItem(Constants::BeamType, m_instrumentModel->indexOfItem(instrument));

//    m_realDataModel->insertNewItem(Constants::RealDataType);
//    m_realDataModel->insertNewItem(Constants::RealDataType);
//    m_realDataModel->insertNewItem(Constants::RealDataType);

}

//! creates and initializes models, order is important
void ApplicationModels::createModels()
{
    createDocumentModel();

    createMaterialModel();

    createSampleModel();

    createInstrumentModel();

    createRealDataModel();

    createJobModel();

    resetModels();
}

void ApplicationModels::createDocumentModel()
{
    delete m_documentModel;
    m_documentModel = new DocumentModel(this);
    connectModel(m_documentModel);
}

void ApplicationModels::createMaterialModel()
{
    delete m_materialModel;
    m_materialModel = new MaterialModel(this);
    connectModel(m_materialModel);
    m_materialSvc = new MaterialSvc(m_materialModel);
}

void ApplicationModels::createSampleModel()
{
    Q_ASSERT(m_materialModel);
    delete m_sampleModel;
    m_sampleModel = new SampleModel(this);
    connectModel(m_sampleModel);
    connect(m_materialModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            m_sampleModel, SLOT(onMaterialModelChanged(QModelIndex,QModelIndex)));
}

void ApplicationModels::createInstrumentModel()
{
    delete m_instrumentModel;
    m_instrumentModel = new InstrumentModel(this);
    connectModel(m_instrumentModel);
    m_instrumentModel->setIconProvider(new IconProvider());
}

void ApplicationModels::createRealDataModel()
{
    delete m_realDataModel;
    m_realDataModel = new RealDataModel(this);
    connectModel(m_realDataModel);
}

void ApplicationModels::createJobModel()
{
    delete m_jobModel;
    m_jobModel = new JobModel(this);
    connectModel(m_jobModel);
}

void ApplicationModels::createTestSample()
{
    SampleBuilderFactory factory;
    const std::unique_ptr<ISample> P_sample(factory.createSample("CylindersAndPrismsBuilder"));

    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(m_sampleModel, *P_sample);

// to populate sample with predefined instrument
//    const std::unique_ptr<GISASSimulation> simulation(StandardSimulations::GISASWithMasks());
//    guiBuilder.populateInstrumentModel(m_instrumentModel, *simulation);
}

void ApplicationModels::createTestJob()
{
    SimulationOptionsItem *optionsItem = m_documentModel->getSimulationOptionsItem();
//    optionsItem->setRunPolicy(Constants::JOB_RUN_IN_BACKGROUND);

    JobItem *jobItem = m_jobModel->addJob(
                m_sampleModel->multiLayerItem(),
                m_instrumentModel->instrumentItem(),
                0,
                optionsItem);

//    IHistogram *data = IntensityDataIOFactory::readIntensityData("/home/pospelov/development/BornAgain/temp/Untitled12/data_job1_0.int");

//    RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(jobItem->getItem(JobItem::T_REALDATA));
//    Q_ASSERT(realDataItem);

//    realDataItem->intensityDataItem()->setOutputData(data->createOutputData());
//    jobItem->setItemValue(JobItem::P_WITH_FITTING, true);

    m_jobModel->runJob(jobItem->index());
}

void ApplicationModels::createTestRealData()
{
    RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(
                m_realDataModel->insertNewItem(Constants::RealDataType));
    realDataItem->setItemName("realdata");

    std::unique_ptr<OutputData<double>> data(
                IntensityDataIOFactory::readOutputData("/home/pospelov/untitled2.int"));

    ImportDataAssistant assistant;
    OutputData<double> *simplified = assistant.createSimlifiedOutputData(*data.get());
    realDataItem->setOutputData(simplified);
}

//! Writes all model in file one by one

void ApplicationModels::writeTo(QXmlStreamWriter *writer)
{
    foreach(SessionModel *model, modelList()) {
        model->writeTo(writer);
    }
}

void ApplicationModels::readFrom(QXmlStreamReader *reader, WarningMessageService *messageService)
{
    foreach(SessionModel *model, modelList()) {
        if(model->getModelTag() == reader->name()) {
            model->readFrom(reader, messageService);
            if(messageService->hasWarnings(model)) {
                messageService->send_message(this, "MODEL_READ_WARNING", model->getModelTag());
            }
            break;
        }
    }

}

//! Returns the list of all GUI models

QList<SessionModel *> ApplicationModels::modelList()
{
    QList<SessionModel *> result;
    result.append(m_documentModel);
    result.append(m_materialModel);
    result.append(m_instrumentModel);
    result.append(m_sampleModel);
    result.append(m_realDataModel);
    result.append(m_jobModel);
    return result;
}

//! Loads model's non-XML data  from the projectDir

void ApplicationModels::loadNonXMLData(const QString &projectDir)
{
    foreach(SessionModel *model, modelList()) {
        model->loadNonXMLData(projectDir);
    }
}

//! Saves model's non-XML data  to the projectDir

void ApplicationModels::saveNonXMLData(const QString &projectDir)
{
    foreach(SessionModel *model, modelList()) {
        model->saveNonXMLData(projectDir);
    }
}

void ApplicationModels::disconnectModel(SessionModel *model)
{
    if(model) {
        disconnect(model, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,
                   SIGNAL(modelChanged()));
        disconnect(model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                   SIGNAL(modelChanged()));
        disconnect(model, SIGNAL(rowsInserted(QModelIndex, int,int)), this,
                   SIGNAL(modelChanged()));
    }
}

void ApplicationModels::connectModel(SessionModel *model)
{
    if(model) {
        connect(model, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,
                   SIGNAL(modelChanged()), Qt::UniqueConnection);
        connect(model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                   SIGNAL(modelChanged()), Qt::UniqueConnection);
        connect(model, SIGNAL(rowsInserted(QModelIndex, int,int)), this,
                   SIGNAL(modelChanged()), Qt::UniqueConnection);
    }
}
