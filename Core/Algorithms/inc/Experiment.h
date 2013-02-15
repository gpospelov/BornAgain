#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Experiment.h
//! @brief  Definition of Experiment class
//! @author Scientific Computing Group at FRM II
//! @date   20.06.2012

#include "ISample.h"
#include "ISampleBuilder.h"
#include "OutputData.h"
#include "Instrument.h"
#include "SimulationParameters.h"

class ProgramOptions;

class Experiment : public IParameterized, public ICloneable
{
public:
    Experiment();
    Experiment(const ProgramOptions *p_options);
    Experiment(const ISample &p_sample, const ProgramOptions *p_options=0);
    Experiment(const ISampleBuilder *p_sample_builder, const ProgramOptions *p_options=0);
    virtual ~Experiment() {delete mp_sample;}

    //! clone method fot the experiment
    virtual Experiment *clone() const;

    //! run a simulation with the current parameter settings
    virtual void runExperiment();

    //! normalize the detector counts
    virtual void normalize();

    //! set the sample to be tested
    void setSample(const ISample &p_sample);

    //! get the sample
    ISample *getSample() { return mp_sample; }
    const ISample *getSample() const { return mp_sample; }

    //! set the sample builder
    void setSampleBuilder(const ISampleBuilder *p_sample_builder);

    //! get data structure that contains the intensity map on the detector for all scan parameters
    OutputData<double>* getOutputDataClone() const;

    const OutputData<double>* getOutputData() const;

    //! get the instrument containing beam and detector information
    Instrument &getInstrument() { return m_instrument; }
    const Instrument &getInstrument() const { return m_instrument; }

    //! set beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double lambda, double alpha_i, double phi_i);

    //! set beam intensity from here (forwarded to Instrument)
    void setBeamIntensity(double intensity);

    //! set detector parameters using axes of output data
    void setDetectorParameters(const OutputData<double > &output_data);

    //! get simulation parameters
    SimulationParameters getSimulationParameters() const { return m_sim_params; }

    //! set simulation parameters
    void setSimulationParameters(const SimulationParameters &sim_params) {
        m_sim_params = sim_params;
    }

    //! set the program options
    void setProgramOptions(ProgramOptions *p_options) { mp_options = p_options; }

    //! add parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const;

protected:
    Experiment(const Experiment &other);

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! Default implementation only adds the detector axes
    virtual void updateIntensityMapAxes();

    //! Update the sample by calling the sample builder, if present
    void updateSample();

    ISample *mp_sample;
    const ISampleBuilder *mp_sample_builder;
    Instrument m_instrument;
    OutputData<double> m_intensity_map;
    bool m_is_normalized;
    const ProgramOptions *mp_options;
    SimulationParameters m_sim_params;
};





#endif /* EXPERIMENT_H_ */
