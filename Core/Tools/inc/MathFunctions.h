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

//! sinc function: \f$sinc(x)\equiv\sin(x)/x\f$
    BA_CORE_API_ double sinc(double value);

//! Complex sinc function: \f$sinc(x)\equiv\sin(x)/x\f$
    BA_CORE_API_ complex_t sinc(const complex_t &value);

//! Complex tanhc function: \f$tanhc(x)\equiv\tanh(x)/x\f$
    BA_CORE_API_ complex_t tanhc(const complex_t &value);

    BA_CORE_API_ complex_t Laue(const complex_t &value, size_t N);

    enum EFFTDirection { FORWARD_FFT, BACKWARD_FFT };
    BA_CORE_API_ std::vector<complex_t > FastFourierTransform(const std::vector<complex_t > &data, EFFTDirection tcase);

    BA_CORE_API_ std::vector<complex_t > FastFourierTransform(const std::vector<double > &data, EFFTDirection tcase);

    BA_CORE_API_ std::vector<complex_t> ConvolveFFT(const std::vector<double> &signal, const std::vector<double> &resfunc);

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


#endif // MATHFUNCTIONS_H
