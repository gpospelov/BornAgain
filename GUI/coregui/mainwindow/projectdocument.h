// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/projectdocument.h
//! @brief     Defines class ProjectDocument
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PROJECTDOCUMENT_H
#define PROJECTDOCUMENT_H

#include "WinDllMacros.h"
#include <QObject>
#include <QString>

class QIODevice;
class QModelIndex;
class JobItem;
class SessionModel;
class InstrumentModel;
class MaterialModel;
class SampleModel;
class JobModel;
class QXmlStreamReader;
class WarningMessageService;

namespace ProjectDocumentXML
{
const QString BornAgainTag("BornAgain");
const QString BornAgainVersionAttribute("Version");
const QString InfoTag("DocumentInfo");
const QString InfoNameAttribute("ProjectName");
}


//! Project document class handles all data related to the opened project
//! (sample, jobModel, project specific windows settings)
//!
//! e.g. if project file is /home/users/development/Untitled/Untitled.pro
//! getProjectName()     - 'Untitled'
//! getProjectDir()      - 'home/users/development/Untitled
//! getProjectFileName() - '/home/users/development/Untitled/Untitled.pro'
class BA_CORE_API_ ProjectDocument : public QObject
{
    Q_OBJECT

public:
    enum EDocumentStatus {
        STATUS_OK = 0x0001,
        STATUS_WARNING = 0x0002,
        STATUS_FAILED = 0x0004
    };

    ProjectDocument();
    ProjectDocument(const QString &projectFileName);

    QString getProjectName() const;
    void setProjectName(const QString &text);

    QString getProjectDir() const;
    void setProjectDir(const QString &text);

    QString getProjectFileName() const;
    void setProjectFileName(const QString &text);

    static QString getProjectFileExtension();

    void setMaterialModel(MaterialModel *materialModel);
    void setInstrumentModel(InstrumentModel *instrumentModel);
    void setSampleModel(SampleModel *sampleModel);
    void setJobModel(JobModel *jobModel);

    bool save();
    bool load(const QString &project_file_name);

    bool hasValidNameAndPath();

    bool isModified();

    void setMessageService(WarningMessageService *messageService);

    EDocumentStatus getDocumentStatus() const;

    bool isReady() const;

    bool hasWarnings() const;

    bool hasErrors() const;

    QString getDocumentVersion() const;

signals:
    void modified();

public slots:
    void onDataChanged(const QModelIndex &, const QModelIndex &);
    void onJobModelChanged(const QString &);
    void onRowsChanged(const QModelIndex &parent, int, int);

private:
    void readFrom(QIODevice *device);
    void writeTo(QIODevice *device);
    void readModel(SessionModel *model, QXmlStreamReader *reader);

    void reviseOutputData();
    void saveOutputData();
    void loadOutputData();

    void disconnectModel(SessionModel *model);
    void connectModel(SessionModel *model);

    QString m_project_dir;
    QString m_project_name;
    MaterialModel *m_materialModel;
    InstrumentModel *m_instrumentModel;
    SampleModel *m_sampleModel;
    JobModel *m_jobModel;
    bool m_modified;
    EDocumentStatus m_documentStatus;
    WarningMessageService *m_messageService;
    QString m_currentVersion;
};


#endif

