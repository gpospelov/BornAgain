// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/DWBASimulation.h
//! @brief     Defines class DWBASimulation.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DWBASIMULATION_H_
#define DWBASIMULATION_H_

#include "ISimulation.h"
#include "Simulation.h"
#include "OutputData.h"
#include "ThreadInfo.h"
#include "Types.h"
#include "EigenCore.h"
#include "ProgressHandlerDWBA.h"

//! @class DWBASimulation
//! @ingroup algorithms_internal
//! @brief Base class for different simulations, using DWBA.

class BA_CORE_API_ DWBASimulation : public ISimulation
{
public:
    DWBASimulation();

    virtual ~DWBASimulation();

    //! Initializes the simulation with the parameters from simulation
    virtual void init(const Simulation& simulation);

    //! Sets thread information for masking
    virtual void setThreadInfo(const ThreadInfo& thread_info)
    { m_thread_info = thread_info; }

    //! Returns output data containing calculated intensity.
    const OutputData<double>& getDWBAIntensity() const;

#ifndef GCCXML_SKIP_THIS
    //! Returns output data containing calculated polarized intensity.
    const OutputData<Eigen::Matrix2d>& getPolarizedDWBAIntensity() const
    { return *mp_polarization_output; }

    //! Indicates if polarized output data is present
    bool hasPolarizedOutputData() const {
        return mp_polarization_output!=0;
    }
#endif

    //! Adds intensity to current dwba intensity
    void addDWBAIntensity(const OutputData<double>& data_to_add)
    { m_dwba_intensity += data_to_add; }

#ifndef GCCXML_SKIP_THIS
    //! Adds polarized intensity to current polarized dwba intensity
    void addPolarizedDWBAIntensity(const OutputData<Eigen::Matrix2d>
        &data_to_add)
    { (*mp_polarization_output) += data_to_add; }
#endif

    virtual DWBASimulation *clone() const;

    // ---------------------------------
    // external iterators (possibly masked)
    // ---------------------------------

    typedef OutputDataIterator<double, OutputData<double> > iterator;
    typedef OutputDataIterator<const double, const OutputData<double> >
        const_iterator;

    //! Returns read/write iterator that points to the first element
    //! The iterator takes the member ThreadInfo object into consideration.
    iterator begin() { return m_dwba_intensity.begin(m_thread_info); }

    //! Returns read-only iterator that points to the first element
    //! The iterator takes the member ThreadInfo object into consideration.
    const_iterator begin() const  { return m_dwba_intensity.begin(m_thread_info); }

    //! Returns  read/write iterator that points to the one past last element
    //! The iterator takes the member ThreadInfo object into consideration.
    const iterator end() { return m_dwba_intensity.end(m_thread_info); }

    //! Returns  read-only iterator that points to the one past last element
    //! The iterator takes the member ThreadInfo object into consideration.
    const const_iterator end() const { return m_dwba_intensity.end(m_thread_info); }

protected:
    //! Checks if the sample requires a polarized calculation
    bool checkPolarizationPresent() const;

    //! Returns the wavelength of the incoming beam
    double getWaveLength() const;

    //! apply beam polarization to get specific polarized intensity map
    const OutputData<double>&  getPolarizationData() const;

    mutable OutputData<double> m_dwba_intensity;
#ifndef GCCXML_SKIP_THIS
    OutputData<Eigen::Matrix2d> *mp_polarization_output;
#endif
    cvector_t m_ki;
    double m_alpha_i;
    ThreadInfo m_thread_info;
    SimulationParameters m_sim_params;
    Simulation *mp_simulation;

    ProgressHandlerDWBA m_progress;
};

#endif /* DWBASIMULATION_H_ */
