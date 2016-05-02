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
#include "FitParametersWidget.h"
#include "RunFitManager.h"
#include "GUIFitObserver.h"
#include <QVBoxLayout>
#include <QTabWidget>
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
    qDebug() << "FitSuiteWidget::onUpdatePlots";
}

void FitSuiteWidget::onUpdateParameters(const QStringList &parameters, QVector<double> values)
{
    Q_UNUSED(parameters);
    Q_UNUSED(values);
    qDebug() << "FitSuiteWidget::onUpdateParameters";
}

void FitSuiteWidget::startFitting()
{
    if(!m_currentItem)
        return;
    qDebug() << "FitSuiteWidget::startFitting()";
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

    connect(m_manager, SIGNAL(error(QString)), this, SLOT(onError(QString)));
    connect(m_observer.get(), SIGNAL(updatePlots(OutputData<double>*,OutputData<double>*)),
            this, SLOT(onUpdatePlots(OutputData<double>*,OutputData<double>*)));
    connect(m_observer.get(), SIGNAL(updateParameters(QStringList,QVector<double>)),
            this, SLOT(onUpdateParameters(QStringList,QVector<double>)));
}

