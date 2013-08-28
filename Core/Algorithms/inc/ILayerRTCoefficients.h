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
    virtual ~ILayerRTCoefficients() {}

    //! The following functions return the transmitted and reflected amplitudes
    //! for different incoming beam polarizations and eigenmodes
    virtual Eigen::Vector2cd T1plus() const=0;
    virtual Eigen::Vector2cd R1plus() const=0;
    virtual Eigen::Vector2cd T2plus() const=0;
    virtual Eigen::Vector2cd R2plus() const=0;
    virtual Eigen::Vector2cd T1min() const=0;
    virtual Eigen::Vector2cd R1min() const=0;
    virtual Eigen::Vector2cd T2min() const=0;
    virtual Eigen::Vector2cd R2min() const=0;
    //! Returns z-part of the two wavevector eigenmodes
    virtual Eigen::Vector2cd getKz() const=0;
};


#endif /* ILAYERRTCOEFFICIENTS_H_ */
