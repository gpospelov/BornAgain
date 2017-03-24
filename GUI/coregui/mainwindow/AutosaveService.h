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
class QTimer;

//! Handles activity related to opening/save projects.

class BA_CORE_API_ AutosaveService : public QObject
{
    Q_OBJECT
public:
    AutosaveService(QObject* parent);

    void setDocument(ProjectDocument* document);

private slots:
    void onTimerTimeout();
    void onDocumentDestroyed(QObject* object);
    void onDocumentModified();

private:
    void autosave();
    bool isDocumentForAutosave();
    QString autosaveName() const;

    ProjectDocument* m_document;
    QTimer* m_timer;
    qint64 m_modificationCount;
};

#endif
