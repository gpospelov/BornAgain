// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ILayerRTCoefficients.h
//! @brief     Defines class ILayerRTCoefficients.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ILAYERRTCOEFFICIENTS_H_
#define ILAYERRTCOEFFICIENTS_H_

#include <Eigen/Core>

class ILayerRTCoefficients
{
public:
    ILayerRTCoefficients();
    virtual ~ILayerRTCoefficients() {}

    //! The following functions return the transmitted and reflected amplitudes
    //! for different incoming beam polarizations and eigenmodes
    Eigen::Vector2cd T1plus() const;
    Eigen::Vector2cd R1plus() const;
    Eigen::Vector2cd T2plus() const;
    Eigen::Vector2cd R2plus() const;
    Eigen::Vector2cd T1min() const;
    Eigen::Vector2cd R1min() const;
    Eigen::Vector2cd T2min() const;
    Eigen::Vector2cd R2min() const;

    Eigen::Vector2cd lambda; // positive eigenvalues of transfer matrix
    Eigen::Vector2cd kz; //!< z-part of the two wavevector eigenmodes
    Eigen::Vector4cd phi_psi_plus; //!< boundary values for up-polarization
    Eigen::Vector4cd phi_psi_min; //!< boundary values for up-polarization
    Eigen::Matrix4cd T1m; //!< matrix selecting the transmitted part of
                          //!< the first eigenmode
    Eigen::Matrix4cd R1m; //!< matrix selecting the reflected part of
                          //!< the first eigenmode
    Eigen::Matrix4cd T2m; //!< matrix selecting the transmitted part of
                          //!< the second eigenmode
    Eigen::Matrix4cd R2m; //!< matrix selecting the reflected part of
                          //!< the second eigenmode
    Eigen::Matrix2cd m_scatt_matrix; //!< scattering matrix
    complex_t m_a; //!< polarization independent part of scattering matrix
    complex_t m_b_mag; //!< magnitude of magnetic interaction term
    complex_t m_bz; //!< z-part of magnetic interaction term
    double m_kt; //!< wavevector length times thickness of layer for use when
                 //!< lambda=0
};


#endif /* ILAYERRTCOEFFICIENTS_H_ */
