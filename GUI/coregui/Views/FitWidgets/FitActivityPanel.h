// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitActivityPanel.h
//! @brief     Declares class FitActivityPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITACTIVITYPANEL_H
#define FITACTIVITYPANEL_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QMap>

class QPushButton;
class QSlider;
class JobModel;
class JobItem;
class QStackedWidget;
class FitSuiteWidget;

//! Main widget to run fitting. Occupies bottom right corner of JobView.
//! Contains stack of FitSuiteWidgets for JobItem's suitable for fitting.

class BA_CORE_API_ FitActivityPanel : public QWidget
{
    Q_OBJECT
public:
    FitActivityPanel(JobModel *jobModel, QWidget *parent = 0);

public slots:
    void setItem(JobItem *item);
    void onJobItemDelete(JobItem *item);
    void onJobItemFinished(const QString &identifier);
    void updateCurrentItem();

private:
    void setJobModel(JobModel *jobModel);
    QWidget *createRunControlWidget();
    bool isValidJobItem(JobItem *item);

    QPushButton *m_startButton;
    QPushButton *m_stopButton;
    QSlider *m_intervalSlider;
    JobModel *m_jobModel;
    JobItem *m_currentItem;
    QStackedWidget *m_stack;
    QMap<JobItem *, FitSuiteWidget *> m_jobItemToFitWidget;
};

#endif
