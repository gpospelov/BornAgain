// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/JobQueueWidgets/JobSelectorWidget.h
//! @brief     Implements class JobSelectorWidget
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef JOBSELECTORWIDGET_H
#define JOBSELECTORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class JobQueueModel;
class JobPropertiesWidget;
class QSplitter;
class QPushButton;
class JobListWidget;
class JobItem;


//! Widget to select JobQueueItem in a list and display its properties
//! Left side of JobQueueView
//! Contains two widgets: JobListWidget (top) and JobQueueProperties(buttom)
class BA_CORE_API_ JobSelectorWidget : public QWidget
{
public:
    explicit JobSelectorWidget(JobQueueModel *model, QWidget *parent = 0);

    void setModel(JobQueueModel *model);

    QSize sizeHint() const { return QSize(210, 600); }
    QSize minimumSizeHint() const { return QSize(64, 300); }

public slots:
    void makeJobItemSelected(JobItem *);

private:
    JobQueueModel *m_jobQueueModel;
    QSplitter *m_splitter;
    JobListWidget *m_jobListWidget;
    JobPropertiesWidget *m_jobProperties;

};




#endif
