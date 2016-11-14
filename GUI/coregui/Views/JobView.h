// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobView.h
//! @brief     Defines class JobView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBVIEW_H
#define JOBVIEW_H

#include "WinDllMacros.h"
#include "fancymainwindow.h"

class MainWindow;
class JobViewDocks;
class JobActivityStatusBar;
class JobProgressAssistant;
class JobItem;

//! The JobView class is a main view to show list of jobs, job results and widgets for real time
//! and fitting activities.

class BA_CORE_API_ JobView : public Manhattan::FancyMainWindow
{
    Q_OBJECT

public:
    JobView(MainWindow *mainWindow);

signals:
    void focusRequest(int);
    void activityChanged(int activity);

public slots:
    void onFocusRequest(JobItem *jobItem);
    void setActivity(int activity);
    void onDockMenuRequest();
    void onSelectionChanged(JobItem *jobItem);

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private:
    void connectSignals();
    void connectActivityRelated();
    void connectLayoutRelated();
    void connectJobRelated();

    void setAppropriateActivityForJob(JobItem *jobItem);

    JobViewDocks *m_docks;
    JobActivityStatusBar *m_jobActivityStatusBar;
    JobProgressAssistant *m_progressAssistant;
    JobItem *m_currentItem;
    MainWindow *m_mainWindow;
};

#endif // JOBVIEW_H
