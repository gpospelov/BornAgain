#ifndef PROJECTDOCUMENT_H
#define PROJECTDOCUMENT_H

#include <QObject>
#include <QString>

class JobQueueModel;
class QIODevice;
class QModelIndex;


namespace ProjectDocumentXML
{
    const QString InfoTag("DocumentInfo");
    const QString InfoNameAttribute("ProjectName");
}


//! Project document class handles all data related to the opened project
//! (sample, jobModel, project specific windows settings)
class ProjectDocument : public QObject
{
    Q_OBJECT

public:
    ProjectDocument();
    ProjectDocument(const QString &path, const QString &name);

    bool save();

    QString getProjectPath() const { return m_project_path; }
    QString getProjectName() const { return m_project_name; }

    void setProjectPath(const QString &text) { m_project_path = text; }
    void setProjectName(const QString &text) { m_project_name = text; emit modified();}
    QString getProjectFileName();

    static ProjectDocument *openExistingDocument(const QString &filename);

    bool isModified() { return m_modified; }
    void setModel(JobQueueModel *model);

    bool hasValidNameAndPath();

signals:
    void modified();

public slots:
    void onDataChanged(const QModelIndex &, const QModelIndex &);

private:
    bool write(QIODevice *device);
    bool read(QIODevice *device);

    QString m_project_path;
    QString m_project_name;
    JobQueueModel *m_jobQueueModel;
    bool m_modified;
};


#endif

