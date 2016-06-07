// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobView.h
//! @brief     Declares class JobView
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

//! The JobView class is a main view to show list of jobs, their results and widgets for real time
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
    void updateGlobalProgressBar(int);
    void onFocusRequest(class JobItem *);
    void resetToDefaultLayout();
    void setActivity(int activity);
    void onToggleJobListRequest();
    void onDockMenuRequest();

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private:
    void connectSignals();

    class JobViewDocks *m_docks;
    class JobActivityStatusBar *m_jobActivityStatusBar;
    MainWindow *m_mainWindow;
};

#endif
