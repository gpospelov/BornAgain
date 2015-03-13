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
    ~Simulation() { delete mp_sample; }

    Simulation *clone() const;

    //! Put into a clean state for running a simulation
    void prepareSimulation();

    //! Run a simulation, possibly averaged over parameter distributions
    void runSimulation();

    //! Run an OpenMPI simulation
    void runOMPISimulation();

    //! Normalize the detector counts
    void normalize();

    //! Sets the sample to be tested
    void setSample(const ISample& sample);

    //! Returns the sample
    ISample *getSample() const { return mp_sample; }

    //! Sets the sample builder
    void setSampleBuilder(SampleBuilder_t sample_builder);

    //! return sample builder
    SampleBuilder_t getSampleBuilder() const { return mp_sample_builder; }

    //! Returns detector intensity map for all scan parameters (no detector resolution)
    const OutputData<double>* getOutputData() const { return &m_intensity_map; }

    //! Clone detector intensity map for all scan parameters (apply detector resolution function first)
    OutputData<double>* getIntensityData() const;

    //! returns component of polarized intensity map (apply detector resolution first)
    OutputData<double>* getPolarizedIntensityData(int row, int column) const;

#ifndef GCCXML_SKIP_THIS
    //! Returns polarized intensity map (no detector resolution)
    const OutputData<Eigen::Matrix2d>* getPolarizedOutputData() const {
        return &m_polarization_output;
    }
#endif

    //! Sets the instrument containing beam and detector information
    void setInstrument(const Instrument& instrument);

    //! Returns the instrument containing beam and detector information
    const Instrument& getInstrument() const { return m_instrument; }

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double wavelength, double alpha_i, double phi_i);

    //! Sets beam intensity from here (forwarded to Instrument)
    void setBeamIntensity(double intensity);

    //! Sets detector parameters using axes of output data
    void setDetectorParameters(const OutputData<double> &output_data);

    //! Sets detector parameters using angle ranges
    void setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max,
        size_t n_alpha, double alpha_f_min, double alpha_f_max,
        bool isgisaxs_style=false);

    //! Sets detector parameters using parameter object
    void setDetectorParameters(const DetectorParameters& params);
    //! Returns simulation parameters
    SimulationParameters getSimulationParameters() const
    { return m_sim_params; }

    //! Define resolution function for detector
    void setDetectorResolutionFunction(
        const IResolutionFunction2D &resolution_function);

    //! Removes detector resolution function
    void removeDetectorResolutionFunction();

    //! Sets simulation parameters
    void setSimulationParameters(const SimulationParameters& sim_params)
    { m_sim_params = sim_params; }

    //! Sets the batch and thread information to be used
    void setThreadInfo(const ThreadInfo &thread_info)
    { m_thread_info = thread_info; }

    //! Sets the program options
    void setProgramOptions(ProgramOptions *p_options)
    { mp_options = p_options; }

    //! Adds parameters from local to external pool, and call recursion over direct children
    std::string addParametersToExternalPool(
        std::string path,
        ParameterPool *external_pool,
        int copy_number=-1) const;

	//! add a sampled parameter distribution
    void addParameterDistribution(const std::string &param_name,
            const IDistribution1D &distribution, size_t nbr_samples,
            double sigma_factor=0.0);

    //! add a sampled parameter distribution
    void addParameterDistribution(const ParameterDistribution &par_distr);

    const DistributionHandler& getDistributionHandler() const;

    //! OffSpecSimulation needs protected copy constructor
    friend class OffSpecSimulation;

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

    //! Default implementation only adds the detector axes
    void updateIntensityMapAxes();
    void updatePolarizationMapAxes();

    //! Update the sample by calling the sample builder, if present
    void updateSample();

    //! Add the intensity maps from the DWBA simulation to the member maps
    void addToIntensityMaps(DWBASimulation *p_dwba_simulation);

    //! Run a single simulation with the current parameter settings
    void runSingleSimulation();

    void verifyDWBASimulation(DWBASimulation *dwbaSimulation);

    // components describing an experiment and its simulation:
    ISample *mp_sample;
    SampleBuilder_t mp_sample_builder;
    Instrument m_instrument;
    SimulationParameters m_sim_params;
    ThreadInfo m_thread_info;

    OutputData<double> m_intensity_map;
#ifndef GCCXML_SKIP_THIS
    OutputData<Eigen::Matrix2d> m_polarization_output;
#endif
    bool m_is_normalized;
    const ProgramOptions *mp_options;

    DistributionHandler m_distribution_handler;
    ProgressHandler_t m_progress;
};

#endif /* SIMULATION_H_ */
