// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/Simulation.h
//! @brief     Defines class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATION_H
#define SIMULATION_H

#include "DistributionHandler.h"
#include "IDetector2D.h"
#include "ProgressHandler.h"
#include "SimulationOptions.h"

template<class T> class OutputData;
class Computation;
class MultiLayer;
class IMultiLayerBuilder;

//! Main class to run the simulation, base class for OffSpecularSimulation and GISASSimulation.
//! @ingroup simulation

class BA_CORE_API_ Simulation : public ICloneable, public IParameterized
{
public:
    Simulation();
    Simulation(const MultiLayer& p_sample);
    Simulation(std::shared_ptr<IMultiLayerBuilder> p_sample_builder);
    virtual ~Simulation();

    virtual Simulation* clone() const=0;

    //! Put into a clean state for running a simulation
    virtual void prepareSimulation();

    //! Run a simulation, possibly averaged over parameter distributions
    void runSimulation();

    //! Run an OpenMPI simulation
    //unused void runOMPISimulation();

    //! Sets the sample to be tested
    void setSample(const MultiLayer& sample);

    //! Returns the sample
    MultiLayer* getSample() const { return mP_sample.get(); }

    //! Sets the sample builder
    void setSampleBuilder(std::shared_ptr<IMultiLayerBuilder> sample_builder);

    //! return sample builder
    std::shared_ptr<IMultiLayerBuilder> getSampleBuilder() const { return mp_sample_builder; }

    //! Gets the number of elements this simulation needs to calculate
    virtual int getNumberOfSimulationElements() const=0;

    //! Clone simulated intensity map
    virtual OutputData<double>* getDetectorIntensity(
        IDetector2D::EAxesUnits units_type = IDetector2D::DEFAULT) const=0;

    //! Adds parameters from local to external pool, and call recursion over direct children
    std::string addParametersToExternalPool(
        std::string path, ParameterPool* external_pool, int copy_number=-1) const;

    //! add a sampled parameter distribution
    void addParameterDistribution(
        const std::string& param_name, const IDistribution1D& distribution, size_t nbr_samples,
        double sigma_factor=0.0, const RealLimits& limits = RealLimits());

    //! add a sampled parameter distribution
    void addParameterDistribution(const ParameterDistribution& par_distr);

    const DistributionHandler& getDistributionHandler() const;

    //unused friend class OMPISimulation;

    void setOptions(const SimulationOptions& options) { m_options = options; }
    const SimulationOptions& getOptions() const { return m_options; }
    SimulationOptions& getOptions() { return m_options; }

    void subscribe(ProgressHandler::Callback_t inform) { m_progress.subscribe(inform); }
    void setTerminalProgressMonitor();

protected:
    Simulation(const Simulation& other);

    //! Initializes the vector of Simulation elements
    virtual void initSimulationElementVector()=0;

    //! Creates the appropriate data structure (e.g. 2D intensity map) from the calculated
    //! SimulationElement objects
    virtual void transferResultsToIntensityMap()=0;

    virtual double getBeamIntensity() const=0;

    //! Update the sample by calling the sample builder, if present
    void updateSample();

    //! Run a single simulation with the current parameter settings
    void runSingleSimulation();

#ifndef SWIG
    void normalize(std::vector<SimulationElement>::iterator begin_it,
                   std::vector<SimulationElement>::iterator end_it) const;
#endif

    //! Returns the start iterator of simulation elements for the current batch
    std::vector<SimulationElement>::iterator getBatchStart(int n_batches, int current_batch);

    //! Returns the end iterator of simulation elements for the current batch
    std::vector<SimulationElement>::iterator getBatchEnd(int n_batches, int current_batch);

    std::unique_ptr<MultiLayer> mP_sample;
    std::shared_ptr<IMultiLayerBuilder> mp_sample_builder;
    SimulationOptions m_options;
    DistributionHandler m_distribution_handler;
    ProgressHandler m_progress;
    std::vector<SimulationElement> m_sim_elements;

private:
    void imposeConsistencyOfBatchNumbers(int& n_batches, int& current_batch);
};

#endif // SIMULATION_H
