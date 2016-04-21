// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/Simulation.h
//! @brief     Declares class Simulation.
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
#include "SimulationOptions.h"
#include "DistributionHandler.h"
#include "ProgressHandler.h"

#include "EigenCore.h"
#include "SimulationElement.h"

class ProgressHandlerDWBA;

//! @class Simulation
//! @ingroup simulation
//! @brief Main class to run the simulation.

class BA_CORE_API_ Simulation : public ICloneable, public IParameterized
{
public:
    Simulation();
    Simulation(const ISample& p_sample);
    Simulation(std::shared_ptr<class ISampleBuilder> p_sample_builder);
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
    void setSampleBuilder(std::shared_ptr<class ISampleBuilder> sample_builder);

    //! return sample builder
    std::shared_ptr<class ISampleBuilder> getSampleBuilder() const { return mp_sample_builder; }

    //! Gets the number of elements this simulation needs to calculate
    virtual int getNumberOfSimulationElements() const=0;

    //! Clone simulated intensity map
    virtual OutputData<double>* getDetectorIntensity(IDetector2D::EAxesUnits units_type = IDetector2D::DEFAULT) const=0;

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

#ifndef GCCXML_SKIP_THIS
    //! sets progress handler (used by GUI)
    void setProgressHandler(ProgressHandler_t progress) { m_progress = progress; }

    //! initializes DWBA progress handler
    void initProgressHandlerDWBA(ProgressHandlerDWBA *dwba_progress);
#endif

    friend class OMPISimulation;

    void setOptions(const SimulationOptions &options);
    const SimulationOptions &getOptions() const;
    SimulationOptions &getOptions();

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

    std::unique_ptr<ISample> mP_sample;
    std::shared_ptr<class ISampleBuilder> mp_sample_builder;
    SimulationOptions m_options;
    DistributionHandler m_distribution_handler;
    ProgressHandler_t m_progress;
    std::vector<SimulationElement> m_sim_elements;

private:
    void imposeConsistencyOfBatchNumbers(int& n_batches, int& current_batch);
};

#endif /* SIMULATION_H_ */
