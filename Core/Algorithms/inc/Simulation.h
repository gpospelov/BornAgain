// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/Simulation.h
//! @brief     Defines class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "ISampleBuilder.h"
#include "Instrument.h"
#include "SimulationParameters.h"
#include "DistributionHandler.h"
#include "ProgressHandler.h"

#include "EigenCore.h"
#include "SimulationElement.h"

#include <boost/function.hpp>

class ProgramOptions;
class ProgressHandlerDWBA;

//! @class Simulation
//! @ingroup simulation
//! @brief Main class to run the simulation.

class BA_CORE_API_ Simulation : public ICloneable, public IParameterized
{
public:
    Simulation();
    Simulation(const ProgramOptions *p_options);
    Simulation(const ISample& p_sample, const ProgramOptions *p_options=0);
    Simulation(SampleBuilder_t p_sample_builder,
               const ProgramOptions *p_options=0);
    virtual ~Simulation() { }

    virtual Simulation *clone() const=0;

    //! Put into a clean state for running a simulation
    virtual void prepareSimulation();

    //! Run a simulation, possibly averaged over parameter distributions
    void runSimulation();

    //! Run an OpenMPI simulation
    void runOMPISimulation();

    //! Sets the sample to be tested
    void setSample(const ISample& sample);

    //! Returns the sample
    ISample *getSample() const { return mP_sample.get(); }

    //! Sets the sample builder
    void setSampleBuilder(SampleBuilder_t sample_builder);

    //! return sample builder
    SampleBuilder_t getSampleBuilder() const { return mp_sample_builder; }

    //! Returns simulation parameters
    SimulationParameters getSimulationParameters() const
    { return m_sim_params; }

    //! Sets simulation parameters
    void setSimulationParameters(const SimulationParameters& sim_params)
    { m_sim_params = sim_params; }

    //! Sets the batch and thread information to be used
    void setThreadInfo(const ThreadInfo &thread_info)
    { m_thread_info = thread_info; }

    //! Sets the program options
    void setProgramOptions(ProgramOptions *p_options)
    { mp_options = p_options; }

    //! Gets the number of elements this simulation needs to calculate
    virtual int getNumberOfSimulationElements() const=0;

    //! Clone simulated intensity map
    virtual OutputData<double>* getDetectorIntensity() const=0;

    //! Adds parameters from local to external pool, and call recursion over direct children
    std::string addParametersToExternalPool(
        std::string path,
        ParameterPool *external_pool,
        int copy_number=-1) const;

    //! add a sampled parameter distribution
    void addParameterDistribution(const std::string &param_name,
            const IDistribution1D &distribution, size_t nbr_samples,
            double sigma_factor=0.0,
            const AttLimits &limits = AttLimits());

    //! add a sampled parameter distribution
    void addParameterDistribution(const ParameterDistribution &par_distr);

    const DistributionHandler& getDistributionHandler() const;

    //! returns wavelength if this is uniquely defined for the current simulation
    virtual double getWavelength() const;

#ifndef GCCXML_SKIP_THIS
    //! sets progress handler (used by GUI)
    void setProgressHandler(ProgressHandler_t progress) { m_progress = progress; }

    //! initializes DWBA progress handler
    void initProgressHandlerDWBA(ProgressHandlerDWBA *dwba_progress);
#endif

    friend class OMPISimulation;

protected:
    Simulation(const Simulation& other);
    //! Registers some class members for later access via parameter pool
    void init_parameters();

    //! Initializes the vector of Simulation elements
    virtual void initSimulationElementVector()=0;

    //! Creates the appropriate data structure (e.g. 2D intensity map) from the calculated
    //! SimulationElement objects
    virtual void transferResultsToIntensityMap()=0;

    //! Returns the intensity of the beam
    virtual double getBeamIntensity() const=0;

    //! Update the sample by calling the sample builder, if present
    void updateSample();

    //! Run a single simulation with the current parameter settings
    void runSingleSimulation();

#ifndef GCCXML_SKIP_THIS
    //! Normalize the detector counts
    void normalize(std::vector<SimulationElement>::iterator begin_it,
                   std::vector<SimulationElement>::iterator end_it) const;
#endif

    //! Verify existence of the DWBASimulation object
    void verifyDWBASimulation(DWBASimulation *dwbaSimulation);

    //! Returns the start iterator of simulation elements for the current batch
    std::vector<SimulationElement>::iterator getBatchStart(int n_batches, int current_batch);

    //! Returns the end iterator of simulation elements for the current batch
    std::vector<SimulationElement>::iterator getBatchEnd(int n_batches, int current_batch);

    // components describing an experiment and its simulation:
    boost::scoped_ptr<ISample> mP_sample;
    SampleBuilder_t mp_sample_builder;
    SimulationParameters m_sim_params;
    ThreadInfo m_thread_info;

    const ProgramOptions *mp_options;

    DistributionHandler m_distribution_handler;
    ProgressHandler_t m_progress;
    std::vector<SimulationElement> m_sim_elements;

private:
    void imposeConsistencyOfBatchNumbers(int& n_batches, int& current_batch);
};

#endif /* SIMULATION_H_ */
