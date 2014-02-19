#ifndef PROJECTDOCUMENT_H
#define PROJECTDOCUMENT_H


#include <QDomDocument>

//! Project document class handles all data related to the opened project
//! (sample, jobModel, project specific windows settings)
class ProjectDocument
{
public:
    ProjectDocument(){}
    ProjectDocument(const QString &path, const QString &name);

    bool save();

    QString getProjectPath() const { return m_project_path; }
    QString getProjectName() const { return m_project_name; }

    void setProjectPath(const QString &text) { m_project_path = text; }
    void setProjectName(const QString &text) { m_project_name = text; }

    static ProjectDocument *openExistingDocument(const QString &filename);

private:
    bool write(QIODevice *device);
    bool read(QIODevice *device);
    void generate_clean_document();
    QString getProjectFileName();

    QString m_project_path;
    QString m_project_name;
//    QDomDocument m_dom_document;
};


#endif

