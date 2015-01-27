// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/OffSpecSimulation.h
//! @brief     Defines class OffSpecSimulation.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
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
	OffSpecSimulation(const ISample& p_sample, const ProgramOptions *p_options=0);
	OffSpecSimulation(SampleBuilder_t p_sample_builder,
               const ProgramOptions *p_options=0);
    ~OffSpecSimulation() {}

    OffSpecSimulation *clone() const;

    //! Put into a clean state for running a simulation
    void prepareSimulation();

    //! Run a simulation with the current parameter settings
    void runSimulation();

    //! Sets the sample to be tested
    void setSample(const ISample& sample)
    { m_simulation.setSample(sample); }

    //! Returns the sample
    ISample *getSample() const
    { return m_simulation.getSample(); }

    //! Sets the sample builder
    void setSampleBuilder(SampleBuilder_t sample_builder)
    { m_simulation.setSampleBuilder(sample_builder); }

    //! return sample builder
    SampleBuilder_t getSampleBuilder() const
    { return m_simulation.getSampleBuilder(); }

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
        return &m_polarized_intensity;
    }
#endif

    //! Sets the instrument containing beam and detector information
    void setInstrument(const Instrument& instrument);

    //! Returns the instrument containing beam and detector information
    const Instrument& getInstrument() const
    { return m_simulation.getInstrument(); }

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double lambda, const IAxis &alpha_axis, double phi_i);

    //! Sets beam intensity from here (forwarded to Instrument)
    void setBeamIntensity(double intensity)
    { m_simulation.setBeamIntensity(intensity); }

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
    { return m_simulation.getSimulationParameters(); }

    //! Define resolution function for detector
    void setDetectorResolutionFunction(
        IResolutionFunction2D *p_resolution_function) {
    	m_simulation.setDetectorResolutionFunction(p_resolution_function);
    }

    void setDetectorResolutionFunction(
        const IResolutionFunction2D &resolution_function) {
    	m_simulation.setDetectorResolutionFunction(resolution_function);
    }

    //! Sets simulation parameters
    void setSimulationParameters(const SimulationParameters& sim_params)
    { m_simulation.setSimulationParameters(sim_params); }

    //! Sets the batch and thread information to be used
    void setThreadInfo(const ThreadInfo &thread_info)
    { m_simulation.setThreadInfo(thread_info); }

    //! Sets the program options
    void setProgramOptions(ProgramOptions *p_options)
    { m_simulation.setProgramOptions(p_options); }

    //! Adds parameters from local to external pool, and call recursion over direct children
    std::string addParametersToExternalPool(
        std::string path,
        ParameterPool *external_pool,
        int copy_number=-1) const;

protected:
    OffSpecSimulation(const OffSpecSimulation& other);

    //! Registers some class members for later access via parameter pool
    void init_parameters();

    //! Default implementation only adds the detector axes
    void updateIntensityMapAxes();

    //! Adds the integrated intensity (over phi) and adds this to the
    //! intensity map
    void addIntegratedIntensity(size_t index);

    // components describing an off-specular experiment and its simulation:
    Simulation m_simulation;
    IAxis *mp_alpha_i_axis;
    double m_lambda;
    double m_phi;

    OutputData<double> m_intensity_map;
#ifndef GCCXML_SKIP_THIS
    OutputData<Eigen::Matrix2d> m_polarized_intensity;
#endif
};

#endif /* OFFSPECSIMULATION_H_ */