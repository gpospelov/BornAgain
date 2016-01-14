// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitWidget.cpp
//! @brief     Implements class RunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RunFitWidget.h"
#include "SampleBuilderFactory.h"
#include "SimulationRegistry.h"
#include "FitSuite.h"
#include "FittingWorker.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QLabel>
#include <QString>
#include <QThread>


RunFitWidget::RunFitWidget(QWidget *parent)
    : QWidget(parent)
    , m_status(0)
{
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QVBoxLayout *tabLayout = new QVBoxLayout();
    tabLayout->setSizeConstraint(QLayout::SetMaximumSize);

    QTabWidget *tabWidget = new QTabWidget();
    QWidget *tab1 = new QWidget();
    QWidget *tab2 = new QWidget();
    QWidget *tab3 = new QWidget();

    tabWidget->addTab(tab1, QStringLiteral("Import experimental data"));
    tabWidget->addTab(tab2, QStringLiteral("Setup fitting parameter"));
    tabWidget->addTab(tab3, QStringLiteral("Run fit"));

    QPushButton *runBut = new QPushButton(QStringLiteral("Run"), tab3);
    runBut->setGeometry(QRect(10, 10, 99, 27));
    stopBut = new QPushButton(QStringLiteral("Stop"), tab3);
    stopBut->setGeometry(QRect(10, 50, 99, 27));
    m_status = new QLabel(tab3);
    m_status->setGeometry(QRect(30, 110, 300, 50));

    tabWidget->setCurrentIndex(2);
    tabLayout->addWidget(tabWidget);
    mainLayout->addLayout(tabLayout);

    connect(runBut, SIGNAL(clicked()), this, SLOT(onRunClicked()));
    connect(stopBut, SIGNAL(clicked()), this, SLOT(onStop()));

    setLayout(mainLayout);
}

void RunFitWidget::onRunClicked()
{
    QThread *thread = new QThread;
    FittingWorker *worker = new FittingWorker();
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(startFit()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(stopBut, SIGNAL(clicked()), worker, SLOT(interrupt()), Qt::DirectConnection);
    connect(worker, SIGNAL(statusUpdate(const QString &)),
            this, SLOT(onStatusUpdate(const QString &)));

    thread->start();
}

void RunFitWidget::onStatusUpdate(const QString &message)
{
    m_status->setText(message);
}

void RunFitWidget::onStop()
{

}

void RunFitWidget::onRunFit()
{
    run_test_fit();
//    run_test_fit_long();
}

void RunFitWidget::run_test_fit()
{
    qDebug() << "RunFitWidget::run_test_fit()";
    SampleBuilderFactory builderFactory;
    boost::scoped_ptr<ISample> sample(builderFactory.createSample("CylindersInBABuilder"));

    SimulationRegistry simRegistry;
    boost::scoped_ptr<GISASSimulation> simulation(simRegistry.createSimulation("BasicGISAS"));

    simulation->setSample(*sample.get());
    simulation->runSimulation();

    boost::scoped_ptr<OutputData<double> > real_data(simulation->getDetectorIntensity());

    boost::scoped_ptr<FitSuite> fitSuite(new FitSuite());
    fitSuite->initPrint(5);
    fitSuite->addFitParameter("*Height", 4.5 * Units::nanometer, AttLimits::lowerLimited(0.01));
    fitSuite->addFitParameter("*Radius", 5.5 * Units::nanometer, AttLimits::lowerLimited(0.01));

    fitSuite->addSimulationAndRealData(*simulation.get(), *real_data.get());


    // run fit
    fitSuite->runFit();
}

void RunFitWidget::run_test_fit_long()
{
    qDebug() << "RunFitWidget::run_test_fit()";
    SampleBuilderFactory builderFactory;
    boost::scoped_ptr<ISample> sample(builderFactory.createSample("CylindersInBABuilder"));

    SimulationRegistry simRegistry;
    boost::scoped_ptr<GISASSimulation> simulation(simRegistry.createSimulation("BasicGISAS"));

    simulation->setSample(*sample.get());
    simulation->runSimulation();

    boost::scoped_ptr<OutputData<double> > real_data(simulation->getDetectorIntensity());

    boost::scoped_ptr<FitSuite> fitSuite(new FitSuite());
    fitSuite->initPrint(100);
    fitSuite->setMinimizer("Genetic");
    fitSuite->getMinimizer()->getOptions()->setMaxIterations(1);
    fitSuite->getMinimizer()->getOptions()->setValue("RandomSeed",1);

    fitSuite->addFitParameter("*Height", 4.5 * Units::nanometer, AttLimits::limited(4.0, 6.0), 0.1);
    fitSuite->addFitParameter("*Radius", 5.5 * Units::nanometer, AttLimits::limited(4.0, 6.0), 0.1);

    fitSuite->addSimulationAndRealData(*simulation.get(), *real_data.get());


    // run fit
    fitSuite->runFit();

}
