//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/JobWidgets/JobSelectorWidget.h
//! @brief     Defines class JobSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBSELECTORWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBSELECTORWIDGET_H

#include <QWidget>

class JobModel;
class JobItem;
class JobSelectorToolBar;
class JobSelectorActions;
class JobListWidget;
class JobPropertiesWidget;

//! The JobSelectorWidget class represents left panel of JobView. Contains a tree to select jobs
//! on the top and job property editor at the bottom.

class JobSelectorWidget : public QWidget {
    Q_OBJECT

public:
    explicit JobSelectorWidget(JobModel* jobModel, QWidget* parent = nullptr);

    void setModel(JobModel* jobModel);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    const JobItem* currentJobItem() const;

signals:
    void selectionChanged(JobItem*);

public slots:
    void makeJobItemSelected(JobItem*);

private slots:
    void onSelectionChanged(JobItem* jobItem);

private:
    JobSelectorActions* m_jobSelectorActions;
    JobSelectorToolBar* m_toolBar;
    JobListWidget* m_jobListWidget;
    JobPropertiesWidget* m_jobProperties;
    JobModel* m_jobModel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBSELECTORWIDGET_H
