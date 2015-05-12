// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestToySimulation.h
//! @brief     Defines classes ToySimulation, TestToySimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTTOYSIMULATION_H
#define TESTTOYSIMULATION_H

#include "IApplicationTest.h"
#include "GISASSimulation.h"
#include "OutputData.h"
#include "TestFumiliLMA.h"
#include "FitSuite.h"

#include <vector>
#include "TF2.h"

//! Toy simulation to test whole fitting chain with simple 2D functions.

class ToySimulation : public GISASSimulation
{
public:
    ToySimulation(TF2 *func)
        : m_func(func)
    {
        pars.resize(func->GetNpar(), 0.0);
        setName("ToySimulation");
        init_parameters();
    }
    virtual ~ToySimulation() {}
    virtual void runSimulation();
    virtual ToySimulation *clone() const
    { return new ToySimulation(*this); }
    void setParameter(size_t i, double value) { pars[i] = value; }
protected:
    virtual void init_parameters();
private:
    ToySimulation(const ToySimulation& other)
        : GISASSimulation(other), m_func(other.m_func), pars(other.pars)
    {
        setName("ToySimulation");
        init_parameters();
    }
    TF2 *m_func;
    std::vector<double > pars;
};

//! Test of fitting chain using toy simulation.

class TestToySimulation : public IApplicationTest
{
public:
    TestToySimulation();
    virtual ~TestToySimulation();
    virtual void execute();

private:
    void initializeSimulationAndRealData();

    //! simulation function
    IFunctionObject *m_func_object;
    //! ROOT representation of the simulation function with min, max defined
    TF2 *m_func;
    double m_sigma_noise;
    ToySimulation *m_simulation;
    OutputData<double > *m_real_data;
    FitSuite *m_fitSuite;
};

#endif // TESTTOYSIMULATION_H


