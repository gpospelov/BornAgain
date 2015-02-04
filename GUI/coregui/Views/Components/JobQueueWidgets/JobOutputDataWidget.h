// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/JobQueueWidgets/JobOutputDataWidget.h
//! @brief     Defines class JobOutputDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef JOBOUTPUTDATAWIDGET_H
#define JOBOUTPUTDATAWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QMap>

class OutputDataWidget;
//class JobQueueModel;
class QStackedWidget;
class QModelIndex;
//class JobItem;
class JobOutputDataToolBar;
class ProjectManager;
class NJobModel;
class NJobItem;

class BA_CORE_API_ JobOutputDataWidget : public QWidget
{
    Q_OBJECT
public:
//    explicit JobOutputDataWidget(JobQueueModel *jobQueueModel, ProjectManager *projectManager, QWidget *parent = 0);
    explicit JobOutputDataWidget(NJobModel *joModel, ProjectManager *projectManager, QWidget *parent = 0);

//    void setJobQueueModel(JobQueueModel *jobQueueModel);
    void setJobModel(NJobModel *jobModel);

    JobOutputDataToolBar *getToolBar() { return m_toolBar; }

signals:
    void jobViewActivityRequest(int activity);

public slots:
    void itemClicked(NJobItem *item);
    void onJobItemDelete(NJobItem *item);
    void onJobItemFinished(const QString &identifier);
    void togglePropertyPanel();
    void toggleProjections();
    void resetTriggered();
    void savePlot();
    void onActivityChanged(int);

private:
    void connectSignals();
    OutputDataWidget *getCurrentOutputDataWidget();

//    JobQueueModel *m_jobQueueModel;
    NJobModel *m_jobModel;
    ProjectManager *m_projectManager;
    NJobItem *m_currentJobItem;
    QStackedWidget *m_stack;
    QMap<NJobItem *, OutputDataWidget *> m_jobItemToPlotWidget;
    JobOutputDataToolBar *m_toolBar;
};


#endif
