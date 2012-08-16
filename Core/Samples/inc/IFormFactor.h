#ifndef IFORMFACTOR_H
#define IFORMFACTOR_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IFormFactor.h
//! @brief  Definition of IFormFactor and IBornFormFactor
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "Types.h"
#include "ISample.h"


//- -------------------------------------------------------------------
//! @class IFormFactor
//! @brief Definition of IFormfactor interface
//- -------------------------------------------------------------------
class IFormFactor : public ISample
{
public:
    IFormFactor(){}
    virtual ~IFormFactor() {}
    virtual IFormFactor *clone() const=0;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index) { (void)refractive_index; }

    /// calculate scattering amplitude
    /// @param k_i   incoming wavevector
    /// @param k_f   outgoing wavevector
    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const=0;

    /// calculate scattering amplitude for complex wavevectors
    /// @param k_i   incoming wavevector
    /// @param k_f   outgoing wavevector
    virtual complex_t evaluate(cvector_t k_i, cvector_t k_f) const=0;

    /// calculate scattering amplitude for wavevectors with complex z-component
    /// @param k_i   incoming wavevector
    /// @param k_f   outgoing wavevector
    /// @param k_iz  complex z-component of incoming wavevector
    /// @param k_fz  complex z-component of outgoing wavevector
    virtual complex_t evaluateForComplexkz(kvector_t k_i, kvector_t k_f, complex_t k_iz, complex_t k_fz) const=0; // TODO: remove this interface function

    /// return number of variable/stochastic parameters
    virtual int getNumberOfStochasticParameters() const { return 0; }
};

class IFormFactorDecorator : public IFormFactor
{
public:
    IFormFactorDecorator(IFormFactor *p_form_factor) : mp_form_factor(p_form_factor) {}
    virtual ~IFormFactorDecorator() {}
    virtual IFormFactorDecorator *clone() const=0;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index) { if (mp_form_factor) mp_form_factor->setAmbientRefractiveIndex(refractive_index); }
protected:
    IFormFactor *mp_form_factor;
};

class IBornFormFactor : public IFormFactor
{
public:
    IBornFormFactor(){}
    virtual ~IBornFormFactor() {}
	virtual IBornFormFactor *clone() const=0;

	virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const
    {
    	return evaluate_for_q(k_i - k_f);
    }
	virtual complex_t evaluate(cvector_t k_i, cvector_t k_f) const
	{
	    return evaluate_for_q(k_i - k_f);
	}
    virtual complex_t evaluateForComplexkz(kvector_t k_i, kvector_t k_f, complex_t k_iz, complex_t k_fz) const
    {
    	return evaluate_for_complex_qz(k_i - k_f, k_iz-k_fz);
    }

protected:
    /// evaluate scattering amplitude
    /// @param q  wavevector transfer \f$q\equiv k_i-k_f\f$
    virtual complex_t evaluate_for_q(kvector_t q) const;

    /// evaluate scattering amplitude for complex wavevector
    /// @param q  wavevector transfer \f$q\equiv k_i-k_f\f$
    virtual complex_t evaluate_for_q(cvector_t q) const { (void)q; return complex_t(0.0, 0.0); } // TODO: remvoe this default implementation

    /// evaluate scattering amplitude for wavevector q\with complex z-component
    /// @param q  wavevector transfer \f$q\equiv k_i-k_f\f$
    /// @param qz complex z-component of wavevector transfer \f$q_z\equiv k_{iz}-k_{fz}\f$
    virtual complex_t evaluate_for_complex_qz(kvector_t q, complex_t qz) const=0;

};

inline complex_t IBornFormFactor::evaluate_for_q(kvector_t q) const
{
    return evaluate_for_complex_qz(q, q.z());
//    return evaluate_for_q(cvector_t(q.x(), q.y(), q.z()));
}

#endif // IFORMFACTOR_H
