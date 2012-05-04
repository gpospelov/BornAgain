/*
 * IDoubleToComplexFunction.h
 *
 *  Created on: Apr 27, 2012
 *      Author: herck
 */

#ifndef IDOUBLETOCOMPLEXFUNCTION_H_
#define IDOUBLETOCOMPLEXFUNCTION_H_

#include "Types.h"

class IDoubleToComplexFunction {
public:
	virtual ~IDoubleToComplexFunction() {}

	virtual complex_t evaluate(double value)=0;
};

class DoubleToComplexFunctionWrapper : public IDoubleToComplexFunction
{
public:
	typedef complex_t (*double_to_complex_t)(double);
	DoubleToComplexFunctionWrapper(double_to_complex_t function) : m_function(function) {}

	virtual complex_t evaluate(double value) { return m_function(value); }

private:
	double_to_complex_t m_function;
};

#endif /* IDOUBLETOCOMPLEXFUNCTION_H_ */
