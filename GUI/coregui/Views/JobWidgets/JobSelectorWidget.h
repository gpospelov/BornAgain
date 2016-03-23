// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobSelectorWidget.h
//! @brief     Implements class JobSelectorWidget
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
class JobPropertiesWidget;
class QSplitter;
class QPushButton;
class JobListWidget;

//! Widget to select JobQueueItem in a list and display its properties
//! Left side of JobQueueView
//! Contains two widgets: JobListWidget (top) and JobQueueProperties(buttom)
class BA_CORE_API_ JobSelectorWidget : public QWidget
{
public:
    explicit JobSelectorWidget(JobModel *model, QWidget *parent = 0);

    void setModel(JobModel *model);

    QSize sizeHint() const { return QSize(210, 600); }
    QSize minimumSizeHint() const { return QSize(64, 300); }

public slots:
    void makeJobItemSelected(JobItem *);

private:
    JobModel *m_jobModel;
    QSplitter *m_splitter;
    JobListWidget *m_jobListWidget;
    JobPropertiesWidget *m_jobProperties;
};




#endif
