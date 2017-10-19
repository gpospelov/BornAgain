// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSuiteManager.cpp
//! @brief     Implements class FitSuiteManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitSuiteManager.h"
#include "RunFitManager.h"
#include "GUIFitObserver.h"
#include "JobItem.h"
#include "FitSuiteItem.h"
#include "DomainFittingBuilder.h"
#include "FitSuite.h"
#include "IntensityDataItem.h"
#include "FitParameterItems.h"
#include "GUIHelpers.h"
#include "FitLog.h"

FitSuiteManager::FitSuiteManager(QObject* parent)
    : QObject(parent)
    , m_jobItem(nullptr)
    , m_runFitManager(new FitWorkerLauncher(this))
    , m_observer(new GUIFitObserver)
    , m_fitlog(new FitLog)
    , m_block_progress_update(false)
{
    connect(m_observer.get(), &GUIFitObserver::plotsUpdate, this, &FitSuiteManager::onPlotsUpdate);

    connect(m_observer.get(), &GUIFitObserver::progressInfoUpdate, this,
            &FitSuiteManager::onProgressInfoUpdate);

    connect(m_observer.get(), &GUIFitObserver::logInfoUpdate, [&](const QString& text) {
        m_fitlog->append(text.toStdString(), FitLogFlags::DEFAULT);
    });

    connect(m_runFitManager, &FitWorkerLauncher::fittingStarted, this,
            &FitSuiteManager::onFittingStarted);
    connect(m_runFitManager, &FitWorkerLauncher::fittingFinished, this,
            &FitSuiteManager::onFittingFinished);
    connect(m_runFitManager, &FitWorkerLauncher::fittingError, this, &FitSuiteManager::onFittingError);
}

FitSuiteManager::~FitSuiteManager()
{
    if (m_jobItem)
        m_jobItem->mapper()->unsubscribe(this);
}

void FitSuiteManager::setItem(JobItem* item)
{
    if (m_jobItem && m_jobItem != item)
        throw GUIHelpers::Error("FitSuiteManager::setItem() -> Item was already set.");

    m_jobItem = item;
    Q_ASSERT(m_jobItem);

    m_jobItem->mapper()->setOnItemDestroy([this](SessionItem*) {m_jobItem = 0;}, this);

    // Propagates update interval from FitSuiteItem to fit observer.
    m_jobItem->fitSuiteItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == FitSuiteItem::P_UPDATE_INTERVAL) {
                m_observer->setInterval(m_jobItem->fitSuiteItem()
                                            ->getItemValue(FitSuiteItem::P_UPDATE_INTERVAL)
                                            .toInt());
            }
        },
        this);

}

void FitSuiteManager::onStartFittingRequest()
{
    if (!m_jobItem)
        return;

    try {
        m_observer->setInterval(
            m_jobItem->fitSuiteItem()->getItemValue(FitSuiteItem::P_UPDATE_INTERVAL).toInt());
        std::shared_ptr<FitSuite> fitSuite(DomainFittingBuilder::createFitSuite(m_jobItem));
        fitSuite->attachObserver(m_observer);
        m_observer->finishedPlotting();
        m_runFitManager->runFitting(fitSuite);
    } catch (std::exception& e) {
        m_jobItem->setStatus(Constants::STATUS_FAILED);
        m_fitlog->append(e.what(), FitLogFlags::ERROR);
        emit fittingError(QString::fromStdString(e.what()));
    }
}

FitLog* FitSuiteManager::fitLog()
{
    return m_fitlog.get();
}

void FitSuiteManager::onStopFittingRequest()
{
    m_runFitManager->interruptFitting();
}

void FitSuiteManager::onPlotsUpdate()
{
    m_jobItem->intensityDataItem()->setRawDataVector(m_observer->simulationData());
    m_observer->finishedPlotting();
}

void FitSuiteManager::onFittingStarted()
{
    m_fitlog->clearLog();

    m_jobItem->setStatus(Constants::STATUS_FITTING);
    m_jobItem->setProgress(0);
    m_jobItem->setBeginTime(GUIHelpers::currentDateTime());
    m_jobItem->setEndTime(QString());
    m_jobItem->setDuration(0);

    emit fittingStarted();
}

void FitSuiteManager::onFittingFinished()
{
    if (m_jobItem->getStatus() != Constants::STATUS_FAILED)
        m_jobItem->setStatus(Constants::STATUS_COMPLETED);
    m_jobItem->setEndTime(GUIHelpers::currentDateTime());
    m_jobItem->setProgress(100);
    m_jobItem->setDuration(m_runFitManager->getDuration());

    if (m_jobItem->isCompleted())
        m_fitlog->append("Done", FitLogFlags::SUCCESS);

    emit fittingFinished();
}

void FitSuiteManager::onFittingError(const QString& text)
{
    QString message;
    message.append("Current settings cause fitting failure.\n\n");
    message.append(text);
    m_fitlog->append(message.toStdString(), FitLogFlags::ERROR);

    emit fittingError(message);
}

//! Propagates fit progress as reported by GUIFitObserver back to JobItem.

void FitSuiteManager::onProgressInfoUpdate(const FitProgressInfo& info)
{
    if (m_block_progress_update)
        return;

    m_block_progress_update = true;

    updateIterationCount(info);
    updateFitParameterValues(info);
    updateLog(info);

    m_block_progress_update = false;
}

void FitSuiteManager::updateIterationCount(const FitProgressInfo& info)
{
    FitSuiteItem* fitSuiteItem = m_jobItem->fitSuiteItem();
    fitSuiteItem->setItemValue(FitSuiteItem::P_ITERATION_COUNT, info.iterationCount());
    fitSuiteItem->setItemValue(FitSuiteItem::P_CHI2, info.chi2());
}

void FitSuiteManager::updateFitParameterValues(const FitProgressInfo& info)
{
    QVector<double> values = info.parValues();
    FitParameterContainerItem* fitParContainer = m_jobItem->fitParameterContainerItem();
    fitParContainer->setValuesInParameterContainer(values, m_jobItem->parameterContainerItem());
}

void FitSuiteManager::updateLog(const FitProgressInfo& info)
{
    QString message = QString("NCalls:%1 chi2:%2 \n").arg(info.iterationCount()).arg(info.chi2());
    FitParameterContainerItem* fitParContainer = m_jobItem->fitParameterContainerItem();
    int index(0);
    QVector<double> values = info.parValues();
    foreach (SessionItem* item,
             fitParContainer->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        if (item->getItems(FitParameterItem::T_LINK).size() == 0)
            continue;
        QString parinfo = QString("      %1 %2\n").arg(item->displayName()).arg(values[index++]);
        message.append(parinfo);
    }

    m_fitlog->append(message.toStdString(), FitLogFlags::DEFAULT);
}
