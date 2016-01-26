// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/MathFunctions.h
//! @brief     Define many functions in namespace MathFunctions,
//!              and provide inline implementation for most of them
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include "Types.h"
#include "Units.h"
#include "Numeric.h"

#include <cstdlib>
#include <vector>
#include <cmath>

#include "gsl/gsl_sf_bessel.h"
#include "gsl/gsl_sf_trig.h"
#include "gsl/gsl_sf_expint.h"
#include "gsl/gsl_integration.h"

#include "EigenCore.h"

//! Various mathematical functions.

namespace MathFunctions
{

    BA_CORE_API_ double Gaussian(double value, double average, double std_dev);

    BA_CORE_API_ double IntegratedGaussian(double value, double average, double std_dev);

    BA_CORE_API_ double GenerateNormalRandom(double average, double std_dev);

    BA_CORE_API_ double StandardNormal(double value);

    BA_CORE_API_ double GenerateStandardNormalRandom();

    BA_CORE_API_ double GenerateUniformRandom();

//! Bessel function of the first kind and order 0
    BA_CORE_API_ double Bessel_J0(double value);

//! Bessel function of the first kind and order 1
    BA_CORE_API_ double Bessel_J1(double value);

//! Bessel function  Bessel_J1(x)/x
    BA_CORE_API_ double Bessel_C1(double value);

//! Complex Bessel function of the first kind and order 0
    BA_CORE_API_ complex_t Bessel_J0(const complex_t &value);

//! Complex Bessel function of the first kind and order 1
    BA_CORE_API_ complex_t Bessel_J1(const complex_t &value);

//! Complex Bessel function  Bessel_J1(x)/x
    BA_CORE_API_ complex_t Bessel_C1(const complex_t &value);

//! Sine integral function: \f$Si(x)\equiv\int_0^x du \sin(u)/u\f$
    BA_CORE_API_ double Si(double value);

//! Sinc function: \f$Sinc(x)\equiv\sin(x)/x\f$
    BA_CORE_API_ double Sinc(double value);

//! Complex sinc function: \f$sinc(x)\equiv\sin(x)/x\f$
    BA_CORE_API_ complex_t Sinc(const complex_t &value);

//! Complex tanhc function: \f$tanhc(x)\equiv\tanh(x)/x\f$
    BA_CORE_API_ complex_t tanhc(const complex_t &value);

    BA_CORE_API_ complex_t Laue(const complex_t &value, size_t N);

    enum EFFTDirection { FORWARD_FFT, BACKWARD_FFT };
    BA_CORE_API_ std::vector<complex_t > FastFourierTransform(const std::vector<complex_t > &data, EFFTDirection tcase);

    BA_CORE_API_ std::vector<complex_t > FastFourierTransform(const std::vector<double > &data, EFFTDirection tcase);

    BA_CORE_API_ std::vector<complex_t> ConvolveFFT(const std::vector<double> &signal, const std::vector<double> &resfunc);

//! fast sine calculations (not actually fast)
    double FastSin(const double& x);

//! fast cosine calculation  (not actually fast)
    double FastCos(const double& x);

//! fast complex sine calculation
    complex_t FastSin(const complex_t &x);

//! fast complex cosine calculation
    complex_t FastCos(const complex_t &x);

#ifndef GCCXML_SKIP_THIS
//! computes the norm element-wise
    BA_CORE_API_ Eigen::Matrix2d Norm(const Eigen::Matrix2cd &M);

//! computes the absolute value element-wise
    BA_CORE_API_ Eigen::Matrix2d Abs(const Eigen::Matrix2cd &M);

//! computes the complex conjugate element-wise
    BA_CORE_API_ Eigen::Matrix2cd Conj(const Eigen::Matrix2cd &M);

//! element-wise product
    BA_CORE_API_ Eigen::Matrix2cd ProductByElement(const Eigen::Matrix2cd &left,
                                                   const Eigen::Matrix2cd &right);

//! take element-wise real value
    BA_CORE_API_ Eigen::Matrix2d Real(const Eigen::Matrix2cd &M);
#endif

    BA_CORE_API_ inline bool isnan(double x)
    {
#ifdef _MSC_VER
        return _isnan(x);
#else
        return std::isnan(x);
#endif
    }

    BA_CORE_API_ inline bool isinf(double x)
    {
#ifdef _MSC_VER
        return !_finite(x);
#else
        return std::isinf(x);
#endif
    }

//! Computes complex Bessel function J0(z), using power series and asymptotic expansion 
    BA_CORE_API_ complex_t Bessel_J0_PowSer(const complex_t &value);

//! Computes complex Bessel function J0(z), using power series and asymptotic expansion 
    BA_CORE_API_ complex_t Bessel_J1_PowSer(const complex_t &value);

//! Calculates the geometric series of z to order N
    complex_t geometricSum(complex_t z, int exponent);

} // Namespace MathFunctions

inline double MathFunctions::GenerateNormalRandom(double average, double std_dev)
{
    return GenerateStandardNormalRandom()*std_dev + average;
}

inline double MathFunctions::GenerateUniformRandom()
{
    int random_int = std::rand();
    return (double)random_int / RAND_MAX;
}

inline double MathFunctions::Bessel_J0(double value)
{
    return gsl_sf_bessel_J0(value);
}

inline double MathFunctions::Bessel_J1(double value)
{
    return gsl_sf_bessel_J1(value);
}

inline double MathFunctions::Bessel_C1(double value)
{
    return value > Numeric::double_epsilon ? gsl_sf_bessel_J1(value)/value : 0.5;
}

inline complex_t MathFunctions::Bessel_J0(const complex_t &value)
{
    if(std::imag(value) < Numeric::double_epsilon) {
        return complex_t(Bessel_J0(std::real(value)), 0.0);
    } else {
        return Bessel_J0_PowSer(value);
    }
}

inline complex_t MathFunctions::Bessel_J1(const complex_t &value)
{
    if(std::imag(value) < Numeric::double_epsilon) {
        return complex_t(Bessel_J1(std::real(value)), 0.0);
    } else {
        return Bessel_J1_PowSer(value);
    }
}

inline complex_t MathFunctions::Bessel_C1(const complex_t &value)
{
    if(std::imag(value) < Numeric::double_epsilon) {
        double xv = std::real(value);
        return std::abs(xv) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(xv)/xv : 0.5;
    } else {
        return std::abs(value) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(value)/value : 0.5;
    }
}

inline double MathFunctions::Si(double value)  // int_0^x du Sin(u)/u
{
    return gsl_sf_Si(value);
}

inline double MathFunctions::Sinc(double value)  // Sin(x)/x
{
    return gsl_sf_sinc(value/Units::PI);
}

inline complex_t MathFunctions::Sinc(const complex_t &value)  // Sin(x)/x
{
    if(std::abs(value)<Numeric::double_epsilon)
        return complex_t(1.0, 0.0);
    return std::sin(value)/value;
}

inline complex_t MathFunctions::tanhc(const complex_t &value)  // tanh(x)/x
{
    if(std::abs(value)<Numeric::double_epsilon)
        return complex_t(1.0, 0.0);
    return std::tanh(value)/value;
}

inline complex_t MathFunctions::Laue(const complex_t &value, size_t N) // Exp(iNx/2)*Sin((N+1)x)/Sin(x)
{
    if (N==0)
        return complex_t(1.0, 0.0);
    if(std::abs(value)<Numeric::double_epsilon)
        return complex_t(N+1.0, 0.0);
    return std::exp(complex_t(0.0, 1.0)*value*(double)N/2.0)*std::sin(value*(N+1.0)/2.0)/std::sin(value/2.0);
}

//! fast sine calculations (not actually fast)
inline double MathFunctions::FastSin(const double& x) {
    const double P = 0.225f;
    const double A = 16 * std::sqrt(P);
    const double B = (1 - P) / std::sqrt(P);
    double y = x / (2 * Units::PI);
    y = y - std::floor(y + 0.5);  // y in range -0.5..0.5
    y = A * y * (0.5 - std::abs(y));
    return y * (B + std::abs(y));
}

//! fast cosine calculation  (not actually fast)
inline double MathFunctions::FastCos(const double& x) {
    const double P = 0.225f;
    const double A = 16 * std::sqrt(P);
    const double B = (1 - P) / std::sqrt(P);
    double y = x / (2 * Units::PI)+0.25; // pi/2. shift
    y = y - std::floor(y + 0.5);  // y in range -0.5..0.5
    y = A * y * (0.5 - std::abs(y));
    return y * (B + std::abs(y));
}

//! fast complex sine calculation
inline complex_t MathFunctions::FastSin(const complex_t &x) {
    return complex_t( std::sin(x.real())*std::cosh(x.imag()), std::cos(x.real())*std::sinh(x.imag()));
}

//! fast complex cosine calculation
inline complex_t MathFunctions::FastCos(const complex_t &x) {
    return complex_t( std::cos(x.real())*std::cosh(x.imag()), -1*std::sin(x.real())*std::sinh(x.imag()));
}

#ifndef GCCXML_SKIP_THIS
inline Eigen::Matrix2d MathFunctions::Norm(const Eigen::Matrix2cd &M) {
    Eigen::Matrix2d result;
    result(0,0) = std::norm((complex_t)M(0,0));
    result(0,1) = std::norm((complex_t)M(0,1));
    result(1,0) = std::norm((complex_t)M(1,0));
    result(1,1) = std::norm((complex_t)M(1,1));
    return result;
}

inline Eigen::Matrix2d MathFunctions::Abs(const Eigen::Matrix2cd &M) {
    Eigen::Matrix2d result;
    result(0,0) = std::abs((complex_t)M(0,0));
    result(0,1) = std::abs((complex_t)M(0,1));
    result(1,0) = std::abs((complex_t)M(1,0));
    result(1,1) = std::abs((complex_t)M(1,1));
    return result;
}

inline Eigen::Matrix2cd MathFunctions::Conj(const Eigen::Matrix2cd &M) {
    Eigen::Matrix2cd result;
    result(0,0) = std::conj((complex_t)M(0,0));
    result(0,1) = std::conj((complex_t)M(0,1));
    result(1,0) = std::conj((complex_t)M(1,0));
    result(1,1) = std::conj((complex_t)M(1,1));
    return result;
}

inline Eigen::Matrix2cd MathFunctions::ProductByElement(
        const Eigen::Matrix2cd &left, const Eigen::Matrix2cd &right) {
    Eigen::Matrix2cd result;
    result(0,0) = left(0,0) * right(0,0);
    result(0,1) = left(0,1) * right(0,1);
    result(1,0) = left(1,0) * right(1,0);
    result(1,1) = left(1,1) * right(1,1);
    return result;
}

inline Eigen::Matrix2d MathFunctions::Real(const Eigen::Matrix2cd &M) {
    Eigen::Matrix2d result;
    result(0,0) = ((complex_t)M(0,0)).real();
    result(0,1) = ((complex_t)M(0,1)).real();
    result(1,0) = ((complex_t)M(1,0)).real();
    result(1,1) = ((complex_t)M(1,1)).real();
    return result;
}
#endif

#endif // MATHFUNCTIONS_H


