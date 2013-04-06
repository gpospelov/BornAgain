// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/IFormFactor.h
//! @brief     Defines and partly implements pure virtual interface IFormFactor.
//!            There is no separate implementation file.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFORMFACTOR_H
#define IFORMFACTOR_H

#include "ISample.h"
#include "Bin.h"

//! The basic interface for formfactors.

class IFormFactor : public ISample
{
 public:
    IFormFactor() {}
    virtual ~IFormFactor() {}

    virtual IFormFactor *clone() const=0;

    //! Passes the refractive index of the ambient material in which this particle is embedded.
    virtual void setAmbientRefractiveIndex(const complex_t& refractive_index)
    {
        (void)refractive_index; // to prevent unused-variable warning
    }

    //! Returns scattering amplitude for complex wavevector bin
    //! @param k_i   incoming wavevector
    //! @param k_f_bin   outgoing wavevector bin
    //! @param alpha_i incident angle wrt scattering surface
    //! @param alpha_f outgoing angle wrt scattering surface
    virtual complex_t evaluate(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin,
        double alpha_i, double alpha_f) const=0;

    //! Returns number of variable/stochastic parameters
    virtual int getNumberOfStochasticParameters() const { return 0; }

    //! Returns the total volume of the particle to which this formfactor belongs
    virtual double getVolume() const;

    //! Returns the total height of the particle to which this formfactor belongs
    virtual double getHeight() const;

    //! Returns the total radial size of the particle to which this formfactor belongs
    virtual double getRadius() const;

    //! Returns true if the formfactor is constructed as an average over multiple simple ones
    virtual bool isDistributedFormFactor() const { return false; }

    //! retrieve a list of simple formfactors and their probabilities when the formfactor is a distributed one
    virtual void createDistributedFormFactors(
        std::vector<IFormFactor *>& form_factors,
        std::vector<double>& probabilities,
        size_t nbr_samples) const {
        (void)form_factors;
        (void)probabilities;
        (void)nbr_samples;
    }
};

inline double IFormFactor::getVolume() const
{
    cvector_t zero;
    Bin1DCVector zero_bin(zero, zero);
    return std::abs(evaluate(zero, zero_bin, 0.0, 0.0));
}

inline double IFormFactor::getHeight() const
{
    return std::pow(getVolume(), 1.0/3.0);
}

inline double IFormFactor::getRadius() const
{
    return std::sqrt(getVolume()/getHeight()/M_PI);
}

#endif // IFORMFACTOR_H


