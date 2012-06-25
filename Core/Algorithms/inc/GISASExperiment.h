#ifndef GISASEXPERIMENT_H_
#define GISASEXPERIMENT_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   GISASExperiment.h
//! @brief  Definition of GISASExperiment class
//! @author Scientific Computing Group at FRM II
//! @date   20.06.2012


#include "Experiment.h"

class GISASExperiment : public Experiment
{
public:
	GISASExperiment();

	virtual void runSimulation();

	void setDetectorParameters(double phi_f_min, double phi_f_max, size_t n_phi,
	        double alpha_f_min, double alpha_f_max, size_t n_alpha, bool isgisaxs_style=false);
protected:
//	virtual void updateIntensityMapAxes();
private:
	void initializeAnglesIsgisaxs(NamedVector<double> *p_axis, double start, double end, size_t size);
};



#endif /* GISASEXPERIMENT_H_ */
