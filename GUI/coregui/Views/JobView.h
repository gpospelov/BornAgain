//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/JobView.h
//! @brief     Defines class JobView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBVIEW_H

#include <QActionGroup>
#include <QMainWindow>

class MainWindow;
class JobView;
class JobSelectorWidget;
class JobOutputDataWidget;
class JobRealTimeWidget;
class FitActivityPanel;
class JobMessagePanel;
class JobProgressAssistant;
class JobItem;
class DocksController;

//! The JobView class is a main view to show list of jobs, job results and widgets for real time
//! and fitting activities.

class JobView : public QMainWindow {
    Q_OBJECT

public:
    JobView(MainWindow* mainWindow);

    void fillViewMenu(QMenu* menu);

signals:
    void focusRequest(int);
    void activityChanged(int activity);

public slots:
    void onFocusRequest(JobItem* jobItem);
    void setActivity(int activity);
    void onSelectionChanged(JobItem* jobItem);

private:
    void createSubWindows();
    void createActions();
    void connectSignals();
    void connectActivityRelated();
    void connectJobRelated();

    void setAppropriateActivityForJob(JobItem* jobItem);
    void resetLayout();

    DocksController* m_docks;
    JobProgressAssistant* m_progressAssistant;
    JobItem* m_currentItem;
    MainWindow* m_mainWindow;

    JobSelectorWidget* m_jobSelector = nullptr;
    JobOutputDataWidget* m_jobOutputDataWidget = nullptr;
    JobRealTimeWidget* m_jobRealTimeWidget = nullptr;
    FitActivityPanel* m_fitActivityPanel = nullptr;
    JobMessagePanel* m_jobMessagePanel = nullptr;

    QActionGroup m_activityActions;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBVIEW_H
