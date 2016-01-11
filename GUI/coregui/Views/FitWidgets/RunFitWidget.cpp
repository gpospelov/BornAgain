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
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>


RunFitWidget::RunFitWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;


    QPushButton *runFit = new QPushButton("Run fit");
    connect(runFit, SIGNAL(clicked()), this, SLOT(onRunFit()));

    mainLayout->addWidget(runFit);

    setLayout(mainLayout);

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
