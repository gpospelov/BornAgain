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


//- -------------------------------------------------------------------
//! @class IFormFactor
//! @brief Definition of IFormfactor interface
//- -------------------------------------------------------------------
class IFormFactor
{
public:
    virtual ~IFormFactor() {}

    /// calculate scattering amplitude
    ///
    /// calculate scattering amplitude
    /// @param k_i   incoming wavevector
    /// @param k_f   outgoing wavevector
    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const=0;

    /// return number of variable/stochastic parameters
    virtual int getNumberOfStochasticParameters() { return 0; }
};

class IBornFormFactor : public IFormFactor
{
public:
	virtual ~IBornFormFactor() {}

    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const
    {
    	return evaluate_for_q(k_i - k_f);
    }
protected:
    /// evaluate scattering amplitude
    /// @param q  wavevector transfer \f$q\equiv k_i-k_f\f$
    virtual complex_t evaluate_for_q(kvector_t q) const=0;
};

#endif // IFORMFACTOR_H
