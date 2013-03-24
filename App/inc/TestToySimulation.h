// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/TestToySimulation.h 
//! @brief     Defines class TestToySimulation.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTTOYSIMULATION_H
#define TESTTOYSIMULATION_H

#include "IFunctionalTest.h"
#include "Simulation.h"
#include "OutputData.h"
#include "TestFumiliLMA.h"
#include "FitSuite.h"

#include <vector>
#include "TF2.h"


//- -------------------------------------------------------------------
//! @class ToySimulation
//! @brief Toy simulation to test whole fitting chain with simple 2D functions
//- -------------------------------------------------------------------
class ToySimulation : public Simulation
{
public:
    ToySimulation(TF2 *func) : m_func(func) { pars.resize(func->GetNpar(), 0.0); setName("ToySimulation"); init_parameters(); }
    virtual ~ToySimulation() {}
    virtual void runSimulation();
    virtual ToySimulation *clone() const { return new ToySimulation(*this); }
    void setParameter(size_t i, double value) { pars[i] = value; }
protected:
    virtual void init_parameters();
private:
    ToySimulation(const ToySimulation &other) : Simulation(other), m_func(other.m_func), pars(other.pars)
    {
        setName("ToySimulation");
        init_parameters();
    }
    TF2 *m_func;
    std::vector<double > pars;
};


//- -------------------------------------------------------------------
//! @class TestToySimulation
//! @brief Test of fitting chain using toy simulation
//- -------------------------------------------------------------------
class TestToySimulation : public IFunctionalTest
{
public:
    TestToySimulation();
    virtual ~TestToySimulation();
    virtual void execute();

private:
    void initializeSimulationAndRealData();

    IFunctionObject *m_func_object; //! simulation function
    TF2 *m_func; //! ROOT representation of the simulation function with min, max defined
    double m_sigma_noise;
    ToySimulation *m_simulation;
    OutputData<double > *m_real_data;
    FitSuite *m_fitSuite;
};

#endif // TESTTOYSIMULATION_H
