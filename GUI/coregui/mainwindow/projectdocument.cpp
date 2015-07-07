// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/projectdocument.cpp
//! @brief     Implements class ProjectDocument
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "projectdocument.h"
#include "MaterialModel.h"
#include "InstrumentModel.h"
#include "JobQueueData.h"
#include "JobModel.h"
#include "JobItem.h"
#include "IntensityDataItem.h"
#include "SampleModel.h"
#include "IntensityDataIOFactory.h"
#include "BAVersion.h"
#include "WarningMessageService.h"
#include "MessageContainer.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <QModelIndex>
#include "GUIHelpers.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

ProjectDocument::ProjectDocument()
    : m_materialModel(0), m_instrumentModel(0), m_sampleModel(0), m_jobModel(0)
    , m_modified(false), m_documentStatus(STATUS_OK), m_messageService(0)
{
    setObjectName("ProjectDocument");
}

ProjectDocument::ProjectDocument(const QString &projectFileName)
    : m_materialModel(0), m_instrumentModel(0), m_sampleModel(0), m_jobModel(0)
    , m_modified(false), m_documentStatus(STATUS_OK), m_messageService(0)
{
    setObjectName("ProjectDocument");
    setProjectFileName(projectFileName);
}

QString ProjectDocument::getProjectName() const
{
    return m_project_name;
}

void ProjectDocument::setProjectName(const QString &text)
{
    m_project_name = text;
    emit modified();
}

QString ProjectDocument::getProjectDir() const
{
    return m_project_dir;
}

void ProjectDocument::setProjectDir(const QString &text)
{
    m_project_dir = text;
}

QString ProjectDocument::getProjectFileName() const
{
    QString result = getProjectDir() + "/" + getProjectName() + getProjectFileExtension();
    return result;
}

void ProjectDocument::setProjectFileName(const QString &projectFileName)
{
    QFileInfo info(projectFileName);
    setProjectName(info.baseName());
    setProjectDir(info.path());
}

QString ProjectDocument::getProjectFileExtension()
{
    return QString(".pro");
}

void ProjectDocument::setMaterialModel(MaterialModel *materialModel)
{
    if (materialModel != m_materialModel) {
        disconnectModel(m_materialModel);
        m_materialModel = materialModel;
        connectModel(m_materialModel);
    }
}

void ProjectDocument::setInstrumentModel(InstrumentModel *instrumentModel)
{
    if (instrumentModel != m_instrumentModel) {
        disconnectModel(m_instrumentModel);
        m_instrumentModel = instrumentModel;
        connectModel(m_instrumentModel);
    }
}

void ProjectDocument::setSampleModel(SampleModel *sampleModel)
{
    if (sampleModel != m_sampleModel) {
        disconnectModel(m_sampleModel);
        m_sampleModel = sampleModel;
        connectModel(m_sampleModel);
    }
}

void ProjectDocument::setJobModel(JobModel *jobModel)
{
    if (jobModel != m_jobModel) {
        disconnectModel(m_jobModel);
        m_jobModel = jobModel;
        connectModel(m_jobModel);
    }
}

bool ProjectDocument::save()
{
    reviseOutputData();
    QString filename = getProjectFileName();

    QFile file(filename);
    // if (!file.open(QFile::WriteOnly | QFile::Text)) {
    if (!file.open(QFile::ReadWrite | QIODevice::Truncate | QFile::Text)) {
        qDebug() << "ProjectDocument::save() -> Error! Can't save file";
        return false;
    }
    writeTo(&file);
    file.close();

    // saving of non-xml data
    saveOutputData();

    m_modified = false;
    emit modified();

    return true;
}

ProjectDocument::EDocumentStatus ProjectDocument::load(const QString &project_file_name)
{
    m_documentStatus = STATUS_OK;

//    bool success_read(false);
//    m_error_message.clear();
    setProjectFileName(project_file_name);
//    Q_ASSERT(project_file_name == getProjectFileName());

    QFile file(getProjectFileName());
//    if (!file.open(QFile::ReadOnly | QFile::Text)) {
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_messageService->send_message(this, WarningMessageService::OPEN_FILE_ERROR, file.errorString());
        m_documentStatus = EDocumentStatus(m_documentStatus|STATUS_FAILED);
//        m_error_message
//            = QString("Can't open '%1'. \n").arg(getProjectFileName());
//        m_error_message.append(file.errorString());
//        qDebug() << "XXX" << "project_file_name" << project_file_name
//                 << "getProjectFileName()" << getProjectFileName()
//                 << "getProjectDir()" << getProjectDir()
//                 << "file_error:" << file.error() << file.errorString();
//        return false;
        return m_documentStatus;
    }

    try {
        // loading project file
        readFrom(&file);
        file.close();

        // loading accompanying non-xml data
        loadOutputData();
    } catch (const std::exception &ex) {
//        m_error_message.append(
//            QString("Exception was thrown with the error message '%1'").arg(QString(ex.what())));
//        success_read = false;
        m_documentStatus = EDocumentStatus(m_documentStatus | STATUS_FAILED);
        m_messageService->send_message(this, WarningMessageService::EXCEPTION_THROW, QString(ex.what()));
    }

    return m_documentStatus;
}

bool ProjectDocument::hasValidNameAndPath()
{
    return (!m_project_name.isEmpty() && !m_project_dir.isEmpty());
}

bool ProjectDocument::isModified()
{
    return m_modified;
}

void ProjectDocument::onDataChanged(const QModelIndex &, const QModelIndex &)
{
    m_modified = true;
    emit modified();
}

void ProjectDocument::onJobModelChanged(const QString &)
{
    m_modified = true;
    emit modified();
}

void ProjectDocument::onRowsChanged(const QModelIndex &, int , int )
{
    m_modified = true;
    emit modified();
}

void ProjectDocument::readFrom(QIODevice *device)
{
    disconnectModel(m_materialModel);
    disconnectModel(m_instrumentModel);
    disconnectModel(m_sampleModel);
    disconnectModel(m_jobModel);

    QXmlStreamReader reader(device);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == ProjectDocumentXML::BornAgainTag) {
                const QString version = reader.attributes()
                                            .value(ProjectDocumentXML::BornAgainVersionAttribute)
                                            .toString();
                if (version != GUIHelpers::getBornAgainVersionString()) {
//                    m_error_message.append(
//                        QString("Given project was created using BornAgain ver. %1").arg(version));
//                    m_error_message.append(
//                        QString(" which is different from the version %1 you are currently using.")
//                            .arg(GUIHelpers::getBornAgainVersionString()));
//                    m_error_message.append(QString(
//                        " At the moment we do not support import from older versions.\n\n"));
                }
            } else if (reader.name() == ProjectDocumentXML::InfoTag) {
                //
            } else if (reader.name() == SessionXML::MaterialModelTag) {
                readModel(m_materialModel, &reader);

            } else if (reader.name() == SessionXML::InstrumentModelTag) {
                readModel(m_instrumentModel, &reader);

            } else if (reader.name() == SessionXML::SampleModelTag) {
                readModel(m_sampleModel, &reader);

            } else if (reader.name() == SessionXML::JobModelTag) {
                readModel(m_jobModel, &reader);

            }
        }
    }

    if (reader.hasError()) {
        m_documentStatus = EDocumentStatus(m_documentStatus | STATUS_FAILED);
        m_messageService->send_message(this, WarningMessageService::XML_FORMAT_ERROR, reader.errorString());
        return;
    }

    connectModel(m_materialModel);
    connectModel(m_instrumentModel);
    connectModel(m_sampleModel);
    connectModel(m_jobModel);
}

void ProjectDocument::writeTo(QIODevice *device)
{
    QXmlStreamWriter writer(device);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("BornAgain");
    QString version_string = GUIHelpers::getBornAgainVersionString();
    writer.writeAttribute("Version", version_string);

    writer.writeStartElement(ProjectDocumentXML::InfoTag);
    writer.writeAttribute(ProjectDocumentXML::InfoNameAttribute, getProjectName());
    writer.writeEndElement(); // InfoTag

    m_materialModel->writeTo(&writer);
    m_instrumentModel->writeTo(&writer);
    m_sampleModel->writeTo(&writer);
    m_jobModel->writeTo(&writer);

    writer.writeEndElement(); // BornAgain tag
    writer.writeEndDocument();
}

void ProjectDocument::readModel(SessionModel *model, QXmlStreamReader *reader)
{
    model->setMessageService(m_messageService);
//    m_messageService->subscribe(model);
    model->readFrom(reader);

    if(m_messageService->hasWarnings(model)) {
        m_documentStatus = EDocumentStatus(m_documentStatus|STATUS_WARNING);
    }
    model->setMessageService(0);
}

//! Adjusts name of IntensityData item to possibly changed name of JobItem. Take care of old
//! *.int files in project directory by removing them.
void ProjectDocument::reviseOutputData()
{
    for (int i = 0; i < m_jobModel->rowCount(QModelIndex()); ++i) {
        JobItem *jobItem = m_jobModel->getJobItemForIndex(m_jobModel->index(i, 0, QModelIndex()));
        IntensityDataItem *dataItem = jobItem->getIntensityDataItem();
        if (dataItem) {
            // handling case when user has renamed jobItem and we have to clean previous
            // *.int file
            QString filename = getProjectDir() + "/" + dataItem->itemName();
            QFile fin(filename);
            if (fin.exists()) {
                fin.remove();
            }

            // making new name of *.int file from jobItem name
            dataItem->setNameFromProposed(jobItem->itemName());
        }
    }
}

//! saves OutputData into project directory
void ProjectDocument::saveOutputData()
{
    Q_ASSERT(m_jobModel);
    for (int i = 0; i < m_jobModel->rowCount(QModelIndex()); ++i) {
        JobItem *jobItem = m_jobModel->getJobItemForIndex(m_jobModel->index(i, 0, QModelIndex()));
        IntensityDataItem *dataItem = jobItem->getIntensityDataItem();
        if (dataItem) {
            QString filename = getProjectDir() + "/" + dataItem->itemName();
            const OutputData<double> *data = dataItem->getOutputData();
            if (data) {
                IntensityDataIOFactory::writeIntensityData(*data, filename.toStdString());
            }
        }
    }
}

//! load OutputData from project directory
void ProjectDocument::loadOutputData()
{
    for (int i = 0; i < m_jobModel->rowCount(QModelIndex()); ++i) {
        JobItem *jobItem = m_jobModel->getJobItemForIndex(m_jobModel->index(i, 0, QModelIndex()));
        IntensityDataItem *dataItem = jobItem->getIntensityDataItem();
        if (dataItem) {
            QString filename = getProjectDir() + "/" + dataItem->itemName();
            QFileInfo info(filename);
            if (info.exists()) {
                jobItem->getIntensityDataItem()->setOutputData(
                    IntensityDataIOFactory::readIntensityData(filename.toStdString()));
            } else {
                jobItem->setStatus(Constants::STATUS_FAILED);
                QString warning("Error while loading job from file, intensity data file '");
                warning.append(filename);
                warning.append("' was not found");
                jobItem->setComments(warning);
            }
        }
    }
}

void ProjectDocument::disconnectModel(SessionModel *model)
{
    if(model) {
        disconnect(model, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,
                   SLOT(onDataChanged(QModelIndex, QModelIndex)));
        disconnect(model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                   SLOT(onRowsChanged(QModelIndex, int, int)));
        disconnect(model, SIGNAL(rowsInserted(QModelIndex, int,int)), this,
                   SLOT(onRowsChanged(QModelIndex, int,int)));
    }
}

void ProjectDocument::connectModel(SessionModel *model)
{
    if(model) {
        connect(model, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,
                   SLOT(onDataChanged(QModelIndex, QModelIndex)));
        connect(model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                   SLOT(onRowsChanged(QModelIndex, int, int)));
        connect(model, SIGNAL(rowsInserted(QModelIndex, int,int)), this,
                   SLOT(onRowsChanged(QModelIndex, int,int)));
    }
}

