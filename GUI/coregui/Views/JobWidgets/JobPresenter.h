// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobPresenter.h
//! @brief     Declares class JobPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBPRESENTER_H
#define JOBPRESENTER_H

#include "WinDllMacros.h"
#include <QWidget>

class JobModel;
class JobItem;

//! The JobPresenter class is the base for all widgets presenting JobItem (JobRealTimeWidget,
//! JobOutputDataWidget, FitActivityPanel). Contains common methods to react on JobItem change.

class BA_CORE_API_ JobPresenter : public QWidget
{
    Q_OBJECT

public:
    JobPresenter(JobModel *jobModel, QWidget *parent = 0);

public slots:
    virtual void setJobModel(JobModel *jobModel);
    virtual void setItem(JobItem *item);
    virtual void onJobItemDelete(JobItem *item);
    virtual void onJobItemFinished(const QString &identifier);
    virtual void updateCurrentItem();
    virtual void onActivityChange(int nactivity);
    virtual void onModelLoaded();

protected:
    virtual bool isValidJobItem(JobItem *item);

    JobModel *m_jobModel;
    JobItem *m_currentItem;
};

#endif
