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

    complex_t kz; //!< z-component of the wavevector in given layer
    complex_t r;  //!< r = R/A - Fresnel reflection coefficient
    complex_t t;  //!< t = T/A - Fresnel transmission coefficient
    complex_t tb; //!< t = T/A - Fresnel transmission coefficient
    complex_t X;  //!<  ratio of amplitudes R/T of the outgoing to the incoming
                  //!<waves in layer
    complex_t R;  //!<  amplitude of the reflected wave in layer
    complex_t T;  //!<  amplitude of the transmitted wave in layer
private:
    Eigen::Vector2cd m_ones_vector;
};

inline ScalarRTCoefficients::ScalarRTCoefficients()
: kz(0), r(0), t(0), tb(0), X(0), R(0), T(0)
{
    m_ones_vector.setOnes();
}

inline Eigen::Vector2cd ScalarRTCoefficients::T1plus() const
{
    return m_ones_vector * T;
}

inline Eigen::Vector2cd ScalarRTCoefficients::R1plus() const
{
    return m_ones_vector * R;
}

inline Eigen::Vector2cd ScalarRTCoefficients::T2plus() const
{
    return m_ones_vector * T;
}

inline Eigen::Vector2cd ScalarRTCoefficients::R2plus() const
{
    return m_ones_vector * R;
}

inline Eigen::Vector2cd ScalarRTCoefficients::T1min() const
{
    return m_ones_vector * T;
}

inline Eigen::Vector2cd ScalarRTCoefficients::R1min() const
{
    return m_ones_vector * R;
}

inline Eigen::Vector2cd ScalarRTCoefficients::T2min() const
{
    return m_ones_vector * T;
}

inline Eigen::Vector2cd ScalarRTCoefficients::R2min() const
{
    return m_ones_vector * R;
}

inline Eigen::Vector2cd ScalarRTCoefficients::getKz() const
{
    return m_ones_vector * kz;
}

#endif /* SCALARRTCOEFFICIENTS_H_ */
