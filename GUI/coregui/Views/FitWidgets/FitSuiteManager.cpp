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
#include "GUIHelpers.h"

FitSuiteManager::FitSuiteManager(QObject* parent)
    : QObject(parent)
    , m_runFitManager(new RunFitManager(this))
    , m_observer(new GUIFitObserver)
{
    connect(m_observer.get(), &GUIFitObserver::plotsUpdate, this, &FitSuiteManager::onPlotsUpdate);
    connect(m_runFitManager, &RunFitManager::fittingStarted,
            this, &FitSuiteManager::onFittingStarted);
    connect(m_runFitManager, &RunFitManager::fittingFinished,
            this, &FitSuiteManager::onFittingFinished);
    connect(m_runFitManager, &RunFitManager::fittingError,
            this, &FitSuiteManager::fittingError);
}

void FitSuiteManager::setItem(JobItem* item)
{
    m_jobItem = item;
}

void FitSuiteManager::onStartFittingRequest()
{
    if(!m_jobItem)
        return;

    m_jobItem->fitSuiteItem()->mapper()->setOnPropertyChange(
                [this](const QString &name)
    {
        // Propagates update interval from FitSuiteItem to fit observer.

        if(name == FitSuiteItem::P_UPDATE_INTERVAL) {
            m_observer->setInterval(m_jobItem->fitSuiteItem()->getItemValue(
                                        FitSuiteItem::P_UPDATE_INTERVAL).toInt());

        }

    }, this);


    try {
        m_observer->setInterval(m_jobItem->fitSuiteItem()->getItemValue(
                                    FitSuiteItem::P_UPDATE_INTERVAL).toInt());
        std::shared_ptr<FitSuite> fitSuite(DomainFittingBuilder::createFitSuite(m_jobItem));
        fitSuite->attachObserver(m_observer);
        m_observer->finishedPlotting();
        m_runFitManager->runFitting(fitSuite);
    } catch(std::exception& e) {
        m_jobItem->setStatus(Constants::STATUS_FAILED);
        m_jobItem->fitSuiteItem()->mapper()->unsubscribe(this);
        emit fittingError(QString::fromStdString(e.what()));
    }

}

RunFitManager* FitSuiteManager::runFitManager()
{
    return m_runFitManager;
}

std::shared_ptr<GUIFitObserver> FitSuiteManager::fitObserver()
{
    return m_observer;
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
    m_jobItem->setStatus(Constants::STATUS_FITTING);
    m_jobItem->setProgress(0);
    m_jobItem->setBeginTime(GUIHelpers::currentDateTime());
    m_jobItem->setEndTime(QString());
    m_jobItem->setDuration(0);

    emit fittingStarted();
}

void FitSuiteManager::onFittingFinished()
{
    if(m_jobItem->getStatus() != Constants::STATUS_FAILED)
        m_jobItem->setStatus(Constants::STATUS_COMPLETED);
    m_jobItem->setEndTime(GUIHelpers::currentDateTime());
    m_jobItem->setProgress(100);
    m_jobItem->setDuration(m_runFitManager->getDuration());
    m_jobItem->fitSuiteItem()->mapper()->unsubscribe(this);

    emit fittingFinished();
}
