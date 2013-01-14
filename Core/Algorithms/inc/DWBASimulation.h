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
#include "Experiment.h"
#include "OutputData.h"
#include "ThreadInfo.h"
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

    //! Set thread information for masking
    virtual void setThreadInfo(const ThreadInfo &thread_info) {
        m_thread_info = thread_info;
    }

    //! return output data containing calculated intensity
    const OutputData<double> &getDWBAIntensity() const;

    //! add intensity to current dwba intensity
    void addDWBAIntensity(const OutputData<double > &data_to_add);

    //! clone DWBA simulation
    virtual DWBASimulation *clone() const;

    // ---------------------------------
    // external iterators (possibly masked)
    // ---------------------------------

    typedef OutputDataIterator<double, OutputData<double> > iterator;
    typedef OutputDataIterator<const double, const OutputData<double> > const_iterator;

    //! return a read/write iterator that points to the first element
    iterator begin();

    //! return a read-only iterator that points to the first element
    const_iterator begin() const;

    //! return a read/write iterator that points to the one past last element
    const iterator end() { return m_dwba_intensity.end(); }

    //! return a read-only iterator that points to the one past last element
    const const_iterator end() const  { return m_dwba_intensity.end(); }

protected:
    OutputData<double> m_dwba_intensity;
    cvector_t m_ki;
    double m_alpha_i;
    double getWaveLength() const;
    ThreadInfo m_thread_info;

};

inline const OutputData<double> &DWBASimulation::getDWBAIntensity() const {
    return m_dwba_intensity;
}

inline void DWBASimulation::addDWBAIntensity(const OutputData<double> &data_to_add) {
    m_dwba_intensity += data_to_add;
}


#endif /* DWBASIMULATION_H_ */
