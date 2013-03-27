// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/InterferenceFunction1DParaCrystal.h
//! @brief     Defines class InterferenceFunction1DParaCrystal.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION1DPARACRYSTAL_H_
#define INTERFERENCEFUNCTION1DPARACRYSTAL_H_

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
	virtual double getKappa() const { return m_kappa; }
    virtual double evaluate(const cvector_t& q) const;
    //TODO: replace these with strategy pattern for different algorithms
    complex_t FTGaussianCorrLength(double qpar) const;
 protected:
	double m_peak_distance;
	double m_width;
	double m_corr_length;
	bool m_use_corr_length;
	double m_kappa;
 private:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();
};

#endif /* INTERFERENCEFUNCTION1DPARACRYSTAL_H_ */
