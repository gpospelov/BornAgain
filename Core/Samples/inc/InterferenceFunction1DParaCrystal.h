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
//! @author Scientific Computing Group at FRM II
//! @date   19.06.2012

#include "IInterferenceFunction.h"

class InterferenceFunction1DParaCrystal : public IInterferenceFunction
{
public:
	InterferenceFunction1DParaCrystal(double peak_distance, double width, double corr_length=0.0);
	virtual ~InterferenceFunction1DParaCrystal() {}
	virtual InterferenceFunction1DParaCrystal *clone() const {
	    InterferenceFunction1DParaCrystal *p_clone = new InterferenceFunction1DParaCrystal(m_peak_distance, m_width, m_corr_length);
	    p_clone->setKappa(m_kappa);
	    return p_clone;
	}

	void setKappa(double kappa) { m_kappa = kappa; }
	double getKappa() const { return m_kappa; }
    virtual double evaluate(const cvector_t &q) const;
    //TODO: replace these with strategy pattern for different algorithms
    complex_t FTGaussianCorrLength(double qpar) const;
protected:
	double m_peak_distance;
	double m_width;
	double m_corr_length;
	bool m_use_corr_length;
	double m_kappa;
private:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();
};



#endif /* INTERFERENCEFUNCTION1DPARACRYSTAL_H_ */
