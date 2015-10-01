// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/IFormFactor.h
//! @brief     Defines and implements pure virtual interface IFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFORMFACTOR_H
#define IFORMFACTOR_H

#include "Units.h"
#include "IMaterial.h"
#include "ISample.h"
#include "Bin.h"
#include "EigenCore.h"

class ILayerRTCoefficients;

//! @class IFormFactor
//! @ingroup formfactors_internal
//! @brief The basic interface for form factors.

class BA_CORE_API_ IFormFactor : public ISample
{
public:
    IFormFactor() {}
    virtual ~IFormFactor() {}

    virtual IFormFactor *clone() const=0;

    //! @{ \internal
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this);}
    //! @}

    //! Passes the refractive index of the ambient material in which this
    //! particle is embedded.
    virtual void setAmbientMaterial(const IMaterial& material) {
        (void)material;
    }

    //! Returns scattering amplitude for complex wavevector bin
    //! @param k_i   incoming wavevector
    //! @param k_f_bin   outgoing wavevector bin
    virtual complex_t evaluate(const cvector_t& k_i, const Bin1DCVector& k_f_bin) const=0;

#ifndef GCCXML_SKIP_THIS
    //! Returns scattering amplitude for matrix interactions
    //! @param k_i   incoming wavevector
    //! @param k_f_bin   outgoing wavevector bin
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i, const Bin1DCVector& k_f_bin) const;
#endif

    //! Returns number of variable/stochastic parameters
    virtual int getNumberOfStochasticParameters() const { return 0; }

    //! Returns the total volume of the particle of this form factor's shape
    virtual double getVolume() const;

    //! Returns the total height of the particle of this form factor's shape
    virtual double getHeight() const;

    //! Returns the total radial size of the particle of this form factor's shape
    virtual double getRadius() const;

    //! Sets reflection/transmission info
    virtual void setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs,
                         const ILayerRTCoefficients *p_out_coeffs) {
        (void)p_in_coeffs;
        (void)p_out_coeffs;
    }
};

class BA_CORE_API_ WavevectorInfo
{
public:
    cvector_t m_ki;
    cvector_t m_kf;
};


#ifndef GCCXML_SKIP_THIS
inline Eigen::Matrix2cd IFormFactor::evaluatePol(const cvector_t& k_i,
                                                 const Bin1DCVector& k_f_bin) const
{
    (void)k_i;
    (void)k_f_bin;
    // Throws to prevent unanticipated behaviour
    throw NotImplementedException("IFormFactor::evaluatePol:"
            " is not implemented by default");
}
#endif

inline double IFormFactor::getVolume() const
{
    cvector_t zero_vector;
    Bin1DCVector zero_vector_bin(zero_vector, zero_vector);
    return std::abs(evaluate(zero_vector, zero_vector_bin));
}

inline double IFormFactor::getHeight() const
{
    return std::pow(getVolume(), 1.0/3.0);
}

inline double IFormFactor::getRadius() const
{
    return std::sqrt(getVolume()/getHeight()/Units::PI);
}

#endif // IFORMFACTOR_H


