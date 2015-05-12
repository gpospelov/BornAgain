// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/OffSpecSimulation.h
//! @brief     Defines class OffSpecSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OFFSPECSIMULATION_H_
#define OFFSPECSIMULATION_H_

#include "Simulation.h"

//! @class OffSpecSimulation
//! @ingroup simulation
//! @brief Main class to run an off-specular simulation.

class BA_CORE_API_ OffSpecSimulation : public ICloneable, public IParameterized
{
public:
    OffSpecSimulation();
    OffSpecSimulation(const ProgramOptions *p_options);
    OffSpecSimulation(const ISample &p_sample, const ProgramOptions *p_options = 0);
    OffSpecSimulation(SampleBuilder_t p_sample_builder, const ProgramOptions *p_options = 0);
    ~OffSpecSimulation()
    {
    }

    OffSpecSimulation *clone() const;

    //! Put into a clean state for running a simulation
    void prepareSimulation();

    //! Run a simulation with the current parameter settings
    void runSimulation();

    //! Sets the sample to be tested
    void setSample(const ISample &sample)
    {
        m_simulation.setSample(sample);
    }

    //! Returns the sample
    ISample *getSample() const
    {
        return m_simulation.getSample();
    }

    //! Sets the sample builder
    void setSampleBuilder(SampleBuilder_t sample_builder)
    {
        m_simulation.setSampleBuilder(sample_builder);
    }

    //! return sample builder
    SampleBuilder_t getSampleBuilder() const
    {
        return m_simulation.getSampleBuilder();
    }

    //! Returns detector intensity map for all scan parameters
    const OutputData<double> *getOutputData() const
    {
        return &m_intensity_map;
    }

    //! Clone detector intensity map for all scan parameters.
    OutputData<double> *getIntensityData() const;

    //! Sets the instrument containing beam and detector information
    void setInstrument(const Instrument &instrument);

    //! Returns the instrument containing beam and detector information
    const Instrument &getInstrument() const
    {
        return m_simulation.getInstrument();
    }

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double lambda, const IAxis &alpha_axis, double phi_i);

    //! Sets beam intensity from here (forwarded to Instrument)
    void setBeamIntensity(double intensity)
    {
        m_simulation.setBeamIntensity(intensity);
    }

    //! Sets the beam polarization according to the given Bloch vector
    void setBeamPolarization(const kvector_t &bloch_vector)
    {
        m_simulation.setBeamPolarization(bloch_vector);
    }

    //! Sets detector parameters using axes of output data
    void setDetectorParameters(const OutputData<double> &output_data);

    //! Sets detector parameters using angle ranges
    void setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max, size_t n_alpha,
                               double alpha_f_min, double alpha_f_max, bool isgisaxs_style = false);

    //! Sets detector parameters using parameter object
    void setDetectorParameters(const DetectorParameters &params);

    //! Returns simulation parameters
    SimulationParameters getSimulationParameters() const
    {
        return m_simulation.getSimulationParameters();
    }

    //! Define resolution function for detector
    void setDetectorResolutionFunction(const IResolutionFunction2D &resolution_function)
    {
        m_simulation.setDetectorResolutionFunction(resolution_function);
    }

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t &direction, double efficiency,
                               double total_transmission = 1.0)
    {
        m_simulation.setAnalyzerProperties(direction, efficiency, total_transmission);
    }

    //! Sets simulation parameters
    void setSimulationParameters(const SimulationParameters &sim_params)
    {
        m_simulation.setSimulationParameters(sim_params);
    }

    //! Sets the batch and thread information to be used
    void setThreadInfo(const ThreadInfo &thread_info)
    {
        m_simulation.setThreadInfo(thread_info);
    }

    //! Sets the program options
    void setProgramOptions(ProgramOptions *p_options)
    {
        m_simulation.setProgramOptions(p_options);
    }

    //! Adds parameters from local to external pool, and call recursion over direct children
    std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                            int copy_number = -1) const;

protected:
    OffSpecSimulation(const OffSpecSimulation &other);

    //! Registers some class members for later access via parameter pool
    void init_parameters();

    //! Default implementation only adds the detector axes
    void updateIntensityMapAxes();

    //! Adds the integrated intensity (over phi) and adds this to the
    //! intensity map
    void addIntegratedIntensity(size_t index);

    // components describing an off-specular experiment and its simulation:
    GISASSimulation m_simulation;
    IAxis *mp_alpha_i_axis;
    double m_lambda;
    double m_phi;

    OutputData<double> m_intensity_map;
};

#endif /* OFFSPECSIMULATION_H_ */
