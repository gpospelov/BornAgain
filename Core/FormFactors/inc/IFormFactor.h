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

#include "IMaterial.h"
#include "ISample.h"
#include "Bin.h"

#ifndef GCCXML_SKIP_THIS
#include <Eigen/Core>
#endif

//! The basic interface for form factors.

class BA_CORE_API_ IFormFactor : public ISample
{
 public:
    IFormFactor() {}
    virtual ~IFormFactor() {}

    virtual IFormFactor *clone() const=0;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *p_visitor) const {
        p_visitor->visit(this);
    }

    //! Passes the refractive index of the ambient material in which this
    //! particle is embedded.
    virtual void setAmbientMaterial(const IMaterial *p_material) {
        (void)p_material; // to prevent unused-variable warning
    }

    //! Returns scattering amplitude for complex wavevector bin
    //! @param k_i   incoming wavevector
    //! @param k_f_bin   outgoing wavevector bin
    //! @param alpha_i incident angle wrt scattering surface
    //! @param alpha_f outgoing angle wrt scattering surface
    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const=0;

#ifndef GCCXML_SKIP_THIS
    //! Returns scattering amplitude for matrix interactions
    //! @param k_i   incoming wavevector
    //! @param k_f1_bin   outgoing wavevector bin for first eigenmode
    //! @param k_f2_bin   outgoing wavevector bin for second eigenmode
    //! @param alpha_i incident inclination angle wrt scattering surface
    //! @param alpha_f outgoing inclination angle wrt scattering surface
    //! @param phi_f outgoing azimuthal angle wrt scattering surface
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin, Bin1D phi_f_bin) const;
#endif

    //! Returns number of variable/stochastic parameters
    virtual int getNumberOfStochasticParameters() const { return 0; }

    //! Returns the total volume of the particle of this form factor's shape
    virtual double getVolume() const;

    //! Returns the total height of the particle of this form factor's shape
    virtual double getHeight() const;

    //! Returns the total radial size of the particle of this form factor's shape
    virtual double getRadius() const;

    //! Returns true if the form factor is constructed as an average over
    //! multiple simple ones
    virtual bool isDistributedFormFactor() const { return false; }

    //! retrieve a list of simple form factors and their probabilities when the
    //! form factor is a distributed one
    virtual void createDistributedFormFactors(
        std::vector<IFormFactor *>& form_factors,
        std::vector<double>& probabilities,
        size_t nbr_samples) const {
        (void)form_factors;
        (void)probabilities;
        (void)nbr_samples;
    }
};

#ifndef GCCXML_SKIP_THIS
inline Eigen::Matrix2cd IFormFactor::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin, Bin1D phi_f_bin) const
{
    (void)k_i;
    (void)k_f_bin;
    (void)alpha_f_bin;
    (void)phi_f_bin;
    // Throws to prevent unanticipated behaviour
    throw NotImplementedException("IFormFactor::evaluatePol:"
            " is not implemented by default");
}
#endif

inline double IFormFactor::getVolume() const
{
    cvector_t zero_vector;
    Bin1DCVector zero_vector_bin(zero_vector, zero_vector);
    Bin1D zero_bin = { 0.0, 0.0 };
    return std::abs(evaluate(zero_vector, zero_vector_bin, zero_bin));
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


