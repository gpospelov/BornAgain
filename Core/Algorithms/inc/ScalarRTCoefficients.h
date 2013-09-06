// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ScalarRTCoefficients.h
//! @brief     Defines class ScalarRTCoefficients.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SCALARRTCOEFFICIENTS_H_
#define SCALARRTCOEFFICIENTS_H_

#include "ILayerRTCoefficients.h"
#include "Types.h"

//! Specular reflection and transmission coefficients in a layer in case
//! of scalar interactions between the layers and the scattered particle
class ScalarRTCoefficients : public ILayerRTCoefficients
{
public:
    ScalarRTCoefficients();
    virtual ~ScalarRTCoefficients() {}

    //! The following functions return the transmitted and reflected amplitudes
    //! for different incoming beam polarizations and eigenmodes
    virtual Eigen::Vector2cd T1plus() const;
    virtual Eigen::Vector2cd R1plus() const;
    virtual Eigen::Vector2cd T2plus() const;
    virtual Eigen::Vector2cd R2plus() const;
    virtual Eigen::Vector2cd T1min() const;
    virtual Eigen::Vector2cd R1min() const;
    virtual Eigen::Vector2cd T2min() const;
    virtual Eigen::Vector2cd R2min() const;
    //! Returns z-part of the two wavevector eigenmodes
    virtual Eigen::Vector2cd getKz() const;

    //! Scalar value getters; these throw errors by default as they should only
    //! be used when the derived object is really scalar
    virtual complex_t getScalarT() const;
    virtual complex_t getScalarR() const;
    virtual complex_t getScalarKz() const {
        return kz;
    }

    complex_t lambda;         //!< positive eigenvalue of transfer matrix
    complex_t kz;             //!< z-part of the wavevector
    Eigen::Vector2cd phi_psi; //!< boundary values of the amplitude
    Eigen::Matrix2cd l;       //!< transfer matrix

private:
    Eigen::Vector2cd m_plus;
    Eigen::Vector2cd m_min;
};

inline ScalarRTCoefficients::ScalarRTCoefficients()
: lambda(0), kz(0)
{
    m_plus(0) = complex_t(1.0, 0.0);
    m_plus(1) = 0.0;
    m_min(0) = 0.0;
    m_min(1) = complex_t(1.0, 0.0);
}

inline Eigen::Vector2cd ScalarRTCoefficients::T1plus() const
{
    return Eigen::Vector2cd::Zero();
}

inline Eigen::Vector2cd ScalarRTCoefficients::R1plus() const
{
    return Eigen::Vector2cd::Zero();
}

inline Eigen::Vector2cd ScalarRTCoefficients::T2plus() const
{
    return m_plus * getScalarT();
}

inline Eigen::Vector2cd ScalarRTCoefficients::R2plus() const
{
    return m_plus * getScalarR();
}

inline Eigen::Vector2cd ScalarRTCoefficients::T1min() const
{
    return m_min * getScalarT();
}

inline Eigen::Vector2cd ScalarRTCoefficients::R1min() const
{
    return m_min * getScalarR();
}

inline Eigen::Vector2cd ScalarRTCoefficients::T2min() const
{
    return Eigen::Vector2cd::Zero();
}

inline Eigen::Vector2cd ScalarRTCoefficients::R2min() const
{
    return Eigen::Vector2cd::Zero();
}

inline Eigen::Vector2cd ScalarRTCoefficients::getKz() const
{
    return (m_plus+m_min) * kz;
}

inline complex_t ScalarRTCoefficients::getScalarR() const
{
    if (lambda==0.0) {
        if (phi_psi(1)==0.0) {
            return -1.0;
        }
        else return 0.0;
    }
    return (phi_psi(1)+phi_psi(0)/lambda)/2.0;}

inline complex_t ScalarRTCoefficients::getScalarT() const
{
    if (lambda==0.0) {
        if (phi_psi(1)==0.0) {
            return 1.0;
        }
        else return phi_psi(1);
    }
    return (phi_psi(1)-phi_psi(0)/lambda)/2.0;
}

#endif /* SCALARRTCOEFFICIENTS_H_ */
