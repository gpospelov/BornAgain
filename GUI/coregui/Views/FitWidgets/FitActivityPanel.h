// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitActivityPanel.h
//! @brief     Defines class FitActivityPanel
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

#include "ItemStackPresenter.h"
#include <QWidget>

class JobModel;
class JobItem;
class FitSuiteWidget;
class JobRealTimeWidget;
class RunFitControlWidget;
class JobMessagePanel;

//! The FitActivityPanel class is a main widget to run the fitting.
//! Occupies bottom right corner of JobView, contains stack of FitSuiteWidgets for every
//! JobItem which is suitable for fitting.

class BA_CORE_API_ FitActivityPanel : public QWidget
{
    Q_OBJECT
public:
    FitActivityPanel(JobModel *jobModel, QWidget *parent = 0);

    void setRealTimeWidget(JobRealTimeWidget *realTimeWidget);
    void setJobMessagePanel(JobMessagePanel *jobMessagePanel);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void setItem(JobItem *item);

private:
    bool isValidJobItem(JobItem *item);
    FitSuiteWidget *currentFitSuiteWidget();

    ItemStackPresenter<FitSuiteWidget> *m_stackedWidget;
    JobRealTimeWidget *m_realTimeWidget;
    JobMessagePanel *m_jobMessagePanel;
};

#endif // FITACTIVITYPANEL_H
