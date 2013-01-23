#ifndef TESTTOYEXPERIMENT_H
#define TESTTOYEXPERIMENT_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestToyExperiment.h
//! @brief  Tests of fitting chain using toy experiment
//! @author Scientific Computing Group at FRM II
//! @date   10.12.2012

#include "IFunctionalTest.h"
#include "Experiment.h"
#include "OutputData.h"
#include "TestFumiliLMA.h"
#include "FitSuite.h"

#include <vector>
#include "TF2.h"


//- -------------------------------------------------------------------
//! @class ToyExperiment
//! @brief Toy experiment to test whole fitting chain with simple 2D functions
//- -------------------------------------------------------------------
class ToyExperiment : public Experiment
{
public:
    ToyExperiment(TF2 *func) : m_func(func) { pars.resize(func->GetNpar(), 0.0); setName("ToyExperiment"); init_parameters(); }
    virtual ~ToyExperiment() {}
    virtual void runSimulation();
    virtual ToyExperiment *clone() const { return new ToyExperiment(*this); }
    void setParameter(size_t i, double value) { pars[i] = value; }
protected:
    virtual void init_parameters();
private:
    ToyExperiment(const ToyExperiment &other) : Experiment(other), m_func(other.m_func), pars(other.pars)
    {
        setName("ToyExperiment");
        init_parameters();
    }
    TF2 *m_func;
    std::vector<double > pars;
};




//- -------------------------------------------------------------------
//! @class TestToyExperiment
//! @brief Test of fitting chain using toy experiment
//- -------------------------------------------------------------------
class TestToyExperiment : public IFunctionalTest
{
public:
    TestToyExperiment();
    virtual ~TestToyExperiment();
    virtual void execute();

private:
    void initializeExperimentAndRealData();

    IFunctionObject *m_func_object; //! simulation function
    TF2 *m_func; //! ROOT representation of the simulation function with min, max defined
    double m_sigma_noise;
    ToyExperiment *m_experiment;
    OutputData<double > *m_real_data;
    FitSuite *m_fitSuite;

};





#endif // TESTTOYEXPERIMENT_H
