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
//!
//! IFormFactor declares the basic interface for formfactors
//- -------------------------------------------------------------------
class IFormFactor : public ISample
{
public:
    IFormFactor() : m_use_large_bin_approximation(false), m_bin_qy(0.0), m_bin_qz(0.0) {}
    virtual ~IFormFactor() {}

    //! create a clone of this formfactor
    virtual IFormFactor *clone() const=0;

    //! pass the refractive index of the ambient material in which this particle is embedded
    virtual void setAmbientRefractiveIndex(complex_t refractive_index) { (void)refractive_index; }

    //! calculate scattering amplitude for complex wavevectors
    //! @param k_i   incoming wavevector
    //! @param k_f   outgoing wavevector
    virtual complex_t evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const=0;

    //! return number of variable/stochastic parameters
    virtual int getNumberOfStochasticParameters() const { return 0; }

    //! propagate the bin sizes to the form factor to possibly enable large bin size approximations
    virtual void setBinSizes(double delta_qy, double delta_qz);

    //! get the total volume of the particle to which this formfactor belongs
    virtual double getVolume() const;

    //! get the total height of the particle to which this formfactor belongs
    virtual double getHeight() const;

    //! get the total radial size of the particle to which this formfactor belongs
    virtual double getRadius() const;

    //! find out if the formfactor is constructed as an average over multiple simple ones
    virtual bool isDistributedFormFactor() const { return false; }

    //! retrieve a list of simple formfactors and their probabilities when the formfactor is a distributed one
    virtual void createDistributedFormFactors(std::vector<IFormFactor *> &form_factors,
            std::vector<double> &probabilities, size_t nbr_samples) const {
        (void)form_factors;
        (void)probabilities;
        (void)nbr_samples;
    }

    //! static method to calculate bin sizes in reciprocal space
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

#endif // IFORMFACTOR_H
