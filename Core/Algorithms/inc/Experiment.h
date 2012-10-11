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

class Experiment : public IParameterized
{
public:
	Experiment();
	Experiment(ISample *p_sample);
	Experiment(ISampleBuilder *p_sample_builder);
    virtual ~Experiment() {}

    //! run a simulation with the current parameter settings
    virtual void runSimulation();

    //! normalize the detector counts
    virtual void normalize();

    //! set the sample to be tested
    void setSample(ISample *p_sample);

    //! get the sample
    ISample *getSample() { return mp_sample; }
    const ISample *getSample() const { return mp_sample; }

    //! set the sample builder
    void setSampleBuilder(ISampleBuilder *p_sample_builder);

    //! get data structure that contains the intensity map on the detector for all scan parameters
    OutputData<double>* getOutputDataClone() const;

    const OutputData<double>* getOutputData() const;

    const OutputData<double>* getOutputDataMask() const;

    void setOutputDataMask(size_t n_chunks_total=1, size_t n_chunk=0);

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

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! Default implementation only adds the detector axes
    virtual void updateIntensityMapAxes();

    //! Update the sample by calling the sample builder, if present
    void updateSample();

    ISample *mp_sample;
    ISampleBuilder *mp_sample_builder;
    Detector m_detector;
    Beam m_beam;
    OutputData<double> m_intensity_map;
    OutputData<double> m_current_output_data_mask;
    bool m_is_normalized;
};





#endif /* EXPERIMENT_H_ */
