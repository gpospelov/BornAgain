#ifndef DOUBLETOCOMPLEXINTERPOLATINGFUNCTION_H_
#define DOUBLETOCOMPLEXINTERPOLATINGFUNCTION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DoubleToComplexInterpolatingFunction.h
//! @brief  Definition of class that interpolates for a given map
//! @author herck
//! @date   01.05.2012

#include "IDoubleToComplexFunction.h"
#include <map>


class DoubleToComplexInterpolatingFunction : public IDoubleToComplexFunction
{
public:
	virtual ~DoubleToComplexInterpolatingFunction();
	DoubleToComplexInterpolatingFunction(const std::map<double, complex_t> &value_map);
	virtual DoubleToComplexInterpolatingFunction *clone() const;

    virtual complex_t evaluate(double value);

protected:
	std::map<double, complex_t> m_value_map;
	double m_lower_limit;
	double m_upper_limit;
};

#endif /* DOUBLETOCOMPLEXINTERPOLATINGFUNCTION_H_ */
