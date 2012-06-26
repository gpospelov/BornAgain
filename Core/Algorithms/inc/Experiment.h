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
#include "OutputData.h"
#include "Beam.h"
#include "Detector.h"

class Experiment
{
public:
	Experiment();
	Experiment(ISample *p_sample);
    virtual ~Experiment() {}

    /// Run a simulation with the current parameter settings
    virtual void runSimulation();

    /// Set the sample to be tested
    void setSample(ISample *p_sample);

    /// Get data structure that contains the intensity map on the detector for all scan parameters
    OutputData<double>* getOutputData() const;

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

protected:
    /// Default implementation only adds the detector axes
    virtual void updateIntensityMapAxes();

    ISample *mp_sample;
    Detector m_detector;
    Beam m_beam;
    OutputData<double> m_intensity_map;
};





#endif /* EXPERIMENT_H_ */
