#ifndef FITSUITE_H
#define FITSUITE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitSuite.h
//! @brief  Definition of FitSuite class
//! @author Scientific Computing Group at FRM II
//! @date   05.10.2012


#include "OutputData.h"
class Experiment;
class Minimizer;

//- -------------------------------------------------------------------
//! @class FitSuite
//! @brief Main class to perform fitting
//- -------------------------------------------------------------------
class FitSuite
{
public:
    FitSuite();

    void setExperiment(Experiment *experiment) { m_experiment = experiment; }
    void setMinimizer(Minimizer *minimizer) { m_minimizer = minimizer; }
private:
    Experiment *m_experiment;
    Minimizer  *m_minimizer;
};

#endif // FITSUITE_H
