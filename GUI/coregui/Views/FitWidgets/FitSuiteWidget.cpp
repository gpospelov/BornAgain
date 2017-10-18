// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSuiteWidget.cpp
//! @brief     Implements class FitSuiteWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitSuiteWidget.h"
#include "FitParameterWidget.h"
#include "FitResultsWidget.h"
#include "JobItem.h"
#include "MinimizerSettingsWidget.h"
#include "mainwindow_constants.h"
#include "FitSuiteManager.h"
#include "RunFitControlWidget.h"
#include "FitLog.h"
#include <QTabWidget>
#include <QVBoxLayout>

FitSuiteWidget::FitSuiteWidget(QWidget* parent)
    : QWidget(parent)
    , m_tabWidget(new QTabWidget)
    , m_controlWidget(new RunFitControlWidget)
    , m_fitParametersWidget(new FitParameterWidget)
    , m_minimizerSettingsWidget(new MinimizerSettingsWidget)
    , m_fitResultsWidget(new FitResultsWidget)
    , m_fitSuiteManager(new FitSuiteManager(this))
{
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_tabWidget->addTab(m_fitParametersWidget, "Fit Parameters");
    m_tabWidget->addTab(m_minimizerSettingsWidget, "Minimizer");
    // m_tabWidget->addTab(m_fitResultsWidget, "Fit Results");

    layout->addWidget(m_tabWidget);
    layout->addWidget(m_controlWidget);

    setLayout(layout);
    connectSignals();
}

void FitSuiteWidget::setItem(JobItem* jobItem)
{
    Q_ASSERT(jobItem);
    m_fitParametersWidget->setItem(jobItem);
    m_minimizerSettingsWidget->setItem(jobItem);
    m_fitSuiteManager->setItem(jobItem);
    m_controlWidget->setItem(jobItem);
}

void FitSuiteWidget::setModelTuningWidget(ParameterTuningWidget* tuningWidget)
{
    Q_ASSERT(m_fitParametersWidget);
    Q_ASSERT(tuningWidget);
    m_fitParametersWidget->setParameterTuningWidget(tuningWidget);
}

void FitSuiteWidget::setJobMessagePanel(JobMessagePanel* jobMessagePanel)
{
    m_fitSuiteManager->fitLog()->setMessagePanel(jobMessagePanel);
}

QSize FitSuiteWidget::sizeHint() const
{
    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, Constants::FIT_SUITE_WIDGET_HEIGHT);
}

QSize FitSuiteWidget::minimumSizeHint() const
{
    return QSize(25, 25);
}

void FitSuiteWidget::onFittingError(const QString& text)
{
    m_controlWidget->onFittingError(text);
}

void FitSuiteWidget::connectSignals()
{
    connect(m_controlWidget, &RunFitControlWidget::startFittingPushed,
            m_fitSuiteManager, &FitSuiteManager::onStartFittingRequest);
    connect(m_controlWidget, &RunFitControlWidget::stopFittingPushed,
            m_fitSuiteManager, &FitSuiteManager::onStopFittingRequest);
    connect(m_fitSuiteManager, &FitSuiteManager::fittingError,
            this, &FitSuiteWidget::onFittingError);
}
