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
#include "Beam.h"
#include "Detector.h"

class ProgramOptions;

class Experiment : public IParameterized
{
public:
    Experiment();
    Experiment(ProgramOptions *p_options);
    Experiment(const ISample &p_sample, ProgramOptions *p_options=0);
	Experiment(const ISampleBuilder *p_sample_builder, ProgramOptions *p_options=0);
    virtual ~Experiment() {delete mp_sample;}

    //! run a simulation with the current parameter settings
    virtual void runSimulation();

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

    Beam getBeam() const
    {
        return m_beam;
    }

    void setBeam(Beam beam)
    {
        m_beam = beam;
    }

    Detector getDetector() const
    {
        return m_detector;
    }

    void setBeamParameters(double lambda, double alpha_i, double phi_i);

    void setBeamIntensity(double intensity);

    //! add parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const;

    //! set the program options
    void setProgramOptions(ProgramOptions *p_options) { mp_options = p_options; }

    //! set detector parameters using axes of output data
    void setDetectorParameters(const OutputData<double > &output_data);

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! Default implementation only adds the detector axes
    virtual void updateIntensityMapAxes();

    //! Update the sample by calling the sample builder, if present
    void updateSample();

    ISample *mp_sample;
    const ISampleBuilder *mp_sample_builder;
    Detector m_detector;
    Beam m_beam;
    OutputData<double> m_intensity_map;
    bool m_is_normalized;
    ProgramOptions *mp_options;
};





#endif /* EXPERIMENT_H_ */
