// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSuiteManager.h
//! @brief     Defines class FitSuiteManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEMANAGER_H
#define FITSUITEMANAGER_H

#include "WinDllMacros.h"
#include <QObject>
#include <memory>

class JobItem;
class RunFitManager;
class GUIFitObserver;

//! Handles all activity related to the single fitting task for JobItem.
//! Provides interaction between FitSuiteWidget and fit observers.

class BA_CORE_API_ FitSuiteManager : public QObject
{
    Q_OBJECT
public:
    FitSuiteManager(QObject* parent = nullptr);

    void setItem(JobItem* item);

    void startFitting();

    RunFitManager* runFitManager();
    std::shared_ptr<GUIFitObserver> fitObserver();

private slots:
    void onPlotsUpdate();

private:
    JobItem* m_jobItem;
    RunFitManager *m_runFitManager;
    std::shared_ptr<GUIFitObserver> m_observer;
};

#endif
