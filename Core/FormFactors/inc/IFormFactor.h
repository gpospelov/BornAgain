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
#include "MemberFunctionIntegrator.h"
#include "MathFunctions.h"


//- -------------------------------------------------------------------
//! @class IFormFactor
//! @brief Definition of IFormfactor interface
//- -------------------------------------------------------------------
class IFormFactor : public ISample
{
public:
    IFormFactor() : m_use_large_bin_approximation(false), m_bin_qy(0.0), m_bin_qz(0.0) {}
    virtual ~IFormFactor() {}
    virtual IFormFactor *clone() const=0;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index) { (void)refractive_index; }

    //! calculate scattering amplitude for complex wavevectors
    //! @param k_i   incoming wavevector
    //! @param k_f   outgoing wavevector
    virtual complex_t evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const=0;

    //! return number of variable/stochastic parameters
    virtual int getNumberOfStochasticParameters() const { return 0; }

    //! propagate the bin sizes to the form factor to possibly enable large bin size approximations
    virtual void setBinSizes(double delta_qy, double delta_qz);

    virtual double getVolume() const;

    virtual double getHeight() const;

    virtual double getRadius() const;

    virtual bool isDistributedFormFactor() const { return false; }

    virtual void createDistributedFormFactors(std::vector<IFormFactor *> &form_factors,
            std::vector<double> &probabilities, size_t nbr_samples) const {
        (void)form_factors;
        (void)probabilities;
        (void)nbr_samples;
    }

    static double CalculateBinSize(double lambda, double phi_range, size_t n_phi);

protected:
    bool m_use_large_bin_approximation;  //!< indicates if large bin size approximation should be used
    double m_bin_qy, m_bin_qz;  //!< the sizes of the bins in q space
};

inline void IFormFactor::setBinSizes(double delta_qy, double delta_qz)
{
    m_bin_qy = delta_qy;
    m_bin_qz = delta_qz;
    if (m_bin_qy > M_PI/2.0/getRadius() || m_bin_qz > M_PI/2.0/getHeight()) {
        m_use_large_bin_approximation = true;
    }
    else {
        m_use_large_bin_approximation = false;
    }
}

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

inline double IFormFactor::getRadius() const
{
    double result = std::sqrt(getVolume()/getHeight());
    return result;
}

inline double IFormFactor::CalculateBinSize(double lambda, double phi_range,
        size_t n_phi)
{
    double k = 2.0*M_PI/lambda;
    return k*phi_range/(n_phi-1.0);
}

class IFormFactorDecorator : public IFormFactor
{
public:
    IFormFactorDecorator(IFormFactor *p_form_factor) : mp_form_factor(p_form_factor) {}
    virtual ~IFormFactorDecorator();
    virtual IFormFactorDecorator *clone() const=0;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index) { if (mp_form_factor) mp_form_factor->setAmbientRefractiveIndex(refractive_index); }

    //! propagate the bin sizes to the form factor to possibly enable large bin size approximations
    virtual void setBinSizes(double delta_qy, double delta_qz) {
        IFormFactor::setBinSizes(delta_qy, delta_qz);
        mp_form_factor->setBinSizes(delta_qy, delta_qz);
    }

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
    IFormFactorBorn() {}
    virtual ~IFormFactorBorn() {}
	virtual IFormFactorBorn *clone() const=0;

	virtual complex_t evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const;

	//! evaluate scattering amplitude for large bin sizes
	virtual complex_t evaluateForLargeBins(const cvector_t &q) const;
protected:
    //! evaluate scattering amplitude for complex wavevector
    //! @param q  wavevector transfer \f$q\equiv k_i-k_f\f$
    virtual complex_t evaluate_for_q(const cvector_t &q) const=0;

    //! override volume getter to avoid infinite loop caused by big bin approximation
    virtual double getVolume() const;
private:
    double bigRadialPart(double qR, void *params) const;
    double bigZPart(double qH2, void *params) const;
};

inline complex_t IFormFactorBorn::evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const
{
    (void)alpha_i;
    (void)alpha_f;
    if (m_use_large_bin_approximation) {
        return evaluateForLargeBins(k_i - k_f);
    }
    return evaluate_for_q(k_i - k_f);
}

inline complex_t IFormFactorBorn::evaluateForLargeBins(const cvector_t& q) const
{
    // z parameters
    complex_t qzH2 = q.z()*getHeight()/2.0;
    double qzH2_d = std::abs(qzH2);
    double effective_bin_size_h = m_bin_qz*getHeight();

    // radial parameters
    double qrR = std::abs(q.magxy())*getRadius();
    double effective_bin_size_r = m_bin_qy*getRadius();
    double qRmin = qrR - effective_bin_size_r/2.0;
    double qRmax = qrR + effective_bin_size_r/2.0;

    // phase from the height of the particle
    complex_t z_phase = std::exp(complex_t(0.0, 1.0)*qzH2);

    // modulus of the height of the particle
    double z_average_intensity = (bigZPart(qzH2_d + effective_bin_size_h/2.0, (void *)0)
            - bigZPart(qzH2_d - effective_bin_size_h/2.0, (void *)0))/effective_bin_size_h;
    double z_modulus = std::sqrt(z_average_intensity);

    // modulus of the radial part
    MemberFunctionIntegrator<IFormFactorBorn>::mem_function p_mf = &IFormFactorBorn::bigRadialPart;
    MemberFunctionIntegrator<IFormFactorBorn> integrator(p_mf, this);
    double average_intensity = integrator.integrate(qRmin, qRmax, (void*)0)/effective_bin_size_r;
    double radial_part = std::sqrt(average_intensity);

    return getVolume()*radial_part*z_modulus*z_phase;
}

inline double IFormFactorBorn::getVolume() const
{
    cvector_t zero;
    return std::abs(evaluate_for_q(zero));
}

#endif // IFORMFACTOR_H
