// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/DWBASimulation.h
//! @brief     Defines class DWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DWBASIMULATION_H_
#define DWBASIMULATION_H_

#include "ISimulation.h"
#include "GISASSimulation.h"
#include "OutputData.h"
#include "ThreadInfo.h"
#include "Types.h"
#include "EigenCore.h"
#include "ProgressHandlerDWBA.h"
#include "SimulationElement.h"

//! @class DWBASimulation
//! @ingroup algorithms_internal
//! @brief Base class for different simulations, using DWBA.

class BA_CORE_API_ DWBASimulation : public ISimulation
{
public:
    DWBASimulation();

    virtual ~DWBASimulation();

    //! Initializes the simulation with the parameters from simulation
    virtual void init(const Simulation &simulation,
                      std::vector<SimulationElement>::iterator begin_it,
                      std::vector<SimulationElement>::iterator end_it);

    //! Sets thread information for masking
    virtual void setThreadInfo(const ThreadInfo &thread_info)
    {
        m_thread_info = thread_info;
    }

    //! Returns output data containing calculated intensity.
    const OutputData<double> &getDWBAIntensity() const;

    //! Adds intensity to current dwba intensity
    void addDWBAIntensity(const OutputData<double> &data_to_add)
    {
        m_dwba_intensity += data_to_add;
    }

    virtual DWBASimulation *clone() const;

protected:
    //! Checks if the sample requires a polarized calculation
    bool checkPolarizationPresent() const;

    //! Iterators that defines the sequence of elements that this simulation will work on
    std::vector<SimulationElement>::iterator m_begin_it, m_end_it;

    mutable OutputData<double> m_dwba_intensity;
#ifndef GCCXML_SKIP_THIS
    Eigen::Matrix2cd m_beam_polarization;
    Eigen::Matrix2cd m_detector_polarization;
#endif
    ThreadInfo m_thread_info;
    SimulationParameters m_sim_params;
    Simulation *mp_simulation;

    ProgressHandlerDWBA m_progress;
};

#endif /* DWBASIMULATION_H_ */
