#include "projectdocument.h"
#include "JobQueueModel.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <QModelIndex>
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
    write(&file);
    file.close();

    m_modified = false;
    emit modified();

    return true;
}


ProjectDocument *ProjectDocument::openExistingDocument(const QString &filename)
{
    qDebug() << "ProjectDocument::openExistingDocument -> " << filename;
    QFileInfo info(filename);
    qDebug()  << info.baseName() << " " << info.path();

    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "ProjectDocument::openExistingDocument -> Error. Can't open file";
        return 0;
    }

    ProjectDocument *result = new ProjectDocument(info.path(), info.baseName());

    bool success_read = result->read(&file);
    file.close();

    if(success_read) {
        return result;
    } else {
        delete result;
        return 0;
    }
}

bool ProjectDocument::read(QIODevice *device)
{
//    QString errorStr;
//    int errorLine;
//    int errorColumn;

//    QDomDocument domDocument;

//    if (!domDocument.setContent(device, true, &errorStr, &errorLine,
//                                &errorColumn)) {
//        std::cout << "ProjectDocument::read() -> parse error!" << std::endl;
////        QMessageBox::information(0, tr("DOM Bookmarks"),
////                                 tr("Parse error at line %1, column %2:\n%3")
////                                 .arg(errorLine)
////                                 .arg(errorColumn)
////                                 .arg(errorStr));
//        return false;
//    }

//    QDomElement root = domDocument.documentElement();
//    if (root.tagName() != "BornAgain") {
//        std::cout << "ProjectDocument::read() -> This is not BornAgain file" << std::endl;
//        return false;
//    }

//    QDomElement child = root.firstChildElement("project");
//    QString name = child.attribute("name");
//    std::cout << "ProjectDocument::read() " << name.toStdString() << std::endl;



//    QXmlStreamReader reader(device);

//    while (!reader->atEnd()) {
//        reader->readNext();
//        if (reader->isStartElement()) {

//            if (reader->name() == ProjectDocumentXML::InfoTag) {
//                //
//            } else if(reader->name() == JobQueueXML::ModelTag) {
//                m_jobQueueModel->readFrom(&reader);
//            }
//        }
//    }

//    if (reader.hasError())
//        throw GUIHelpers::Error(reader.errorString());



    return true;

}


bool ProjectDocument::write(QIODevice *device)
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


//! constructs project file name from ProjectPath and ProjectName
//! if ProjectPath=/home/username and ProjectName=MultiLayer then project file
//! will be /home/username/MultiLayer/MultiLayer.pro
QString ProjectDocument::getProjectFileName()
{
    QString result = getProjectPath() + "/" + getProjectName() + "/"+getProjectName()+".pro";
    return result;
}

