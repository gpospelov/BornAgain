#ifndef ISGISAXSMORPHOLOGYFILEINTERFERENCEFUNCTION_H_
#define ISGISAXSMORPHOLOGYFILEINTERFERENCEFUNCTION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IsGISAXSMorphologyFileInterferenceFunction.h
//! @brief  Definition of IsGISAXSMorphologyFileInterferenceFunction class
//! @author Scientific Computing Group at FRM II
//! @date   Jan 7, 2013

#include "IInterferenceFunction.h"

class IsGISAXSMorphologyFileInterferenceFunction : public IInterferenceFunction
{
public:
    IsGISAXSMorphologyFileInterferenceFunction(double pos_x, double pos_y, double cutoff);
    virtual ~IsGISAXSMorphologyFileInterferenceFunction() {}

    virtual double evaluate(const cvector_t &q) const;
    virtual IsGISAXSMorphologyFileInterferenceFunction *clone() const;
protected:
    double m_pos_x;
    double m_pos_y;
    double m_cutoff;
    double m_hann_value;
private:
    double hannFunction(double x, double y, double cutoff);
};

#endif /* ISGISAXSMORPHOLOGYFILEINTERFERENCEFUNCTION_H_ */
