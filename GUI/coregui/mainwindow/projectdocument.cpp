#include "projectdocument.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <iostream>

ProjectDocument::ProjectDocument(const QString &path, const QString &name)
    : m_project_path(path)
    , m_project_name(name)
{
//    generate_clean_document();
}


//void ProjectDocument::generate_clean_document()
//{
//    QDomProcessingInstruction xmlHeaderPI = m_dom_document.createProcessingInstruction("xml", "version=\"1.0\" " );
//    m_dom_document.appendChild(xmlHeaderPI);
//    QDomElement root = m_dom_document.createElement("BornAgain");
//    m_dom_document.appendChild(root);
//    QDomElement childElement = m_dom_document.createElement("project");
//    childElement.setAttribute(QString("name"), QString("Untitled"));
//    root.appendChild(childElement);
//}


bool ProjectDocument::save()
{
    QString filename = getProjectFileName();
    std::cout << "ProjectDocument::saveProjectFile " << filename.toStdString()<< std::endl;
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        std::cout << "ProjectDocument::save() -> Error! Can't save file" << std::endl;
        return false;
    }
    write(&file);
    file.close();
    return true;
}


ProjectDocument *ProjectDocument::openExistingDocument(const QString &filename)
{
    std::cout << "ProjectDocument::openExistingDocument -> " << filename.toStdString() << std::endl;
    QFileInfo info(filename);
    std::cout << " " << info.baseName().toStdString() << " " << info.path().toStdString() << std::endl;

    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        std::cout << "ProjectDocument::openExistingDocument -> Error. Can't open file" << std::endl;
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
    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument domDocument;

    if (!domDocument.setContent(device, true, &errorStr, &errorLine,
                                &errorColumn)) {
        std::cout << "ProjectDocument::read() -> parse error!" << std::endl;
//        QMessageBox::information(0, tr("DOM Bookmarks"),
//                                 tr("Parse error at line %1, column %2:\n%3")
//                                 .arg(errorLine)
//                                 .arg(errorColumn)
//                                 .arg(errorStr));
        return false;
    }

    QDomElement root = domDocument.documentElement();
    if (root.tagName() != "BornAgain") {
        std::cout << "ProjectDocument::read() -> This is not BornAgain file" << std::endl;
        return false;
    }

    QDomElement child = root.firstChildElement("project");
    QString name = child.attribute("name");
    std::cout << "ProjectDocument::read() " << name.toStdString() << std::endl;

    return true;

}



bool ProjectDocument::write(QIODevice *device)
{
    const int IndentSize = 4;
    QTextStream out(device);
    QDomDocument dom_document("BornAgain");

    QDomProcessingInstruction xmlHeaderPI = dom_document.createProcessingInstruction("xml", "version=\"1.0\" " );
    dom_document.appendChild(xmlHeaderPI);
    QDomElement root = dom_document.createElement("BornAgain");
    dom_document.appendChild(root);
    QDomElement childElement = dom_document.createElement("project");
    childElement.setAttribute(QString("name"), getProjectName());
    root.appendChild(childElement);

    dom_document.save(out, IndentSize);

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

