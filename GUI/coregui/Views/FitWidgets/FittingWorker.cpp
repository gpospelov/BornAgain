// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FittingWorker.cpp
//! @brief     Implements class RunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FittingWorker.h"
#include "FitSuite.h"
#include "SampleBuilderFactory.h"
#include "SimulationRegistry.h"
#include "IObserver.h"
#include <QDebug>
#include <QChar>


void FittingWorker::startFit()
{
    qDebug() << "RunFitWidget::run_test_fit()";
    SampleBuilderFactory builderFactory;
    boost::scoped_ptr<ISample> sample(builderFactory.createSample("CylindersInBABuilder"));

    SimulationRegistry simRegistry;
    boost::scoped_ptr<GISASSimulation> simulation(simRegistry.createSimulation("BasicGISAS"));

    simulation->setSample(*sample.get());
    simulation->runSimulation();

    boost::scoped_ptr<OutputData<double> > real_data(simulation->getDetectorIntensity());

    FittingWorker::m_fitsuite = boost::shared_ptr<FitSuite>(new FitSuite());
    //fitSuite->initPrint(100);
    FittingWorker::m_fitsuite->attachObserver(me);
    FittingWorker::m_fitsuite->setMinimizer("Genetic");
    FittingWorker::m_fitsuite->getMinimizer()->getOptions()->setValue("RandomSeed",1);

    FittingWorker::m_fitsuite->addFitParameter("*Height", 4.5 * Units::nanometer, AttLimits::limited(4.0, 6.0), 0.1);
    FittingWorker::m_fitsuite->addFitParameter("*Radius", 5.5 * Units::nanometer, AttLimits::limited(4.0, 6.0), 0.1);

    FittingWorker::m_fitsuite->addSimulationAndRealData(*simulation.get(), *real_data.get());


    // run fit
    FittingWorker::m_fitsuite->runFit();
}

void FittingWorker::update(FitSuite *subject)
{
    QString msg = QString("Iteration: %1\nChi: %2").arg(QString::number(subject->getNumberOfIterations()));
    msg = msg.arg(subject->getChi2(), 10, 'f', 1, QChar(' '));


    emit statusUpdate(msg);
}

void FittingWorker::interrupt()
{
    if (m_fitsuite) {
        m_fitsuite->interruptFitting();
    }
}
