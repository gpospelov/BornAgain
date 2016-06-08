// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobOutputDataWidget.cpp
//! @brief     Implements class JobOutputDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobOutputDataWidget.h"
#include "JobModel.h"
#include "JobItem.h"
#include "IntensityDataWidget.h"
#include "JobOutputDataToolBar.h"
#include "JobView.h"
#include "JobViewActivities.h"
#include "AppSvc.h"
#include "projectmanager.h"
#include "JobViewFlags.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QStandardPaths>
#include <QDebug>
#include "GUIHelpers.h"

JobOutputDataWidget::JobOutputDataWidget(JobModel *jobModel, QWidget *parent)
    : QWidget(parent)
    , m_stackedWidget(new ItemStackPresenter<IntensityDataWidget>)
    , m_toolBar(new JobOutputDataToolBar)
{
    setWindowTitle(QLatin1String("Job OutputData"));

    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_stackedWidget);

    m_stackedWidget->setMinimumSize(600, 600);
    m_stackedWidget->setModel(jobModel);

    setLayout(mainLayout);

    connectSignals();
}


void JobOutputDataWidget::setItem(JobItem * jobItem)
{
    if(!isValidJobItem(jobItem)) {
        m_stackedWidget->hideWidgets();
        return;
    }

    bool isNew(false);
    m_stackedWidget->setItem(jobItem, isNew);

    if(isNew) {
        IntensityDataWidget *widget = m_stackedWidget->currentWidget();
        Q_ASSERT(widget);
        widget->setItem(jobItem->getIntensityDataItem());
        connect(widget, SIGNAL(savePlotRequest()), this, SLOT(onSavePlot()));
    }

}

void JobOutputDataWidget::togglePropertyPanel()
{
    IntensityDataWidget *widget = currentOutputDataWidget();
    if(widget) widget->togglePropertyPanel();
}

void JobOutputDataWidget::toggleProjections()
{
    IntensityDataWidget *widget = currentOutputDataWidget();
    if(widget) widget->toggleProjections();
}

void JobOutputDataWidget::onResetView()
{
    IntensityDataWidget *widget = currentOutputDataWidget();
    if(widget) widget->onResetView();
}

void JobOutputDataWidget::onSavePlot()
{
    IntensityDataWidget *widget = currentOutputDataWidget();
    if(widget) widget->savePlot(AppSvc::projectManager()->userExportDir());
}

void JobOutputDataWidget::onActivityChanged(int activity)
{
    if(activity == JobViewFlags::REAL_TIME_ACTIVITY) {
        IntensityDataWidget *widget = currentOutputDataWidget();
        if(widget) {
            widget->setPropertyPanelVisible(false);
        }
    }
}

bool JobOutputDataWidget::isValidJobItem(JobItem *item)
{
    if(!item) return false;
    if(item->isCompleted() || item->isCanceled()) return true;
    return false;
}

void JobOutputDataWidget::connectSignals()
{
    connect(m_toolBar, SIGNAL(togglePropertyPanel()), this, SLOT(togglePropertyPanel()));
    connect(m_toolBar, SIGNAL(toggleProjections()), this, SLOT(toggleProjections()));
    connect(m_toolBar, SIGNAL(resetView()), this, SLOT(onResetView()));
    connect(m_toolBar, SIGNAL(savePlot()), this, SLOT(onSavePlot()));
}

IntensityDataWidget *JobOutputDataWidget::currentOutputDataWidget()
{
    return m_stackedWidget->currentWidget();
}

