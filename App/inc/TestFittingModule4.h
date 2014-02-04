// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestFittingModule4.h
//! @brief     Defines class TestFittingModule4.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTFITTINGMODULE4_H_
#define TESTFITTINGMODULE4_H_

#include "IApplicationTest.h"
#include "OutputData.h"
#include "ISample.h"
#include "Simulation.h"
#include "ISampleBuilder.h"

class FitSuite;

//! Testing Genetic and SimmulatedAnnealing minimizers
//!
//! Cylinders on top of substrate without interference. Combination of two
//! minimizers is used: Genetic algorithm to run quickly through parameter space
//! to identify most promising local minima and then Migrad to explore it.

class TestFittingModule4 : public IApplicationTest
{
public:
    TestFittingModule4();
    virtual ~TestFittingModule4();
    virtual void execute();

private:
    void initializeSample();
    void initializeSimulation();
    void initializeRealData();

    OutputData<double> *mp_real_data;
    OutputData<double> *mp_simulated_data;
    Simulation *mp_simulation;
    ISample *mp_sample;
    FitSuite *m_fitSuite;
};

#endif /* TESTFITTINGMODULE4_H_ */


