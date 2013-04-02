// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/SimulationParameters.h
//! @brief     Defines class SimulationParameters.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONPARAMETERS_H_
#define SIMULATIONPARAMETERS_H_

//! Collect the different options for simulation

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


