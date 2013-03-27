// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/DWBASimulation.h
//! @brief     Defines class DWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef DWBASIMULATION_H_
#define DWBASIMULATION_H_

#include "ISimulation.h"
#include "Simulation.h"
#include "OutputData.h"
#include "ThreadInfo.h"
#include "Types.h"

//! Base class for different simulations, using DWBA.

class DWBASimulation : public ISimulation
{
 public:
    DWBASimulation() : m_alpha_i(0), m_thread_info(), mp_simulation(0) {}

    virtual ~DWBASimulation() { delete mp_simulation; }

    //! Initializes the simulation with the parameters from simulation
    virtual void init(const Simulation& simulation);

    //! Sets thread information for masking
    virtual void setThreadInfo(const ThreadInfo& thread_info)
    { m_thread_info = thread_info; }

    //! Returns output data containing calculated intensity.
    const OutputData<double>& getDWBAIntensity() const
    { return m_dwba_intensity; }

    //! Adds intensity to current dwba intensity
    void addDWBAIntensity(const OutputData<double>& data_to_add)
    { m_dwba_intensity += data_to_add; }

    virtual DWBASimulation *clone() const;

    // ---------------------------------
    // external iterators (possibly masked)
    // ---------------------------------

    typedef OutputDataIterator<double, OutputData<double> > iterator;
    typedef OutputDataIterator<const double, const OutputData<double> >
        const_iterator;

    //! Returns read/write iterator that points to the first element
    iterator begin();

    //! Returns read-only iterator that points to the first element
    const_iterator begin() const;

    //! Returns  read/write iterator that points to the one past last element
    const iterator end() { return m_dwba_intensity.end(); }

    //! Returns  read-only iterator that points to the one past last element
    const const_iterator end() const { return m_dwba_intensity.end(); }

 protected:
    OutputData<double> m_dwba_intensity;
    cvector_t m_ki;
    double m_alpha_i;
    double getWaveLength() const;
    ThreadInfo m_thread_info;
    SimulationParameters m_sim_params;
    Simulation *mp_simulation;
};

#endif /* DWBASIMULATION_H_ */
