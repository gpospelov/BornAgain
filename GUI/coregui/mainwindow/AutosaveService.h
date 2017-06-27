// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/AutosaveService.h
//! @brief     Defines class AutosaveService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef AUTOSAVESERVICE_H
#define AUTOSAVESERVICE_H

#include "WinDllMacros.h"
#include <QObject>

class ProjectDocument;
class UpdateTimer;

//! Handles activity related to opening/save projects.

class BA_CORE_API_ AutosaveService : public QObject
{
    Q_OBJECT
public:
    explicit AutosaveService(QObject* parent = 0);

    void setDocument(ProjectDocument* document);

    //! Sets autosave time (in msec)
    void setAutosaveTime(int timerInterval);

    QString autosaveDir() const;
    QString autosaveName() const;

    //! remove auto save directory for given project and all its content
    void removeAutosaveDir();

signals:
    void autosaveRequest();

private slots:
    void onTimerTimeout();
    void onDocumentDestroyed(QObject* object);
    void onDocumentModified();

private:
    void autosave();
    void setDocumentConnected(bool set_connected);

    ProjectDocument* m_document;
    UpdateTimer* m_timer;
};

#endif
