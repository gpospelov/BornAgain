#ifndef IDOUBLETOCOMPLEXFUNCTION_H_
#define IDOUBLETOCOMPLEXFUNCTION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IDoubleToComplexFunction.h
//! @brief  Definition of HomogeneousMaterial class
//! @author herck
//! @date   27.04.2012

#include "Types.h"


class IDoubleToComplexFunction
{
public:
	virtual ~IDoubleToComplexFunction() {}
	virtual IDoubleToComplexFunction *clone() const=0;

	virtual complex_t evaluate(double value)=0;
};


class DoubleToComplexFunctionWrapper : public IDoubleToComplexFunction
{
public:
	typedef complex_t (*double_to_complex_t)(double);
	DoubleToComplexFunctionWrapper(double_to_complex_t function) : m_function(function) {}
	virtual DoubleToComplexFunctionWrapper *clone() const {
	    return new DoubleToComplexFunctionWrapper(m_function);
	}

	virtual complex_t evaluate(double value) { return m_function(value); }

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    DoubleToComplexFunctionWrapper(const DoubleToComplexFunctionWrapper &);
    DoubleToComplexFunctionWrapper &operator=(const DoubleToComplexFunctionWrapper &);

	double_to_complex_t m_function;
};

#endif /* IDOUBLETOCOMPLEXFUNCTION_H_ */
