// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSessionWidget.cpp
//! @brief     Implements class FitSessionWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitSessionWidget.h"
#include "FitParameterWidget.h"
#include "FitResultsWidget.h"
#include "JobItem.h"
#include "MinimizerSettingsWidget.h"
#include "mainwindow_constants.h"
#include "FitSuiteManager.h"
#include "RunFitControlWidget.h"
#include <QTabWidget>
#include <QVBoxLayout>

FitSessionWidget::FitSessionWidget(QWidget* parent)
    : QWidget(parent)
    , m_tabWidget(new QTabWidget)
    , m_controlWidget(new RunFitControlWidget)
    , m_fitParametersWidget(new FitParameterWidget)
    , m_minimizerSettingsWidget(new MinimizerSettingsWidget)
    , m_fitResultsWidget(new FitResultsWidget)
    , m_fitSuiteManager(nullptr)
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
}

void FitSessionWidget::setItem(JobItem* jobItem)
{
    Q_ASSERT(jobItem);
    m_fitParametersWidget->setItem(jobItem);
    m_minimizerSettingsWidget->setItem(jobItem);
//    m_fitSuiteManager->setItem(jobItem);
    m_controlWidget->setItem(jobItem);
}

void FitSessionWidget::setModelTuningWidget(ParameterTuningWidget* tuningWidget)
{
    Q_ASSERT(m_fitParametersWidget);
    Q_ASSERT(tuningWidget);
    m_fitParametersWidget->setParameterTuningWidget(tuningWidget);
}

void FitSessionWidget::setFitSuiteManager(FitSuiteManager* fitSuiteManager)
{
    if (m_fitSuiteManager) {
        disconnect(m_fitSuiteManager, &FitSuiteManager::fittingError,
                   this, &FitSessionWidget::onFittingError);
        disconnect(m_controlWidget, &RunFitControlWidget::startFittingPushed,
                m_fitSuiteManager, &FitSuiteManager::onStartFittingRequest);
        disconnect(m_controlWidget, &RunFitControlWidget::stopFittingPushed,
                m_fitSuiteManager, &FitSuiteManager::onStopFittingRequest);
    }

    m_fitSuiteManager = fitSuiteManager;

    if (m_fitSuiteManager) {
        connect(m_fitSuiteManager, &FitSuiteManager::fittingError,
                this, &FitSessionWidget::onFittingError);
        connect(m_controlWidget, &RunFitControlWidget::startFittingPushed,
                m_fitSuiteManager, &FitSuiteManager::onStartFittingRequest);
        connect(m_controlWidget, &RunFitControlWidget::stopFittingPushed,
                m_fitSuiteManager, &FitSuiteManager::onStopFittingRequest);
    }
}

QSize FitSessionWidget::sizeHint() const
{
    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, Constants::FIT_SUITE_WIDGET_HEIGHT);
}

QSize FitSessionWidget::minimumSizeHint() const
{
    return QSize(25, 25);
}

void FitSessionWidget::onFittingError(const QString& text)
{
    m_controlWidget->onFittingError(text);
}

