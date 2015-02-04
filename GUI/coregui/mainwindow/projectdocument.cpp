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
//#include "JobQueueModel.h"
//#include "JobItem.h"
//#include "OutputDataItem.h"
#include "NJobModel.h"
#include "NJobItem.h"
#include "NIntensityDataItem.h"
#include "SampleModel.h"
#include "IntensityDataIOFactory.h"
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
    : m_materialModel(0)
    , m_instrumentModel(0)
    , m_sampleModel(0)
//    , m_jobQueueModel(0)
    , m_jobModel(0)
    , m_modified(false)
{

}

ProjectDocument::ProjectDocument(const QString &projectFileName)
    : m_sampleModel(0)
//    , m_jobQueueModel(0)
    , m_jobModel(0)
    , m_modified(false)
{
    setProjectFileName(projectFileName);
    qDebug() << "ProjectDocument::ProjectDocument(const QString &projectFileName)"
             << projectFileName << getProjectPath() << getProjectName() << getProjectFileName();
}


void ProjectDocument::setProjectFileName(const QString &projectFileName)
{
    QFileInfo info(projectFileName);
    setProjectName(info.baseName());

    QFileInfo info_dir(info.path());
    setProjectPath(info_dir.path());
}



ProjectDocument::ProjectDocument(const QString &path, const QString &name)
    : m_project_path(path)
    , m_project_name(name)
    , m_materialModel(0)
    , m_sampleModel(0)
//    , m_jobQueueModel(0)
    , m_jobModel(0)
    , m_modified(false)
{

}


void ProjectDocument::onDataChanged(const QModelIndex &, const QModelIndex &)
{
    qDebug() << "ProjectDocument::onDataChanged()";
    m_modified = true;
    emit modified();
}


//void ProjectDocument::onJobQueueModelChanged(const QString &)
//{
//    m_modified = true;
//    emit modified();
//}
void ProjectDocument::onJobModelChanged(const QString &)
{
    m_modified = true;
    emit modified();
}


void ProjectDocument::setMaterialModel(MaterialModel *materialModel)
{
    if(materialModel != m_materialModel) {
        if(m_materialModel) disconnect(m_materialModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );
        m_materialModel = materialModel;
        connect(m_materialModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );
    }
}

void ProjectDocument::setInstrumentModel(InstrumentModel *model)
{
    if(model != m_instrumentModel) {
        if(m_instrumentModel) disconnect(m_instrumentModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );
        m_instrumentModel = model;
        connect(m_instrumentModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );
    }
}


void ProjectDocument::setSampleModel(SampleModel *model)
{
    if(model != m_sampleModel) {
        if(m_sampleModel) disconnect(m_sampleModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );
        m_sampleModel = model;
        connect(m_sampleModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );
    }
}


void ProjectDocument::setJobModel(NJobModel *model)
{
    if(model != m_jobModel) {
        if(m_jobModel) {
            disconnect(m_jobModel->getJobQueueData(), SIGNAL(jobIsFinished(QString)), this, SLOT(onJobModelChanged(QString)));
        }
//        m_jobQueueModel = model;
        m_jobModel = model;

//        connect(m_jobQueueModel->getJobQueueData(), SIGNAL(jobIsFinished(QString)), this, SLOT(onJobQueueModelChanged(QString)));
        connect(m_jobModel->getJobQueueData(), SIGNAL(jobIsFinished(QString)), this, SLOT(onJobModelChanged(QString)));
    }
}


bool ProjectDocument::hasValidNameAndPath()
{
    return (!m_project_name.isEmpty() && !m_project_path.isEmpty());
}


bool ProjectDocument::save()
{
    qDebug() << "ProjectDocument::save() -> " << getProjectName() << getProjectPath() << getProjectFileName();

    QString filename = getProjectFileName();

    QFile file(filename);
    //if (!file.open(QFile::WriteOnly | QFile::Text)) {
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


bool ProjectDocument::load()
{
    qDebug() << "ProjectDocument::load() -> " << getProjectFileName();
    //QFileInfo info(filename);
    //qDebug()  << info.baseName() << " " << info.path();

    QFile file(getProjectFileName());
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "ProjectDocument::openExistingDocument -> Error. Can't open file" << getProjectFileName();
        return 0;
    }

    //ProjectDocument *result = new ProjectDocument(info.path(), info.baseName());

    bool success_read = readFrom(&file);
    file.close();

    // loading non-xml data
    loadOutputData();

    return success_read;
}


bool ProjectDocument::readFrom(QIODevice *device)
{
    Q_ASSERT(m_materialModel);
    disconnect(m_materialModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );

    Q_ASSERT(m_instrumentModel);
    disconnect(m_instrumentModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );

    Q_ASSERT(m_sampleModel);
    disconnect(m_sampleModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );

//    Q_ASSERT(m_jobQueueModel);
    Q_ASSERT(m_jobModel);
    disconnect(m_jobModel->getJobQueueData(), SIGNAL(jobIsFinished(QString)), this, SLOT(onJobModelChanged(QString)));

    QXmlStreamReader reader(device);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {

            if (reader.name() == ProjectDocumentXML::InfoTag) {
                //
            }
            else if(reader.name() == SessionXML::MaterialModelTag) {
                m_materialModel->readFrom(&reader);

            }
            else if(reader.name() == SessionXML::InstrumentModelTag) {
                m_instrumentModel->readFrom(&reader);

            }
            else if(reader.name() == SessionXML::SampleModelTag) {
                m_sampleModel->readFrom(&reader);

            }
            else if(reader.name() == SessionXML::JobModelTag) {
//                m_jobQueueModel->readFrom(&reader);
                m_jobModel->readFrom(&reader);
            }
        }
    }

    if (reader.hasError())
        throw GUIHelpers::Error(reader.errorString());

    connect(m_materialModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );
    connect(m_instrumentModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );
    connect(m_sampleModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );
//    connect(m_jobQueueModel->getJobQueueData(), SIGNAL(jobIsFinished(QString)), this, SLOT(onJobQueueModelChanged(QString)));
    connect(m_jobModel->getJobQueueData(), SIGNAL(jobIsFinished(QString)), this, SLOT(onJobModelChanged(QString)));

    return true;

}


bool ProjectDocument::writeTo(QIODevice *device)
{
    QXmlStreamWriter writer(device);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("BornAgain");
    writer.writeAttribute("Version", "1.9");

    writer.writeStartElement(ProjectDocumentXML::InfoTag);
    writer.writeAttribute(ProjectDocumentXML::InfoNameAttribute, getProjectName());
    writer.writeEndElement(); // InfoTag

    Q_ASSERT(m_materialModel);
    m_materialModel->writeTo(&writer);

    Q_ASSERT(m_instrumentModel);
    m_instrumentModel->writeTo(&writer);

    Q_ASSERT(m_sampleModel);
    m_sampleModel->writeTo(&writer);

    Q_ASSERT(m_jobModel);
    m_jobModel->writeTo(&writer);

    writer.writeEndElement(); // BornAgain
    writer.writeEndDocument();

    return true;
}


//! returns project file name
//!
//! if ProjectPath=/home/username and ProjectName=MultiLayer then project file
//! will be /home/username/MultiLayer/MultiLayer.pro
QString ProjectDocument::getProjectFileName()
{
    QString result = getProjectPath() + "/" + getProjectName() + "/"+getProjectName()+".pro";
    return result;
}

//! returns project directory
QString ProjectDocument::getProjectDir()
{
    QString result = getProjectPath() + "/" + getProjectName();
    return result;
}


//! saves OutputData into project directory
void ProjectDocument::saveOutputData()
{
    Q_ASSERT(m_jobModel);

//    for(int i=0; i<m_jobQueueModel->rowCount(); ++i) {
//        JobItem *jobItem = m_jobQueueModel->getJobItemForIndex(m_jobQueueModel->index(i,0));
//        OutputDataItem *dataItem = jobItem->getOutputDataItem();
//        if(dataItem) {
//            QString filename = getProjectDir() + "/" + dataItem->getName();
//            const OutputData<double> *data = dataItem->getOutputData();
//            if(data) {
//                IntensityDataIOFactory::writeIntensityData(*data, filename.toStdString());
//            }
//        }
//    }
    for(int i=0; i<m_jobModel->rowCount(QModelIndex()); ++i) {
        NJobItem *jobItem = m_jobModel->getJobItemForIndex(m_jobModel->index(i,0, QModelIndex()));
        NIntensityDataItem *dataItem = jobItem->getIntensityDataItem();
        if(dataItem) {
            QString filename = getProjectDir() + "/" + dataItem->itemName();
            const OutputData<double> *data = dataItem->getOutputData();
            if(data) {
                IntensityDataIOFactory::writeIntensityData(*data, filename.toStdString());
            }
        }
    }

}


//! load OutputData from project directory
void ProjectDocument::loadOutputData()
{
    Q_ASSERT(m_jobModel);

//    for(int i=0; i<m_jobQueueModel->rowCount(); ++i) {
//        JobItem *jobItem = m_jobQueueModel->getJobItemForIndex(m_jobQueueModel->index(i,0));
//        OutputDataItem *dataItem = jobItem->getOutputDataItem();
//        if(dataItem) {
//            QString filename = getProjectDir() + "/" + dataItem->getName();
//            QFileInfo info(filename);
//            if(info.exists()) {
//                jobItem->getOutputDataItem()->setOutputData(IntensityDataIOFactory::readIntensityData(filename.toStdString()));
//            }
//        }
//    }
    for(int i=0; i<m_jobModel->rowCount(QModelIndex()); ++i) {
        NJobItem *jobItem = m_jobModel->getJobItemForIndex(m_jobModel->index(i,0, QModelIndex()));
        NIntensityDataItem *dataItem = jobItem->getIntensityDataItem();
        if(dataItem) {
            QString filename = getProjectDir() + "/" + dataItem->itemName();
            QFileInfo info(filename);
            if(info.exists()) {
                jobItem->getIntensityDataItem()->setOutputData(IntensityDataIOFactory::readIntensityData(filename.toStdString()));
            }
        }
    }


}



