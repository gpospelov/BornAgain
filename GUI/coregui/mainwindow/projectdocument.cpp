#include "projectdocument.h"
#include "JobQueueModel.h"
#include "JobItem.h"
#include "OutputDataItem.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <QModelIndex>
#include "GUIHelpers.h"
//#include <iostream>
//#include <QDomDocument>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>



ProjectDocument::ProjectDocument()
    : m_jobQueueModel(0)
    , m_modified(false)
{

}

ProjectDocument::ProjectDocument(const QString &projectFileName)
    : m_jobQueueModel(0)
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
    , m_jobQueueModel(0)
    , m_modified(false)
{

}


void ProjectDocument::onDataChanged(const QModelIndex &, const QModelIndex &)
{
    qDebug() << "ProjectDocument::onDataChanged()";
    m_modified = true;
    emit modified();
}


void ProjectDocument::setModel(JobQueueModel *model)
{
    if(model != m_jobQueueModel) {
        m_jobQueueModel = model;
        connect(m_jobQueueModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );
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

    loadOutputData();

    return success_read;
}


bool ProjectDocument::readFrom(QIODevice *device)
{

    Q_ASSERT(m_jobQueueModel);
    disconnect(m_jobQueueModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );

    QXmlStreamReader reader(device);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {

            if (reader.name() == ProjectDocumentXML::InfoTag) {
                //
            } else if(reader.name() == JobQueueXML::ModelTag) {
                m_jobQueueModel->readFrom(&reader);
            }
        }
    }

    if (reader.hasError())
        throw GUIHelpers::Error(reader.errorString());

    connect(m_jobQueueModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onDataChanged(QModelIndex, QModelIndex)) );

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

    Q_ASSERT(m_jobQueueModel);
    m_jobQueueModel->writeTo(&writer);

    writer.writeEndElement(); // BornAgain
    writer.writeEndDocument();

//    const int IndentSize = 4;
//    QTextStream out(device);
//    QDomDocument dom_document("BornAgain");

//    QDomProcessingInstruction xmlHeaderPI = dom_document.createProcessingInstruction("xml", "version=\"1.0\" " );
//    dom_document.appendChild(xmlHeaderPI);
//    QDomElement root = dom_document.createElement("BornAgain");
//    dom_document.appendChild(root);
//    QDomElement childElement = dom_document.createElement("project");
//    childElement.setAttribute(QString("name"), getProjectName());
//    root.appendChild(childElement);

//    dom_document.save(out, IndentSize);

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
    Q_ASSERT(m_jobQueueModel);

    for(int i=0; i<m_jobQueueModel->rowCount(); ++i) {
        JobItem *jobItem = m_jobQueueModel->getJobItemForIndex(m_jobQueueModel->index(i,0));
        OutputDataItem *dataItem = jobItem->getOutputDataItem();
        if(dataItem) {
            QString filename = getProjectDir() + "/" + dataItem->getName();
            const OutputData<double> *data = dataItem->getOutputData();
            if(data) {
                OutputDataIOFactory::writeIntensityData(*data, filename.toStdString());
            }
        }

    }
}


//! load OutputData from project directory
void ProjectDocument::loadOutputData()
{
    for(int i=0; i<m_jobQueueModel->rowCount(); ++i) {
        JobItem *jobItem = m_jobQueueModel->getJobItemForIndex(m_jobQueueModel->index(i,0));
        OutputDataItem *dataItem = jobItem->getOutputDataItem();
        if(dataItem) {
            QString filename = getProjectDir() + "/" + dataItem->getName();
            QFileInfo info(filename);
            if(info.exists()) {
                jobItem->getOutputDataItem()->setOutputData(OutputDataIOFactory::readIntensityData(filename.toStdString()));
            }
        }
    }
}



