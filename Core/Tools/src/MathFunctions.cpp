// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/MathFunctions.cpp
//! @brief     Implements functions in namespace MathFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MathFunctions.h"

#include <cmath>
#include <cstring>
#include <stdexcept>
#include <fftw3.h>
#include <gsl/gsl_sf_erf.h>
#include <gsl/gsl_randist.h>
#include "gsl/gsl_sf_bessel.h"
#include "gsl/gsl_sf_trig.h"
#include "gsl/gsl_sf_expint.h"
#include "gsl/gsl_integration.h"


double MathFunctions::GenerateNormalRandom(double average, double std_dev)
{
    return GenerateStandardNormalRandom()*std_dev + average;
}

double MathFunctions::GenerateUniformRandom()
{
    int random_int = std::rand();
    return (double)random_int / RAND_MAX;
}

double MathFunctions::Bessel_J0(double value)
{
    return gsl_sf_bessel_J0(value);
}

double MathFunctions::Bessel_J1(double value)
{
    return gsl_sf_bessel_J1(value);
}

double MathFunctions::Bessel_C1(double value)
{
    return value > Numeric::double_epsilon ? gsl_sf_bessel_J1(value)/value : 0.5;
}

complex_t MathFunctions::Bessel_J0(const complex_t &value)
{
    if(std::imag(value) < Numeric::double_epsilon) {
        return complex_t(Bessel_J0(std::real(value)), 0.0);
    } else {
        return Bessel_J0_PowSer(value);
    }
}

complex_t MathFunctions::Bessel_J1(const complex_t &value)
{
    if(std::imag(value) < Numeric::double_epsilon) {
        return complex_t(Bessel_J1(std::real(value)), 0.0);
    } else {
        return Bessel_J1_PowSer(value);
    }
}

complex_t MathFunctions::Bessel_C1(const complex_t &value)
{
    if(std::imag(value) < Numeric::double_epsilon) {
        double xv = std::real(value);
        return std::abs(xv) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(xv)/xv : 0.5;
    } else {
        return std::abs(value) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(value)/value : 0.5;
    }
}

double MathFunctions::Si(double value)  // int_0^x du Sin(u)/u
{
    return gsl_sf_Si(value);
}

double MathFunctions::sinc(double value)  // Sin(x)/x
{
    return gsl_sf_sinc(value/Units::PI);
}

complex_t MathFunctions::sinc(const complex_t &value)  // Sin(x)/x
{
    // This is an exception from the rule that we must not test floating-point numbers for equality.
    // For small non-zero values, sin(z) returns quite accurately z or z-z^3/6.
    // There is no loss of precision in computing sin(z)/z.
    // Therefore there is no need for an expensive test like abs(z)<eps.
    if( value==complex_t(0.,0.) )
        return complex_t(1.0, 0.0);
    return std::sin(value)/value;
}

complex_t MathFunctions::tanhc(const complex_t &value)  // tanh(x)/x
{
    if(std::abs(value)<Numeric::double_epsilon)
        return complex_t(1.0, 0.0);
    return std::tanh(value)/value;
}

complex_t MathFunctions::Laue(const complex_t &value, size_t N) // Exp(iNx/2)*Sin((N+1)x)/Sin(x)
{
    if (N==0)
        return complex_t(1.0, 0.0);
    if(std::abs(value)<Numeric::double_epsilon)
        return complex_t(N+1.0, 0.0);
    return std::exp(complex_t(0.0, 1.0)*value*(double)N/2.0)*std::sin(value*(N+1.0)/2.0)/std::sin(value/2.0);
}

#ifndef GCCXML_SKIP_THIS
Eigen::Matrix2d MathFunctions::Norm(const Eigen::Matrix2cd &M) {
    Eigen::Matrix2d result;
    result(0,0) = std::norm((complex_t)M(0,0));
    result(0,1) = std::norm((complex_t)M(0,1));
    result(1,0) = std::norm((complex_t)M(1,0));
    result(1,1) = std::norm((complex_t)M(1,1));
    return result;
}

Eigen::Matrix2d MathFunctions::Abs(const Eigen::Matrix2cd &M) {
    Eigen::Matrix2d result;
    result(0,0) = std::abs((complex_t)M(0,0));
    result(0,1) = std::abs((complex_t)M(0,1));
    result(1,0) = std::abs((complex_t)M(1,0));
    result(1,1) = std::abs((complex_t)M(1,1));
    return result;
}

Eigen::Matrix2cd MathFunctions::Conj(const Eigen::Matrix2cd &M) {
    Eigen::Matrix2cd result;
    result(0,0) = std::conj((complex_t)M(0,0));
    result(0,1) = std::conj((complex_t)M(0,1));
    result(1,0) = std::conj((complex_t)M(1,0));
    result(1,1) = std::conj((complex_t)M(1,1));
    return result;
}

Eigen::Matrix2cd MathFunctions::ProductByElement(
        const Eigen::Matrix2cd &left, const Eigen::Matrix2cd &right) {
    Eigen::Matrix2cd result;
    result(0,0) = left(0,0) * right(0,0);
    result(0,1) = left(0,1) * right(0,1);
    result(1,0) = left(1,0) * right(1,0);
    result(1,1) = left(1,1) * right(1,1);
    return result;
}

Eigen::Matrix2d MathFunctions::Real(const Eigen::Matrix2cd &M) {
    Eigen::Matrix2d result;
    result(0,0) = ((complex_t)M(0,0)).real();
    result(0,1) = ((complex_t)M(0,1)).real();
    result(1,0) = ((complex_t)M(1,0)).real();
    result(1,1) = ((complex_t)M(1,1)).real();
    return result;
}
#endif

double MathFunctions::Gaussian(double value, double average, double std_dev)
{
    return StandardNormal((value - average) / std_dev) / std_dev;
}

double MathFunctions::IntegratedGaussian(double value, double average, double std_dev)
{
    double normalized_value = (value - average) / std_dev;
    double root2 = std::sqrt(2.0);
    return (gsl_sf_erf(normalized_value / root2) + 1.0) / 2.0;
}

double MathFunctions::StandardNormal(double value)
{
    return std::exp(-value * value / 2.0) / std::sqrt(Units::PI2);
}

double MathFunctions::GenerateStandardNormalRandom() // using GSL
{
    gsl_rng *r;
    r = gsl_rng_alloc(gsl_rng_ranlxs2);
    double result = gsl_ran_ugaussian(r);
    gsl_rng_free(r);
    return result;
}

//! @brief simple (and unoptimized) wrapper function
//!   for the discrete fast Fourier transformation library (fftw3)

std::vector<complex_t> MathFunctions::FastFourierTransform(const std::vector<complex_t> &data,
                                                           MathFunctions::EFFTDirection ftCase)
{
    double scale(1.);
    size_t npx = data.size();

    fftw_complex *ftData = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * npx);
    fftw_complex *ftResult = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * npx);
    memset(ftData, 0, sizeof(fftw_complex) * npx);
    memset(ftResult, 0, sizeof(fftw_complex) * npx);

    for (size_t i = 0; i < npx; i++) {
        ftData[i][0] = data[i].real();
        ftData[i][1] = data[i].imag();
    }

    fftw_plan plan;
    switch (ftCase) {
    case MathFunctions::FORWARD_FFT:
        plan = fftw_plan_dft_1d((int)npx, ftData, ftResult, FFTW_FORWARD, FFTW_ESTIMATE);
        break;
    case MathFunctions::BACKWARD_FFT:
        plan = fftw_plan_dft_1d((int)npx, ftData, ftResult, FFTW_BACKWARD, FFTW_ESTIMATE);
        scale = 1. / double(npx);
        break;
    default:
        throw std::runtime_error(
            "MathFunctions::FastFourierTransform -> Panic! Unknown transform case.");
    }

    fftw_execute(plan);

    // saving data for user
    std::vector<complex_t> outData;
    outData.resize(npx);
    for (size_t i = 0; i < npx; i++) {
        outData[i] = scale * complex_t(ftResult[i][0], ftResult[i][1]);
    }

    fftw_destroy_plan(plan);
    fftw_free(ftData);
    fftw_free(ftResult);

    return outData;
}

//! @brief simple (and unoptimized) wrapper function
//!   for the discrete fast Fourier transformation library (fftw3);
//!   transforms real to complex

std::vector<complex_t> MathFunctions::FastFourierTransform(const std::vector<double> &data,
                                                           MathFunctions::EFFTDirection ftCase)
{
    std::vector<complex_t> cdata;
    cdata.resize(data.size());
    for (size_t i = 0; i < data.size(); i++) {
        cdata[i] = complex_t(data[i], 0);
    }
    return MathFunctions::FastFourierTransform(cdata, ftCase);
}

//! convolution of two real vectors of equal size

std::vector<complex_t> MathFunctions::ConvolveFFT(const std::vector<double> &signal,
                                                  const std::vector<double> &resfunc)
{
    if (signal.size() != resfunc.size()) {
        throw std::runtime_error("MathFunctions::ConvolveFFT() -> This convolution works only for "
                                 "two vectors of equal size. Use Convolve class instead.");
    }
    std::vector<complex_t> fft_signal
        = MathFunctions::FastFourierTransform(signal, MathFunctions::FORWARD_FFT);
    std::vector<complex_t> fft_resfunc
        = MathFunctions::FastFourierTransform(resfunc, MathFunctions::FORWARD_FFT);

    std::vector<complex_t> fft_prod;
    fft_prod.resize(fft_signal.size());
    for (size_t i = 0; i < fft_signal.size(); i++) {
        fft_prod[i] = fft_signal[i] * fft_resfunc[i];
    }

    std::vector<complex_t> result
        = MathFunctions::FastFourierTransform(fft_prod, MathFunctions::BACKWARD_FFT);
    return result;
}

//! Computes the complex Bessel function J0(z), using standard power series and asymptotic expansion.
//!
//! Forked from unoptimized code at http://www.crbond.com/math.htm,
//! who refers to "Computation of Special Functions", Zhang and Jin, John Wiley and Sons, 1996.

//! TODO: Some optimizations of J1 not yet propagated here.

complex_t MathFunctions::Bessel_J0_PowSer(const complex_t &z)
{
    complex_t cj0;
    static const complex_t cone(1.0, 0.0);
    static const complex_t czero(0.0, 0.0);
    static const double eps = 1e-15;
    static double a[] = { -7.03125e-2,           0.112152099609375,     -0.5725014209747314,
                          6.074042001273483,     -1.100171402692467e2,  3.038090510922384e3,
                          -1.188384262567832e5,  6.252951493434797e6,   -4.259392165047669e8,
                          3.646840080706556e10,  -3.833534661393944e12, 4.854014686852901e14,
                          -7.286857349377656e16, 1.279721941975975e19 };
    static double b[] = { 7.32421875e-2,         -0.2271080017089844,  1.727727502584457,
                          -2.438052969955606e1,  5.513358961220206e2,  -1.825775547429318e4,
                          8.328593040162893e5,   -5.006958953198893e7, 3.836255180230433e9,
                          -3.649010818849833e11, 4.218971570284096e13, -5.827244631566907e15,
                          9.476288099260110e17,  -1.792162323051699e20 };

    double a0 = std::abs(z);
    complex_t z1 = z;
    if (a0 == 0.0)
        return cone;
    if (std::real(z) < 0.0)
        z1 = -z;
    if (a0 <= 12.0) {
        // standard power series [http://dlmf.nist.gov/10.2 (10.2.2)]
        complex_t z2 = z * z;
        cj0 = cone;
        complex_t cr = cone;
        for (size_t k = 1; k <= 40; ++k) {
            cr *= -0.25 * z2 / (double)(k * k);
            cj0 += cr;
            if (std::abs(cr) < std::abs(cj0) * eps)
                break;
        }
    } else {
        // Hankel's asymptotic expansion [http://dlmf.nist.gov/10.17 (10.17.3)]
        size_t kz;
        if (a0 >= 50.0)
            kz = 8; // can be changed to 10
        else if (a0 >= 35.0)
            kz = 10; //   "      "     "  12
        else
            kz = 12; //   "      "     "  14
        complex_t ct1 = z1 - Units::PID4;
        complex_t cp0 = cone;
        complex_t cq0 = -0.125 / z1;
        complex_t ptmp = std::pow(z1, -2.0);
        for (size_t k = 0; k < kz; ++k) {
            cp0 += a[k] * ptmp;
            cq0 += b[k] * ptmp / z1;
            ptmp /= (z1 * z1);
        }
        cj0 = std::sqrt(M_2_PI / z1) * (cp0 * std::cos(ct1) - cq0 * std::sin(ct1));
    }
    return cj0;
}

//! Computes the complex Bessel function J1(z), using standard power series and asymptotic expansion.
//!
//! Forked from same source as for Bessel_J0_PowSer

complex_t MathFunctions::Bessel_J1_PowSer(const complex_t &z)
{
    complex_t cj1;
    static const complex_t cone(1.0, 0.0);
    static const complex_t czero(0.0, 0.0);
    static const double eps = 1e-15;

    static double a1[] = { 0.1171875,             -0.1441955566406250,  0.6765925884246826,
                           -6.883914268109947,    1.215978918765359e2,  -3.302272294480852e3,
                           1.276412726461746e5,   -6.656367718817688e6, 4.502786003050393e8,
                           -3.833857520742790e10, 4.011838599133198e12, -5.060568503314727e14,
                           7.572616461117958e16,  -1.326257285320556e19 };
    static double b1[] = { -0.1025390625,         0.2775764465332031,    -1.993531733751297,
                           2.724882731126854e1,   -6.038440767050702e2,  1.971837591223663e4,
                           -8.902978767070678e5,  5.310411010968522e7,   -4.043620325107754e9,
                           3.827011346598605e11,  -4.406481417852278e13, 6.065091351222699e15,
                           -9.833883876590679e17, 1.855045211579828e20 };

    double a0 = std::abs(z);
    if (a0 == 0.0)
        return czero;

    complex_t z1 = z;
    if (std::real(z) < 0.0)
        z1 = -z;
    if (a0 <= 12.0) {
        // standard power series [http://dlmf.nist.gov/10.2 (10.2.2)]
        const complex_t z2 = 0.25 * z * z;
        cj1 = cone;
        complex_t cr = cone; // powers will be computed recursively
        for (int k = 1; k <= 40; ++k) {
            cr *= -z2 / (double)(k * (k + 1));
            cj1 += cr;
            if (std::abs(cr) < std::abs(cj1) * eps)
                break;
        }
        cj1 *= 0.5 * z1;
    } else {
        // Hankel's asymptotic expansion [http://dlmf.nist.gov/10.17 (10.17.3)]
        size_t kz;
        if (a0 >= 50.0)
            kz = 8; // can be changed to 10
        else if (a0 >= 35.0)
            kz = 10; //   "      "     "  12
        else
            kz = 12; //   "      "     "  14
        complex_t cp1 = cone;
        complex_t cq1 = 0.375; // division by z1 postponed to final sum
        const complex_t z1m2 = 1. / (z1*z1); // faster than std::pow(z1, -2.0) ??
        complex_t ptmp = z1m2; // powers will be computed recursively
        for (size_t k = 0; k < kz; ++k) {
            cp1 += a1[k] * ptmp;
            cq1 += b1[k] * ptmp; // division by z1 postponed to final sum
            ptmp *= z1m2;
        }
        const complex_t ct2 = z1 - 0.75 * Units::PI;
        cj1 = std::sqrt(M_2_PI / z1) * (cp1 * std::cos(ct2) - cq1/z1 * std::sin(ct2));
    }
    if (std::real(z) < 0.0)
        cj1 = -cj1;
    return cj1;
}

complex_t MathFunctions::geometricSum(complex_t z, int exponent)
{
    if (exponent < 1) {
        throw LogicErrorException("MathFunctions::geometricSeries:"
                                  " exponent should be > 0");
    }
    complex_t result(0.0, 0.0);
    double nd = (double)exponent;
    --exponent;
    while (exponent > 0) {
        result += std::pow(z, exponent) * (nd - exponent);
        --exponent;
    }
    return result;
}
