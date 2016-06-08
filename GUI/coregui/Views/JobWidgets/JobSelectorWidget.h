// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobSelectorWidget.h
//! @brief     Declares class JobSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBSELECTORWIDGET_H
#define JOBSELECTORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class JobModel;
class JobItem;

//! The JobSelectorWidget class represents left panel of JobView. Contains a tree to select jobs
//! on the top and job property editor at the bottom.

class BA_CORE_API_ JobSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JobSelectorWidget(JobModel *jobModel, QWidget *parent = 0);

    void setModel(JobModel *model);

    QSize sizeHint() const { return QSize(210, 600); }
    QSize minimumSizeHint() const { return QSize(64, 300); }

public slots:
    void makeJobItemSelected(JobItem *);

private:
    class QSplitter *m_splitter;
    class StyledToolBar *m_toolBar;
    class JobSelectorActions *m_jobSelectorActions;
    class JobListWidget *m_jobListWidget;
    class JobPropertiesWidget *m_jobProperties;
    JobModel *m_jobModel;
};

#endif
