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

    /// calculate scattering amplitude for complex wavevectors
    /// @param k_i   incoming wavevector
    /// @param k_f   outgoing wavevector
    virtual complex_t evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const=0;

    /// return number of variable/stochastic parameters
    virtual int getNumberOfStochasticParameters() const { return 0; }

    virtual double getVolume() const;

    virtual double getHeight() const;

    virtual bool isDistributedFormFactor() const { return false; }

    virtual void createDistributedFormFactors(std::vector<IFormFactor *> &form_factors,
            std::vector<double> &probabilities, size_t nbr_samples) const {
        (void)form_factors;
        (void)probabilities;
        (void)nbr_samples;
    }

};

inline double IFormFactor::getVolume() const
{
    cvector_t zero;
    return std::abs(evaluate(zero, zero, 0.0, 0.0));
}

inline double IFormFactor::getHeight() const
{
    double result = std::pow(getVolume(), 1.0/3.0);
    return result;
}

class IFormFactorDecorator : public IFormFactor
{
public:
    IFormFactorDecorator(IFormFactor *p_form_factor) : mp_form_factor(p_form_factor) {}
    virtual ~IFormFactorDecorator();
    virtual IFormFactorDecorator *clone() const=0;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index) { if (mp_form_factor) mp_form_factor->setAmbientRefractiveIndex(refractive_index); }

    virtual double getHeight() const { return mp_form_factor->getHeight(); }

protected:
    IFormFactor *mp_form_factor;
};

inline IFormFactorDecorator::~IFormFactorDecorator()
{
    delete mp_form_factor;
}

class IFormFactorBorn : public IFormFactor
{
public:
    IFormFactorBorn(){}
    virtual ~IFormFactorBorn() {}
	virtual IFormFactorBorn *clone() const=0;

	virtual complex_t evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const;
protected:
    /// evaluate scattering amplitude for complex wavevector
    /// @param q  wavevector transfer \f$q\equiv k_i-k_f\f$
    virtual complex_t evaluate_for_q(const cvector_t &q) const=0;
};

inline complex_t IFormFactorBorn::evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const
{
    (void)alpha_i;
    (void)alpha_f;
    return evaluate_for_q(k_i - k_f);
}

#endif // IFORMFACTOR_H
