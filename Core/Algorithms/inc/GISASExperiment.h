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
#include "DetectorParameters.h"
#include "IResolutionFunction2D.h"


class GISASExperiment : public Experiment
{
public:
    GISASExperiment();
    GISASExperiment(ProgramOptions *p_options);

	virtual void runSimulation();

    virtual void runSimulationElement(size_t index);


	//! normalize the calculated intensity

    //! This normalization assumes that the intensity map contains total differential scattering cross sections
    //! (so not the cross section per scattering particle as is usual)
    virtual void normalize();

    using Experiment::setDetectorParameters;
    void setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max,
            size_t n_alpha, double alpha_f_min, double alpha_f_max, bool isgisaxs_style=false);

    void setDetectorParameters(const DetectorParameters &params);

    void setDetectorResolutionFunction(IResolutionFunction2D *p_resolution_function);

	void smearIntensityFromZAxisTilting();

    virtual GISASExperiment *clone() const;

    static const std::string PHI_AXIS_NAME;
    static const std::string ALPHA_AXIS_NAME;
protected:
    // hiding copy constructor and disabling assignment operator
    GISASExperiment(const GISASExperiment &other);
    GISASExperiment &operator=(const GISASExperiment &);

private:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

	double getSolidAngle(size_t index) const;
	double deltaAlpha(double alpha, double zeta) const;
	double deltaPhi(double alpha, double phi, double zeta);
	void createZetaAndProbVectors(std::vector<double> &zetas, std::vector<double> &probs, size_t nbr_zetas, double zeta_sigma);
	void addToIntensityMap(double alpha, double phi, double value);
};

#endif /* GISASEXPERIMENT_H_ */
