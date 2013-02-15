#ifndef TESTTOYSIMULATION_H
#define TESTTOYSIMULATION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestToySimulation.h
//! @brief  Tests of fitting chain using toy simulation
//! @author Scientific Computing Group at FRM II
//! @date   10.12.2012

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
