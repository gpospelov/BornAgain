// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/SaveService.h
//! @brief     Defines class SaveService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAVESERVICE_H
#define SAVESERVICE_H

#include "WinDllMacros.h"
#include <QObject>
#include <QQueue>

class ProjectDocument;
class AutosaveController;

//! Provides save/autosave of ProjectDocument in a thread.

class BA_CORE_API_ SaveService : public QObject
{
    Q_OBJECT

public:
    explicit SaveService(QObject* parent = 0);

    void setDocument(ProjectDocument* document);

    void save(const QString& project_file_name);

    void setAutosaveEnabled(bool value);

    //! Sets autosave time (in msec)
    void setAutosaveTime(int timerInterval);

    bool isSaving() const;


signals:
    void projectSaved();

public slots:
    void onAutosaveRequest();

private slots:
    void onProjectSaved();

private:
    void process_queue();

    QQueue<QString> m_save_queue;
    bool m_is_saving;
    AutosaveController* m_autosave;
    ProjectDocument* m_document;
};


#endif
