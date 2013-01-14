#ifndef BIN_H_
#define BIN_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Bin.h
//! @brief  Definition of Bin classes
//! @author Scientific Computing Group at FRM II
//! @date   Dec 10, 2012

#include "Numeric.h"
#include "Types.h"

//- -------------------------------------------------------------------
//! @class Bin1D
//! @brief Definition of Bin1D class that stores the bounds of a
//! one-dimensional bin
//- -------------------------------------------------------------------
struct Bin1D
{
    double m_lower;  //!< lower bound of the bin
    double m_upper;  //!< upper bound of the bin
    double getMidPoint() const { return (m_lower + m_upper)/2.0; }
};

//- -------------------------------------------------------------------
//! @class Bin1DCVector
//! @brief Definition of Bin1DCVector class that stores a 1 dimensional
//! range of cvector_t's
//- -------------------------------------------------------------------
struct Bin1DCVector
{
    Bin1DCVector() : m_q_lower(), m_q_upper() {}
    Bin1DCVector(const cvector_t &lower, const cvector_t &upper)
        : m_q_lower(lower), m_q_upper(upper) {}
    Bin1DCVector(double wavelength, const Bin1D &alpha_bin, const Bin1D &phi_bin);
    cvector_t getMidPoint() const { return (m_q_lower + m_q_upper)/2.0; }
    cvector_t getDelta() const { return m_q_upper - m_q_lower; }
    cvector_t m_q_lower;  //!< lower bound of the bin
    cvector_t m_q_upper;  //!< upper bound of the bin
};

//! equality operator for bins
inline bool operator==(const Bin1D &left, const Bin1D &right)
{
    if (std::abs(left.m_lower - right.m_lower) > Numeric::double_epsilon) return false;
    if (std::abs(left.m_upper - right.m_upper) > Numeric::double_epsilon) return false;
    return true;
}

//! inequality operator for bins
inline bool operator!=(const Bin1D &left, const Bin1D &right) {
    return !(left==right);
}

//! creation on Bin1DCVector from alpha and phi bins
inline Bin1DCVector::Bin1DCVector(double wavelength, const Bin1D &alpha_bin, const Bin1D &phi_bin) : m_q_lower(), m_q_upper()
{
    m_q_lower.setLambdaAlphaPhi(wavelength, alpha_bin.m_lower, phi_bin.m_lower);
    m_q_upper.setLambdaAlphaPhi(wavelength, alpha_bin.m_upper, phi_bin.m_upper);
}

#endif /* BIN_H_ */
