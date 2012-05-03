/*
 * DoubleToComplexInterpolatingFunction.h
 *
 *  Created on: Apr 27, 2012
 *      Author: herck
 */

#ifndef DOUBLETOCOMPLEXINTERPOLATINGFUNCTION_H_
#define DOUBLETOCOMPLEXINTERPOLATINGFUNCTION_H_

#include "IDoubleToComplexFunction.h"
#include <map>

class DoubleToComplexInterpolatingFunction : public IDoubleToComplexFunction
{
public:
	virtual ~DoubleToComplexInterpolatingFunction();
	DoubleToComplexInterpolatingFunction(std::map<double, complex_t> value_map);

    virtual complex_t evaluate(double value);

protected:
	std::map<double, complex_t> m_value_map;
	double m_lower_limit;
	double m_upper_limit;
};

#endif /* DOUBLETOCOMPLEXINTERPOLATINGFUNCTION_H_ */
