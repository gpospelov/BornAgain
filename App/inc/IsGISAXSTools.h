#ifndef ISGISAXSTOOLS_H_
#define ISGISAXSTOOLS_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IsGISAXSTools.h
//! @brief  Definition of functions and classes for IsGISAXS validation
//! @author herck
//! @date   19.06.2012
#include "Types.h"
#include "NamedVector.h"
#include "IDoubleToComplexFunction.h"

complex_t transmission_fresnel(double alpha_i);
void initialize_angles_sine(NamedVector<double> *p_axis, double start, double end, size_t size);

class ReflectionFresnelFunctionWrapper : public IDoubleToComplexFunction
{
public:
	ReflectionFresnelFunctionWrapper(complex_t refraction_index) : m_refraction_index(refraction_index) {}

	virtual complex_t evaluate(double value) { return reflection_fresnel(value, m_refraction_index); }

private:
	complex_t reflection_fresnel(double alpha_i, complex_t refraction_index);
	complex_t m_refraction_index;
};



#endif /* ISGISAXSTOOLS_H_ */
