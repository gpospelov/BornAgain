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
//! @file   ISimulation.h
//! @brief  Definition of ISimulation class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "ISample.h"
#include "OutputData.h"

class Experiment
{
public:
	Experiment();
	Experiment(ISample *p_sample);
    virtual ~Experiment() {}

    /// Run a simulation with the current parameter settings
    void runSimulation();

    /// Set the sample to be tested
    void setSample(ISample *p_sample);

    /// Set data structure that will contain the intensity map on the detector
    void setOutputData(OutputData<double> *p_data);

protected:
    ISample *mp_sample;
//    Detector *mp_detector;
//    Beam *mp_beam;
    OutputData<double> *mp_intensity_map;
};





#endif /* EXPERIMENT_H_ */
