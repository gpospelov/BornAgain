// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitActivityPanel.cpp
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
#include "FitSuiteWidget.h"
#include "JobItem.h"
#include "JobMessagePanel.h"
#include "JobModel.h"
#include "JobRealTimeWidget.h"
#include "RunFitControlWidget.h"
#include "mainwindow_constants.h"
#include "FitActivityManager.h"
#include <QPushButton>
#include <QVBoxLayout>

FitActivityPanel::FitActivityPanel(JobModel *jobModel, QWidget *parent)
    : QWidget(parent)
    , m_stackedWidget(new ItemStackPresenter<FitSuiteWidget>)
    , m_realTimeWidget(0)
    , m_jobMessagePanel(0)
    , m_fitActivityManager(new FitActivityManager(this))
{
    setWindowTitle(Constants::JobFitPanelName);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_stackedWidget);

    setLayout(mainLayout);

    m_stackedWidget->setModel(jobModel);
}

void FitActivityPanel::setRealTimeWidget(JobRealTimeWidget *realTimeWidget)
{
    Q_ASSERT(realTimeWidget);
    m_realTimeWidget = realTimeWidget;
}

void FitActivityPanel::setJobMessagePanel(JobMessagePanel *jobMessagePanel)
{
    m_jobMessagePanel = jobMessagePanel;
    m_fitActivityManager->setMessagePanel(m_jobMessagePanel);
}

QSize FitActivityPanel::sizeHint() const {
    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, Constants::FIT_ACTIVITY_PANEL_HEIGHT);
}

QSize FitActivityPanel::minimumSizeHint() const {
    return QSize(80, 80);
}

void FitActivityPanel::setItem(JobItem *item)
{

    if(!isValidJobItem(item)) {
        m_jobMessagePanel->onClearLog();
        m_stackedWidget->hideWidgets();
        return;
    }

    bool isNew(false);
    m_stackedWidget->setItem(item, &isNew);

    if(isNew) {
        FitSuiteWidget *widget = m_stackedWidget->currentWidget();
        Q_ASSERT(widget);
        widget->setItem(item);
        widget->setModelTuningWidget(m_realTimeWidget->parameterTuningWidget(item));
    }

    if (FitSuiteWidget* widget = m_stackedWidget->currentWidget())
        widget->setFitSuiteManager(m_fitActivityManager->manager(item));
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
