// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/Simulation.h
//! @brief     Defines class Simulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "ISampleBuilder.h"
#include "Instrument.h"
#include "SimulationParameters.h"

#include "EigenCore.h"

class ProgramOptions;

//! Run one simulation.

class BA_CORE_API_ Simulation : public ICloneable, public IParameterized
{
public:
    Simulation();
    Simulation(const ProgramOptions *p_options);
    Simulation(const ISample& p_sample, const ProgramOptions *p_options=0);
    Simulation(const ISampleBuilder *p_sample_builder,
               const ProgramOptions *p_options=0);
    ~Simulation() { delete mp_sample; }

    Simulation *clone() const;

    //! Put into a clean state for running a simulation
    void prepareSimulation();

    //! Run a simulation with the current parameter settings
    void runSimulation();

    //! Returns intensity for a single detector element
    void runSimulationElement(size_t index);

    //! Normalize the detector counts
    void normalize();

    //! Sets the sample to be tested
    void setSample(const ISample& sample);

    //! Returns the sample
    ISample *getSample() const { return mp_sample; }

    //! Sets the sample builder
    void setSampleBuilder(const ISampleBuilder *p_sample_builder);

    //! return sample builder
    const ISampleBuilder *getSampleBuilder() const { return mp_sample_builder; }

    //! Returns detector intensity map for all scan parameters
    const OutputData<double>* getOutputData() const { return &m_intensity_map; }

    //! Clone detector intensity map for all scan parameters.
    OutputData<double>* getIntensityData() const
    { return m_intensity_map.clone(); }

    //! returns component of polarized intensity map
    OutputData<double>* getPolarizedIntensityData(int row, int column) const;

#ifndef GCCXML_SKIP_THIS
    //! Returns polarized intensity map
    const OutputData<Eigen::Matrix2d>* getPolarizedOutputData() const {
        return &m_polarization_output;
    }
#endif

    //! Sets the instrument containing beam and detector information
    void setInstrument(const Instrument& instrument);

    //! Returns the instrument containing beam and detector information
    const Instrument& getInstrument() const { return m_instrument; }

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double lambda, double alpha_i, double phi_i);

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
        IResolutionFunction2D *p_resolution_function);
    void setDetectorResolutionFunction(
        const IResolutionFunction2D &p_resolution_function);

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

    //! Apply smearing of intensity due to tilting of z-axis (DEPRECATED)
    void smearIntensityFromZAxisTilting();

protected:
    Simulation(const Simulation& other);

    //! Registers some class members for later access via parameter pool
    void init_parameters();

    //! Default implementation only adds the detector axes
    void updateIntensityMapAxes();

    //! Update the sample by calling the sample builder, if present
    void updateSample();

    //! Add the intensity maps from the DWBA simulation to the member maps
    void addToIntensityMaps(DWBASimulation *p_dwba_simulation);

    // components describing an experiment and its simulation:
    ISample *mp_sample;
    const ISampleBuilder *mp_sample_builder;
    Instrument m_instrument;
    SimulationParameters m_sim_params;
    ThreadInfo m_thread_info;

    OutputData<double> m_intensity_map;
#ifndef GCCXML_SKIP_THIS
    OutputData<Eigen::Matrix2d> m_polarization_output;
#endif
   bool m_is_normalized;
    const ProgramOptions *mp_options;

    //TODO: investigate usage:
    double deltaAlpha(double alpha, double zeta) const;
    double deltaPhi(double alpha, double phi, double zeta) const;
    void createZetaAndProbVectors(std::vector<double>& zetas,
                                  std::vector<double>& probs,
                                  size_t nbr_zetas, double zeta_sigma) const;
    void addToIntensityMap(double alpha, double phi, double value);
};

#endif /* SIMULATION_H_ */


