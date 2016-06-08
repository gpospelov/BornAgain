// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitSuiteWidget.cpp
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
#include <QVBoxLayout>
#include <QTabWidget>
#include <QMessageBox>
#include <QDebug>

FitSuiteWidget::FitSuiteWidget(QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(new QTabWidget)
    , m_fitParametersWidget(new FitParameterWidget(this))
    , m_minimizerSettingsWidget(new MinimizerSettingsWidget(this))
    , m_fitResultsWidget(new FitResultsWidget(this))
    , m_currentItem(0)
    , m_manager(new RunFitManager(parent))
    , m_observer(new GUIFitObserver())
{
    QVBoxLayout *layout = new QVBoxLayout;

    m_tabWidget->addTab(m_fitParametersWidget, "Fit Parameters");
    m_tabWidget->addTab(m_minimizerSettingsWidget, "Minimizer");
    m_tabWidget->addTab(m_fitResultsWidget, "Fit Results");

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
}

void FitSuiteWidget::setModelTuningWidget(ParameterTuningWidget *tuningWidget)
{
    Q_ASSERT(m_fitParametersWidget);
    Q_ASSERT(tuningWidget);
    m_fitParametersWidget->setParameterTuningWidget(tuningWidget);
}

void FitSuiteWidget::onError(const QString &text)
{
    qDebug() << "FitSuiteWidget::onError" << text;
}

void FitSuiteWidget::onUpdatePlots(OutputData<double> *sim, OutputData<double> *chi2)
{
    Q_UNUSED(sim);
    Q_UNUSED(chi2);
    // FIXME Ownership sim,chi2 - shouldn't they be deleted here?

    qDebug() << "FitSuiteWidget::onUpdatePlots";
    OutputData<double> *data = m_currentItem->getIntensityDataItem()->getOutputData();
    data->setRawDataVector(sim->getRawDataVector());
    m_currentItem->getIntensityDataItem()->emitDataChanged();
    m_observer->finishedPlotting();
}

//! Propagates current values of fit parameters back to FitParameterItem and ParameterItem
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

void FitSuiteWidget::onUpdateStatus(const QString &text)
{
    Q_ASSERT(m_currentItem);
    qDebug() << "FitSuiteWidget::onUpdateStatus(const QString &text)" << text;
    FitSuiteItem *fitSuiteItem = m_currentItem->fitSuiteItem();
    Q_ASSERT(fitSuiteItem);
    bool ok;
    int niter = text.toInt(&ok);
    fitSuiteItem->setItemValue(FitSuiteItem::P_ITERATION_COUNT, niter);
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
        m_manager->setFitSuite(fitSuite);
        m_observer->finishedPlotting();
        m_manager->runFitting();
        qDebug() << " done";
    } catch(std::exception& e) {
//        QMessageBox box;
//        box.setText(e.what());
//        box.exec();
        emit fittingError(QString::fromStdString(e.what()));
    }


}

void FitSuiteWidget::stopFitting()
{
//    if(!m_currentItem)
//        return;
    qDebug() << "FitSuiteWidget::stopFitting()";
    m_manager->interruptFitting();
}

void FitSuiteWidget::onFittingStarted()
{
    qDebug() << "FitSuiteWidget::onFittingStarted()";
    emit fittingStarted();
}

void FitSuiteWidget::onFittingFinished()
{
    qDebug() << "FitSuiteWidget::onFittingFinished()";
    m_currentItem->fitSuiteItem()->mapper()->unsubscribe(this);
    emit fittingFinished();
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
    connect(m_manager, SIGNAL(startedFitting()), this, SLOT(onFittingStarted()));
    connect(m_manager, SIGNAL(finishedFitting()), this, SLOT(onFittingFinished()));

//    connect(m_manager, SIGNAL(error(QString)), this, SLOT(onError(QString)));
    connect(m_manager, SIGNAL(error(QString)), this, SIGNAL(fittingError(QString)));

    connect(m_observer.get(), SIGNAL(updatePlots(OutputData<double>*,OutputData<double>*)),
            this, SLOT(onUpdatePlots(OutputData<double>*,OutputData<double>*)));
    connect(m_observer.get(), SIGNAL(updateParameters(QStringList,QVector<double>)),
            this, SLOT(onUpdateParameters(QStringList,QVector<double>)));
    connect(m_observer.get(), SIGNAL(updateStatus(QString)),
            this, SLOT(onUpdateStatus(QString)));
}

