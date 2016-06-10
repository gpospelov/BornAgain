// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitActivityPanel.h
//! @brief     Implements class FitActivityPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitActivityPanel.h"
#include "JobModel.h"
#include "JobItem.h"
#include "FitSuiteWidget.h"
#include "JobRealTimeWidget.h"
#include "mainwindow_constants.h"
#include "RunFitControlWidget.h"
#include <QVBoxLayout>
#include <QPushButton>

FitActivityPanel::FitActivityPanel(JobModel *jobModel, QWidget *parent)
    : QWidget(parent)
    , m_stackedWidget(new ItemStackPresenter<FitSuiteWidget>)
    , m_controlWidget(new RunFitControlWidget)
    , m_realTimeWidget(0)
{
    setWindowTitle(Constants::JobFitPanelName);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_stackedWidget);
    mainLayout->addWidget(m_controlWidget);

    setLayout(mainLayout);

    connect(m_controlWidget, SIGNAL(startFitting()), this, SLOT(onStartFitting()));
    connect(m_controlWidget, SIGNAL(stopFitting()), this, SLOT(onStopFitting()));

    m_stackedWidget->setModel(jobModel);
}

void FitActivityPanel::setRealTimeWidget(JobRealTimeWidget *realTimeWidget)
{
    Q_ASSERT(realTimeWidget);
    m_realTimeWidget = realTimeWidget;
}

QSize FitActivityPanel::sizeHint() const {
    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, Constants::FIT_ACTIVITY_PANEL_HEIGHT);
}

QSize FitActivityPanel::minimumSizeHint() const {
    return QSize(80, 80);
}

void FitActivityPanel::setItem(JobItem *item)
{
    m_controlWidget->setItem(item);

    if(!isValidJobItem(item)) {
        m_stackedWidget->hideWidgets();
        return;
    }

    bool isNew(false);
    m_stackedWidget->setItem(item, isNew);

    if(isNew) {
        FitSuiteWidget *widget = m_stackedWidget->currentWidget();
        Q_ASSERT(widget);
        widget->setItem(item);
        widget->setModelTuningWidget(m_realTimeWidget->parameterTuningWidget(item));
        connect(widget, SIGNAL(fittingStarted(JobItem *)), m_controlWidget,
                SLOT(onFittingStarted(JobItem *)), Qt::UniqueConnection);
        connect(widget, SIGNAL(fittingFinished(JobItem *)), m_controlWidget,
                SLOT(onFittingFinished(JobItem *)), Qt::UniqueConnection);
        connect(widget, SIGNAL(fittingError(QString)), m_controlWidget,
                SLOT(onFittingError(QString)), Qt::UniqueConnection);
    }
}

void FitActivityPanel::onStartFitting()
{
    if(FitSuiteWidget *widget = currentFitSuiteWidget())
        widget->startFitting();
}

void FitActivityPanel::onStopFitting()
{
    if(FitSuiteWidget *widget = currentFitSuiteWidget())
        widget->stopFitting();
}

bool FitActivityPanel::isValidJobItem(JobItem *item)
{
    if(!item) return false;
    return item->isValidForFitting();
}

FitSuiteWidget *FitActivityPanel::currentFitSuiteWidget()
{
    return m_stackedWidget->currentWidget();
}
