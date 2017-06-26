// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/projectdocument.h
//! @brief     Defines class ProjectDocument
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROJECTDOCUMENT_H
#define PROJECTDOCUMENT_H

#include "WinDllMacros.h"
#include "ProjectFlags.h"
#include <QObject>

class QIODevice;
class ApplicationModels;
class WarningMessageService;
class OutputDataIOService;

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
//! projectName()     - 'Untitled'
//! projectDir()      - '/home/users/development/Untitled
//! projectFileName() - '/home/users/development/Untitled/Untitled.pro'
class BA_CORE_API_ ProjectDocument : public QObject
{
    Q_OBJECT

public:
    ProjectDocument(const QString& projectFileName = QString());

    QString projectName() const;
    void setProjectName(const QString& text);

    QString projectDir() const;
    void setProjectDir(const QString& text);

    QString projectFileName() const;
    void setProjectFileName(const QString& text);

    static QString projectFileExtension();

    void setApplicationModels(ApplicationModels* applicationModels);

    bool save(const QString& project_file_name, bool autoSave = false);
    bool load(const QString& project_file_name);

    bool hasValidNameAndPath();

    bool isModified();
    void setModified(bool flag);

    void setLogger(WarningMessageService* messageService);

    ProjectFlags::DocumentStatus documentStatus() const;

    bool isReady() const;

    bool hasWarnings() const;

    bool hasErrors() const;

    bool isSaving() const;

    QString documentVersion() const;

signals:
    void modified();

public slots:
    void onModelChanged();

private:
    bool save_document(const QString& project_file_name, bool autoSave = false);
    void readFrom(QIODevice* device);
    void writeTo(QIODevice* device);

    void disconnectModels();
    void connectModels();

    QString m_project_dir;
    QString m_project_name;
    ApplicationModels* m_applicationModels;
    bool m_modified;
    ProjectFlags::DocumentStatus m_documentStatus;
    WarningMessageService* m_messageService;
    QString m_currentVersion;
    OutputDataIOService* m_dataService;
};

#endif // PROJECTDOCUMENT_H
