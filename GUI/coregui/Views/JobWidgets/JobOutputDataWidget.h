// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobOutputDataWidget.h
//! @brief     Declares class JobOutputDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBOUTPUTDATAWIDGET_H
#define JOBOUTPUTDATAWIDGET_H

#include "JobPresenter.h"
#include <QMap>

class IntensityDataWidget;
class QStackedWidget;
class JobOutputDataToolBar;
class JobModel;
class JobItem;

class BA_CORE_API_ JobOutputDataWidget : public JobPresenter
{
    Q_OBJECT
public:
    explicit JobOutputDataWidget(JobModel *jobModel, QWidget *parent = 0);

public slots:
    void setItem(JobItem *item);
    void onJobItemDelete(JobItem *item);
    void togglePropertyPanel();
    void toggleProjections();
    void onResetView();
    void onSavePlot();
    void onActivityChanged(int);

private:
    void connectSignals();
    IntensityDataWidget *getCurrentOutputDataWidget();

    QStackedWidget *m_stack;
    QMap<JobItem *, IntensityDataWidget *> m_jobItemToPlotWidget;
    JobOutputDataToolBar *m_toolBar;
};

#endif
