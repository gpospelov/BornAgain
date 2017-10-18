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
#include "DomainFittingBuilder.h"
#include "FitParameterItems.h"
#include "FitParameterWidget.h"
#include "FitProgressInfo.h"
#include "FitResultsWidget.h"
#include "FitSuite.h"
#include "FitSuiteItem.h"
#include "GUIFitObserver.h"
#include "GUIHelpers.h"
#include "IntensityDataItem.h"
#include "JobItem.h"
#include "JobModel.h"
#include "MinimizerSettingsWidget.h"
#include "ModelPath.h"
#include "ParameterTreeItems.h"
#include "RunFitManager.h"
#include "mainwindow_constants.h"
#include "FitSuiteManager.h"
#include "RunFitControlWidget.h"
#include "JobMessagePanel.h"
#include <QMessageBox>
#include <QTabWidget>
#include <QVBoxLayout>

FitSuiteWidget::FitSuiteWidget(QWidget *parent)
    : QWidget(parent)
    , m_controlWidget(new RunFitControlWidget)
    , m_tabWidget(new QTabWidget)
    , m_fitParametersWidget(new FitParameterWidget)
    , m_minimizerSettingsWidget(new MinimizerSettingsWidget)
    , m_fitResultsWidget(new FitResultsWidget)
    , m_currentItem(0)
    , m_jobMessagePanel(nullptr)
    , m_fitSuiteManager(new FitSuiteManager(this))
    , m_block_progress_update(false)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setMargin(0);
    layout->setSpacing(0);

//    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    m_tabWidget->setMinimumSize(25, 25);
//    m_tabWidget->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    m_tabWidget->addTab(m_fitParametersWidget, "Fit Parameters");
    m_tabWidget->addTab(m_minimizerSettingsWidget, "Minimizer");
    //m_tabWidget->addTab(m_fitResultsWidget, "Fit Results");

    layout->addWidget(m_tabWidget);
    layout->addWidget(m_controlWidget);

    setLayout(layout);
    connectSignals();
}

FitSuiteWidget::~FitSuiteWidget()
{

}

void FitSuiteWidget::setItem(JobItem *jobItem)
{
    Q_ASSERT(jobItem);
    m_currentItem = jobItem;
    m_fitParametersWidget->setItem(jobItem);
    m_minimizerSettingsWidget->setItem(jobItem);
    m_fitSuiteManager->setItem(jobItem);
    m_controlWidget->setItem(jobItem);
}

void FitSuiteWidget::setModelTuningWidget(ParameterTuningWidget *tuningWidget)
{
    Q_ASSERT(m_fitParametersWidget);
    Q_ASSERT(tuningWidget);
    m_fitParametersWidget->setParameterTuningWidget(tuningWidget);
}

void FitSuiteWidget::setJobMessagePanel(JobMessagePanel* jobMessagePanel)
{
    m_jobMessagePanel = jobMessagePanel;
}

QSize FitSuiteWidget::sizeHint() const
{
    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, Constants::FIT_SUITE_WIDGET_HEIGHT);
}

QSize FitSuiteWidget::minimumSizeHint() const
{
    return QSize(25, 25);
}

//! Propagates fit progress as reported by GUIFitObserver back to JobItem.

void FitSuiteWidget::onProgressInfoUpdate(const FitProgressInfo &info)
{
    if(m_block_progress_update) return;

    m_block_progress_update = true;

    updateIterationCount(info);
    updateTuningWidgetParameterValues(info);
    updateLog(info);

    m_block_progress_update = false;
}


void FitSuiteWidget::onFittingStarted()
{
    m_jobMessagePanel->onClearLog();
}

void FitSuiteWidget::onFittingFinished()
{

    if(m_currentItem->isCompleted())
        m_jobMessagePanel->onMessage(QStringLiteral("Done"), QColor(Qt::darkBlue));
}

void FitSuiteWidget::onFittingLogUpdate(const QString& text)
{
    m_jobMessagePanel->onMessage(text);
}

void FitSuiteWidget::onFittingError(const QString& text)
{
    QString message;
    message.append("Current settings cause fitting failure.\n\n");
    message.append(text);
    m_jobMessagePanel->onMessage(message, QColor(Qt::darkRed));

    m_controlWidget->onFittingError(message);
}

void FitSuiteWidget::connectSignals()
{
    connect(m_controlWidget, SIGNAL(startFittingPushed()), m_fitSuiteManager, SLOT(onStartFittingRequest()));
    connect(m_controlWidget, SIGNAL(stopFittingPushed()), m_fitSuiteManager, SLOT(onStopFittingRequest()));

    connect(m_fitSuiteManager, SIGNAL(fittingStarted()), this, SLOT(onFittingStarted()));
    connect(m_fitSuiteManager, SIGNAL(fittingFinished()), this, SLOT(onFittingFinished()));

    connect(m_fitSuiteManager, SIGNAL(fittingError(QString)),
            this, SLOT(onFittingError(QString)));

    connect(m_fitSuiteManager->fitObserver().get(), SIGNAL(logInfoUpdate(QString)),
            this, SLOT(onFittingLogUpdate(QString)));

    connect(m_fitSuiteManager->fitObserver().get(), SIGNAL(progressInfoUpdate(const FitProgressInfo&)),
            this, SLOT(onProgressInfoUpdate(const FitProgressInfo&)));

}

//! Propagates current number of iteration to FitSuiteItem to make FitControlWidget informed.

void FitSuiteWidget::updateIterationCount(const FitProgressInfo &info)
{
    FitSuiteItem *fitSuiteItem = m_currentItem->fitSuiteItem();
    fitSuiteItem->setItemValue(FitSuiteItem::P_ITERATION_COUNT, info.iterationCount());
    fitSuiteItem->setItemValue(FitSuiteItem::P_CHI2, info.chi2());
}

void FitSuiteWidget::updateTuningWidgetParameterValues(const FitProgressInfo &info)
{
    QVector<double> values = info.parValues();
    FitParameterContainerItem *fitParContainer = m_currentItem->fitParameterContainerItem();
    fitParContainer->setValuesInParameterContainer(values, m_currentItem->parameterContainerItem());
}

// FIXME provide normal print on log update

void FitSuiteWidget::updateLog(const FitProgressInfo &info)
{
    QString message = QString("NCalls:%1 chi2:%2 \n").arg(info.iterationCount()).arg(info.chi2());
    FitParameterContainerItem *fitParContainer = m_currentItem->fitParameterContainerItem();
    int index(0);
    QVector<double> values = info.parValues();
    foreach(SessionItem *item,
            fitParContainer->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        if(item->getItems(FitParameterItem::T_LINK).size()==0)
            continue;
        QString parinfo = QString("      %1 %2\n").arg(item->displayName()).arg(values[index++]);
        message.append(parinfo);
    }

//    message.append("\n");
    m_jobMessagePanel->onMessage(message);
}

