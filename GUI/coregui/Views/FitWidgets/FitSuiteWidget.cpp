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
#include "FitParametersWidget.h"
#include "RunFitManager.h"
#include "GUIFitObserver.h"
#include "DomainFittingBuilder.h"
#include "IntensityDataItem.h"
#include "FitSuite.h"
#include "ModelPath.h"
#include "ParameterTreeItems.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <QMessageBox>
#include <QDebug>

FitSuiteWidget::FitSuiteWidget(JobModel *jobModel, QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(new QTabWidget)
    , m_fitParametersWidget(new FitParametersWidget(this))
    , m_jobModel(jobModel)
    , m_currentItem(0)
    , m_manager(new RunFitManager(parent))
    , m_observer(new GUIFitObserver())
{
    QVBoxLayout *layout = new QVBoxLayout;

    m_tabWidget->addTab(m_fitParametersWidget, "Fit Parameters");

    layout->addWidget(m_tabWidget);

    setLayout(layout);
    connectSignals();
}

FitSuiteWidget::~FitSuiteWidget()
{

}

void FitSuiteWidget::setItem(JobItem *jobItem)
{
    m_currentItem = jobItem;
    m_fitParametersWidget->setItem(jobItem);
}

void FitSuiteWidget::setModelTuningWidget(ModelTuningWidget *tuningWidget)
{
    Q_ASSERT(m_fitParametersWidget);
    Q_ASSERT(tuningWidget);
    m_fitParametersWidget->setModelTuningWidget(tuningWidget);
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
//    OutputData<double> *data = m_currentItem->getIntensityDataItem()->getOutputData();
//    data->setRawDataVector(sim->getRawDataVector());
//    m_currentItem->getIntensityDataItem()->emitDataChanged();
    m_observer->finishedPlotting();
}

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

    try {
        qDebug() << " try run fitting";
        std::shared_ptr<FitSuite> fitSuite(DomainFittingBuilder::getFitSuite(m_currentItem));
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
    if(!m_currentItem)
        return;
    qDebug() << "FitSuiteWidget::stopFitting()";
}

void FitSuiteWidget::connectSignals()
{
    connect(m_manager, SIGNAL(startedFitting()), this, SIGNAL(fittingStarted()));
    connect(m_manager, SIGNAL(finishedFitting()), this, SIGNAL(fittingFinished()));

//    connect(m_manager, SIGNAL(error(QString)), this, SLOT(onError(QString)));
    connect(m_manager, SIGNAL(error(QString)), this, SIGNAL(fittingError(QString)));

    connect(m_observer.get(), SIGNAL(updatePlots(OutputData<double>*,OutputData<double>*)),
            this, SLOT(onUpdatePlots(OutputData<double>*,OutputData<double>*)));
    connect(m_observer.get(), SIGNAL(updateParameters(QStringList,QVector<double>)),
            this, SLOT(onUpdateParameters(QStringList,QVector<double>)));
    connect(m_observer.get(), SIGNAL(updateStatus(QString)),
            this, SLOT(onUpdateStatus(QString)));
}

