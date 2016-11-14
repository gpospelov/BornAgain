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
#include <QDebug>
#include <QMessageBox>
#include <QTabWidget>
#include <QVBoxLayout>

FitSuiteWidget::FitSuiteWidget(QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(new QTabWidget)
    , m_fitParametersWidget(new FitParameterWidget)
    , m_minimizerSettingsWidget(new MinimizerSettingsWidget)
    , m_fitResultsWidget(new FitResultsWidget)
    , m_currentItem(0)
    , m_runFitManager(new RunFitManager(parent))
    , m_observer(new GUIFitObserver())
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
}

void FitSuiteWidget::setModelTuningWidget(ParameterTuningWidget *tuningWidget)
{
    Q_ASSERT(m_fitParametersWidget);
    Q_ASSERT(tuningWidget);
    m_fitParametersWidget->setParameterTuningWidget(tuningWidget);
}

QSize FitSuiteWidget::sizeHint() const
{
    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, Constants::FIT_SUITE_WIDGET_HEIGHT);
}

QSize FitSuiteWidget::minimumSizeHint() const
{
    return QSize(25, 25);
}

void FitSuiteWidget::onError(const QString &text)
{
    qDebug() << "FitSuiteWidget::onError" << text;
}

void FitSuiteWidget::onPlotsUpdate()
{
    qDebug() << "FitSuiteWidget::onPlotsUpdate";
    m_currentItem->intensityDataItem()->setRawDataVector(m_observer->simulationData());
    m_observer->finishedPlotting();
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

void FitSuiteWidget::startFitting()
{
    if(!m_currentItem)
        return;
    qDebug() << "FitSuiteWidget::startFitting()";

    m_currentItem->fitSuiteItem()->mapper()->setOnPropertyChange(
                [this](const QString &name)
    {
        onFitSuitePropertyChange(name);
    }, this);


    try {
        qDebug() << " try run fitting";
        m_observer->setInterval(m_currentItem->fitSuiteItem()->getItemValue(
                                    FitSuiteItem::P_UPDATE_INTERVAL).toInt());
        std::shared_ptr<FitSuite> fitSuite(DomainFittingBuilder::createFitSuite(m_currentItem));
        fitSuite->attachObserver(m_observer);
        m_runFitManager->setFitSuite(fitSuite);
        m_observer->finishedPlotting();
        m_runFitManager->runFitting();
        qDebug() << " done";
    } catch(std::exception& e) {
        m_currentItem->setStatus(Constants::STATUS_FAILED);
        m_currentItem->fitSuiteItem()->mapper()->unsubscribe(this);
        processFittingError(QString::fromStdString(e.what()));
        emit fittingError(QString::fromStdString(e.what()));
    }


}

void FitSuiteWidget::stopFitting()
{
//    if(!m_currentItem)
//        return;
    qDebug() << "FitSuiteWidget::stopFitting()";
    m_runFitManager->interruptFitting();
}

void FitSuiteWidget::onFittingStarted()
{
    m_currentItem->setStatus(Constants::STATUS_FITTING);
    m_currentItem->setProgress(0);
    m_currentItem->setBeginTime(GUIHelpers::currentDateTime());
    m_currentItem->setEndTime(QString());
    m_currentItem->setDuration(0);

    qDebug() << "FitSuiteWidget::onFittingStarted()";
    emit fittingStarted(m_currentItem);
}

void FitSuiteWidget::onFittingFinished()
{
    if(m_currentItem->getStatus() != Constants::STATUS_FAILED)
        m_currentItem->setStatus(Constants::STATUS_COMPLETED);
    m_currentItem->setEndTime(GUIHelpers::currentDateTime());
    m_currentItem->setProgress(100);
    m_currentItem->setDuration(m_runFitManager->getDuration());
    qDebug() << "FitSuiteWidget::onFittingFinished()";
    m_currentItem->fitSuiteItem()->mapper()->unsubscribe(this);
    emit fittingFinished(m_currentItem);
}

//! Propagates update interval from FitSuiteItem to fit observer.
void FitSuiteWidget::onFitSuitePropertyChange(const QString &name)
{
    if(name == FitSuiteItem::P_UPDATE_INTERVAL) {
        m_observer->setInterval(m_currentItem->fitSuiteItem()->getItemValue(
                                    FitSuiteItem::P_UPDATE_INTERVAL).toInt());

    }

}

void FitSuiteWidget::processFittingError(const QString &text)
{
    //m_currentItem->setStatus(Constants::STATUS_FITTING_FAILED);
    emit fittingError(text);
}

void FitSuiteWidget::connectSignals()
{
    connect(m_runFitManager, SIGNAL(startedFitting()), this, SLOT(onFittingStarted()));
    connect(m_runFitManager, SIGNAL(finishedFitting()), this, SLOT(onFittingFinished()));
    connect(m_runFitManager, SIGNAL(fittingError(QString)),
            this, SLOT(processFittingError(QString)));

    connect(m_observer.get(), SIGNAL(plotsUpdate()), this, SLOT(onPlotsUpdate()));


    connect(m_observer.get(), SIGNAL(logInfoUpdate(QString)),
            this, SIGNAL(fittingLog(QString)));


    connect(m_observer.get(), SIGNAL(progressInfoUpdate(const FitProgressInfo&)),
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
        QString parinfo = QString("      %1 %2\n").arg(item->displayName()).arg(values[index++]);
        message.append(parinfo);
    }

//    message.append("\n");
    emit fittingLog(message);
}

