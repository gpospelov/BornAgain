#ifndef BEAM_H_
#define BEAM_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Beam.h
//! @brief  Definition of Beam class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 21, 2012

#include "Types.h"
#include "IParameterized.h"

class Beam : public IParameterized
{
public:
	Beam();
	virtual ~Beam() {}

	cvector_t getCentralK() const { return m_central_k; }

	void setCentralK(const cvector_t &k_i);
	void setCentralK(double lambda, double alpha_i, double phi_i);

	double getIntensity() const { return m_intensity; }

	void setIntensity(double intensity) { m_intensity = intensity; }

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

	cvector_t m_central_k;
	double m_intensity;
};


#endif /* BEAM_H_ */
