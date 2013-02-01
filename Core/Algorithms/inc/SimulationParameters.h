#ifndef SIMULATIONPARAMETERS_H_
#define SIMULATIONPARAMETERS_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   SimulationParameters.h
//! @brief  Definition of SimulationParameters class
//! @author Scientific Computing Group at FRM II
//! @date   Jan 24, 2013

//- -------------------------------------------------------------------
//! @class SimulationParameters
//! @brief Definition of parameter class collecting the different
//! options for simulation
//- -------------------------------------------------------------------
class SimulationParameters
{
public:
    SimulationParameters();
    enum EFramework { DWBA, BA } me_framework;
    enum EInterferenceApproximation { DA, LMA, SSCA, ISGISAXSMOR } me_if_approx;
    enum ELatticeType { NONE, LATTICE, PARA1D, PARA1DFINITE } me_lattice_type;
};

inline SimulationParameters::SimulationParameters()
: me_framework(DWBA)
, me_if_approx(DA)
, me_lattice_type(NONE)
{
}

#endif /* SIMULATIONPARAMETERS_H_ */
