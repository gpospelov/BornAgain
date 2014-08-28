// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/Bin.h
//! @brief     Defines structs Bin1D, Bin1DCVector
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BIN_H_
#define BIN_H_

#include "Numeric.h"
#include "Types.h"
#include "WinDllMacros.h"

//! @class Bin1D
//! @ingroup tools_internal
//! @brief One dimensional bin with left and right bounds.

#include <iostream>

struct BA_CORE_API_ Bin1D
{
    Bin1D() {}
    Bin1D(double lower, double upper) : m_lower(lower), m_upper(upper) {}
    double m_lower;  //!< lower bound of the bin
    double m_upper;  //!< upper bound of the bin
    double getMidPoint() const { return (m_lower + m_upper)/2.0; }
    double getBinSize() const
    {
        return m_upper - m_lower;
    }
};


//! @class Bin1DCVector
//! @ingroup tools_internal
//! @brief An one-dimensional range of cvector_t's

struct BA_CORE_API_ Bin1DCVector
{
    Bin1DCVector() : m_q_lower(), m_q_upper() {}
    Bin1DCVector(const cvector_t& lower, const cvector_t& upper)
        : m_q_lower(lower), m_q_upper(upper) {}
    Bin1DCVector(double wavelength, const Bin1D& alpha_bin,
                 const Bin1D& phi_bin);
    cvector_t getMidPoint() const { return (m_q_lower + m_q_upper)/2.0; }
    cvector_t getDelta() const
    {
        return m_q_upper - m_q_lower;
    }
    cvector_t m_q_lower;  //!< lower bound of the bin
    cvector_t m_q_upper;  //!< upper bound of the bin
};

//inline bool operator==(const Bin1D& left, const Bin1D& right)
//{
//    if (std::abs(left.m_lower - right.m_lower) > Numeric::double_epsilon) {
//        return false;
//    }
//    if (std::abs(left.m_upper - right.m_upper) > Numeric::double_epsilon) {
//        return false;
//    }
//    return true;
//}

//inline bool operator!=(const Bin1D& left, const Bin1D& right) {
//    return !(left==right);
//}

//! creation on Bin1DCVector from alpha and phi bins
inline Bin1DCVector::Bin1DCVector(double wavelength, const Bin1D& alpha_bin,
           const Bin1D& phi_bin) : m_q_lower(), m_q_upper()
{
    m_q_lower.setLambdaAlphaPhi(wavelength, alpha_bin.m_lower, phi_bin.m_lower);
    m_q_upper.setLambdaAlphaPhi(wavelength, alpha_bin.m_upper, phi_bin.m_upper);
}

#endif /* BIN_H_ */


