#ifndef DWBASIMULATION_H_
#define DWBASIMULATION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DWBASimulation.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Jun 26, 2012

#include "ISimulation.h"
#include "OutputData.h"
#include "Types.h"

//- -------------------------------------------------------------------
//! @class DWBASimulation
//! @brief Calculates scattering cross sections in DWBA
//- -------------------------------------------------------------------
class DWBASimulation : public ISimulation
{
public:
    DWBASimulation();
    virtual ~DWBASimulation();

    //! Initialize the simulation with the parameters from experiment
    virtual void init(const Experiment &experiment);

    // TODO: return const or clone
    OutputData<double> &getDWBAIntensity();
protected:
    OutputData<double> m_dwba_intensity;
    cvector_t m_ki;
    double m_alpha_i;

private:
    //! copy constructor and assignment operator are hidden
    DWBASimulation(const DWBASimulation &);
    DWBASimulation &operator=(const DWBASimulation &);

};

inline OutputData<double> &DWBASimulation::getDWBAIntensity() {
    return m_dwba_intensity;
}

#endif /* DWBASIMULATION_H_ */
