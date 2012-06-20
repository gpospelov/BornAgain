#ifndef INTERFERENCEFUNCTION1DPARACRYSTAL_H_
#define INTERFERENCEFUNCTION1DPARACRYSTAL_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   InterferenceFunction1DParaCrystal.h
//! @brief  Definition of InterferenceFunction1DParaCrystal class
//! @author herck
//! @date   19.06.2012

#include "IInterferenceFunction.h"

class InterferenceFunction1DParaCrystal : public IInterferenceFunction
{
public:
	InterferenceFunction1DParaCrystal(double peak_distance, double width, double corr_length=0.0);
	virtual ~InterferenceFunction1DParaCrystal() {}

	virtual double evaluate(kvector_t q) const;
protected:
	double m_peak_distance;
	double m_width;
	double m_corr_length;
	bool m_use_corr_length;
private:
	// replace these with strategy pattern for different algorithms
	complex_t FTGaussianCorrLength(double qpar) const;
};



#endif /* INTERFERENCEFUNCTION1DPARACRYSTAL_H_ */
