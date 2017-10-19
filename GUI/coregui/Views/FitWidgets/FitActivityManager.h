// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitActivityManager.h
//! @brief     Defines class FitActivityManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITACTIVITYMANAGER_H
#define FITACTIVITYMANAGER_H

#include "WinDllMacros.h"
#include <QObject>
#include <QMap>

class JobModel;
class SessionItem;
class JobItem;
class FitSuiteManager;
class JobMessagePanel;

//! Handles all activity related to the simultaneous running of fitting jobs.

class BA_CORE_API_ FitActivityManager : public QObject
{
    Q_OBJECT
public:
    FitActivityManager(QObject* parent = nullptr);

    void setMessagePanel(JobMessagePanel* messagePanel);

    FitSuiteManager* manager(JobItem* item);

    void disableLogging();

private:
    FitSuiteManager* createManager(JobItem* jobItem);
    void removeManager(SessionItem* jobItem);

    FitSuiteManager* m_activeManager;
    JobMessagePanel* m_jobMessagePanel;
    QMap<SessionItem*, FitSuiteManager*> m_item_to_manager;
};

#endif
