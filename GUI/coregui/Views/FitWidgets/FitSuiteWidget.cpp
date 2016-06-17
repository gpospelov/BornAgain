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
#include "JobModel.h"
#include "JobItem.h"
#include "FitSuiteItem.h"
#include "FitParameterItems.h"
#include "FitParameterWidget.h"
#include "RunFitManager.h"
#include "GUIFitObserver.h"
#include "DomainFittingBuilder.h"
#include "IntensityDataItem.h"
#include "FitSuite.h"
#include "ModelPath.h"
#include "ParameterTreeItems.h"
#include "MinimizerSettingsWidget.h"
#include "FitResultsWidget.h"
#include "mainwindow_constants.h"
#include "FitProgressInfo.h"
#include "GUIHelpers.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <QMessageBox>
#include <QDebug>

FitSuiteWidget::FitSuiteWidget(QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(new QTabWidget)
    , m_fitParametersWidget(new FitParameterWidget)
    , m_minimizerSettingsWidget(new MinimizerSettingsWidget)
    , m_fitResultsWidget(new FitResultsWidget)
    , m_currentItem(0)
    , m_runFitManager(new RunFitManager(parent))
    , m_observer(new GUIFitObserver())
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
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
    qDebug() << "FitSuiteWidget::onUpdatePlots";
    m_currentItem->getIntensityDataItem()->setRawDataVector(m_observer->simulationData());
    m_observer->finishedPlotting();
}

//! Propagates current values of fit parameters as reported by FitSuite observer back to JobItem.

void FitSuiteWidget::onUpdateParameters(const QStringList &parameters, QVector<double> values)
{
    qDebug() << "FitSuiteWidget::onUpdateParameters" << parameters << values;

    ParameterContainerItem *parContainer = m_currentItem->parameterContainerItem();
    Q_ASSERT(parContainer);

    SessionItem *fitParContainer = m_currentItem->fitParameterContainerItem();
    Q_ASSERT(fitParContainer);

    foreach(SessionItem *fitParItem, fitParContainer->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        foreach(SessionItem *linkItem, fitParItem->getItems(FitParameterItem::T_LINK)) {
            QString domainPath = linkItem->getItemValue(FitParameterLinkItem::P_DOMAIN).toString();

            if (parameters.contains(domainPath)) {
                QString parPath = linkItem->getItemValue(FitParameterLinkItem::P_LINK).toString();
                int index = parameters.indexOf(domainPath);
                SessionItem *parItem = ModelPath::getItemFromPath(parPath, parContainer);
                Q_ASSERT(parItem);
                parItem->setValue(values[index]);
            }

        }
    }
}

void FitSuiteWidget::onStatusUpdate(const QString &text)
{
    Q_ASSERT(m_currentItem);
    qDebug() << "FitSuiteWidget::onUpdateStatus(const QString &text)" << text;
    FitSuiteItem *fitSuiteItem = m_currentItem->fitSuiteItem();
    Q_ASSERT(fitSuiteItem);
    bool ok;
    int niter = text.toInt(&ok);
    fitSuiteItem->setItemValue(FitSuiteItem::P_ITERATION_COUNT, niter);
}

void FitSuiteWidget::onProgressInfoUpdate(const FitProgressInfo &info)
{

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
        m_observer->setInterval(m_currentItem->fitSuiteItem()->getItemValue(FitSuiteItem::P_UPDATE_INTERVAL).toInt());
        std::shared_ptr<FitSuite> fitSuite(DomainFittingBuilder::createFitSuite(m_currentItem));
        fitSuite->attachObserver(m_observer);
        m_runFitManager->setFitSuite(fitSuite);
        m_observer->finishedPlotting();
        m_runFitManager->runFitting();
        qDebug() << " done";
    } catch(std::exception& e) {
        m_currentItem->fitSuiteItem()->mapper()->unsubscribe(this);
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
    qDebug() << "FitSuiteWidget::onFitSuitePropertyChange(const QString &name)" << name;
    if(name == FitSuiteItem::P_UPDATE_INTERVAL) {
        m_observer->setInterval(m_currentItem->fitSuiteItem()->getItemValue(FitSuiteItem::P_UPDATE_INTERVAL).toInt());

    }

}

void FitSuiteWidget::connectSignals()
{
    connect(m_runFitManager, SIGNAL(startedFitting()), this, SLOT(onFittingStarted()));
    connect(m_runFitManager, SIGNAL(finishedFitting()), this, SLOT(onFittingFinished()));
    connect(m_runFitManager, SIGNAL(fittingError(QString)), this, SIGNAL(fittingError(QString)));

    connect(m_observer.get(), SIGNAL(plotsUpdate()), this, SLOT(onPlotsUpdate()));

    connect(m_observer.get(), SIGNAL(parameterUpdate(QStringList,QVector<double>)),
            this, SLOT(onUpdateParameters(QStringList,QVector<double>)));

    connect(m_observer.get(), SIGNAL(statusUpdate(QString)), this, SLOT(onStatusUpdate(QString)));

    connect(m_observer.get(), SIGNAL(logInfoUpdate(QString)),
            this, SIGNAL(fittingLog(QString)));


    connect(m_observer.get(), SIGNAL(progressInfoUpdate(FitProgressInfo)),
            this, SLOT(onProgressInfoUpdate(QString)));

}

