// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Tools/MathFunctions.cpp 
//! @brief     Implements functions in namespace MathFunctions.
//
// ************************************************************************** //

#include "MathFunctions.h"

#include <cmath>
#include <cstring>
#include <stdexcept>
#include <fftw3.h>
#include <gsl/gsl_sf_erf.h>

double MathFunctions::Gaussian(double value, double average, double std_dev)
{
    return StandardNormal((value-average)/std_dev)/std_dev;
}

double MathFunctions::IntegratedGaussian(double value, double average, double std_dev)
{
    double normalized_value = (value - average)/std_dev;
    double root2 = std::sqrt(2.0);
    return (gsl_sf_erf(normalized_value/root2) + 1.0)/2.0;
}

double MathFunctions::StandardNormal(double value)
{
    return std::exp(- value*value / 2.0) / std::sqrt(2.0*M_PI);
}

double MathFunctions::GenerateStandardNormalRandom()  // using Box-Muller transform
{
    double u1 = GenerateUniformRandom();
    double u2 = GenerateUniformRandom();
    return std::sqrt(-2.0*std::log(u1))*std::cos(2*M_PI*u2);
}


/* ************************************************************************* */
// simple (and unoptimized) wrapper function for the discrete fast fourier
// transformation library (fftw3)
/* ************************************************************************* */
std::vector<complex_t > MathFunctions::FastFourierTransform(const std::vector<complex_t > &data, MathFunctions::TransformCase ftCase)
{
    double scale(1.);
    size_t npx = data.size();

    fftw_complex *ftData = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * npx);
    fftw_complex *ftResult = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * npx);
    memset(ftData, 0, sizeof(fftw_complex) * npx);
    memset(ftResult, 0, sizeof(fftw_complex) * npx);

    for(size_t i=0; i<npx; i++){
        ftData[i][0] = data[i].real();
        ftData[i][1] = data[i].imag();
    }

    fftw_plan plan;
    switch (ftCase)
    {
        case MathFunctions::ForwardFFT:
            plan = fftw_plan_dft_1d( (int)npx, ftData, ftResult, FFTW_FORWARD, FFTW_ESTIMATE );
            break;
        case MathFunctions::BackwardFFT:
            plan = fftw_plan_dft_1d( (int)npx, ftData, ftResult, FFTW_BACKWARD, FFTW_ESTIMATE );
            scale = 1./double(npx);
            break;
        default:
            throw std::runtime_error("MathFunctions::FastFourierTransform -> Panic! Unknown transform case.");
    }

    fftw_execute(plan);

    // saving data for user
    std::vector<complex_t > outData;
    outData.resize(npx);
    for(size_t i=0; i<npx; i++){
        outData[i] = scale*complex_t(ftResult[i][0], ftResult[i][1]);
    }

    fftw_destroy_plan(plan);
    fftw_free(ftData);
    fftw_free(ftResult);

    return outData;
}


/* ************************************************************************* */
// simple (and unoptimized) wrapper function for the discrete fast fourier
// transformation library (fftw3)
//
// transforms real to complex
/* ************************************************************************* */
std::vector<complex_t > MathFunctions::FastFourierTransform(const std::vector<double > &data, MathFunctions::TransformCase ftCase)
{
    std::vector<complex_t> cdata;
    cdata.resize(data.size());
    for(size_t i=0; i<data.size(); i++) { cdata[i] = complex_t(data[i], 0); }
    return MathFunctions::FastFourierTransform(cdata, ftCase);
}

//complex_t MathFunctions::Bessel_J1(complex_t value)
//{
//    complex_t z1,z2,cr,cp,cs,cp0,cq0,cp1,cq1,ct1,ct2,cu;
//    complex_t result;
//    double a0;
//    int k,kz;
//
//    static complex_t czero(0.0, 0.0);
//    static complex_t cone(1.0, 0.0);
//    static double a1[] = {
//         0.1171875,
//        -0.1441955566406250,
//         0.6765925884246826,
//        -6.883914268109947,
//         1.215978918765359e2,
//        -3.302272294480852e3,
//         1.276412726461746e5,
//        -6.656367718817688e6,
//         4.502786003050393e8,
//        -3.833857520742790e10,
//         4.011838599133198e12,
//        -5.060568503314727e14,
//         7.572616461117958e16,
//        -1.326257285320556e19};
//    static double b1[] = {
//        -0.1025390625,
//         0.2775764465332031,
//        -1.993531733751297,
//         2.724882731126854e1,
//        -6.038440767050702e2,
//         1.971837591223663e4,
//        -8.902978767070678e5,
//         5.310411010968522e7,
//        -4.043620325107754e9,
//         3.827011346598605e11,
//        -4.406481417852278e13,
//         6.065091351222699e15,
//        -9.833883876590679e17,
//         1.855045211579828e20};
//
//    a0 = abs(value);
//    z2 = value*value;
//    z1 = value;
//    if (a0 == 0.0) {
//        result = czero;
//        return result;
//    }
//    if (real(value) < 0.0) z1 = -value;
//    if (a0 <= 12.0) {
//        result = cone;
//        cr = cone;
//        for (k=1;k<=40;k++) {
//            cr *= -0.25*z2/(k*(k+1.0));
//            result += cr;
//            if (abs(cr) < abs(result)*Numeric::double_epsilon) break;
//        }
//        result *= 0.5*z1;
//        return result;
//    }
//    else {
//        if (a0 >= 50.0) kz = 8;         // can be changed to 10
//        else if (a0 >= 35.0) kz = 10;   //   "      "     "  12
//        else kz = 12;                   //   "      "     "  14
//        cp1 = cone;
//        for (k=0;k<kz;k++) {
//            cp1 += a1[k]*pow(z1,-2.0*k-2.0);
//        }
//        cq1 = 0.375/z1;
//        for (k=0;k<kz;k++) {
//            cq1 += b1[k]*pow(z1,-2.0*k-3.0);
//        }
//        result = cu*(cp1*cos(ct2)-cq1*sin(ct2));
//        return result;
//    }
//}

/* ************************************************************************* */
// convolution of two real vectors of equal size
/* ************************************************************************* */
std::vector<complex_t> MathFunctions::ConvolveFFT(const std::vector<double> &signal, const std::vector<double> &resfunc)
{
    if(signal.size() != resfunc.size() ) {
        throw std::runtime_error("MathFunctions::ConvolveFFT() -> This convolution works only for two vectors of equal size. Use Convolve class instead.");
    }
    std::vector<complex_t > fft_signal = MathFunctions::FastFourierTransform(signal, MathFunctions::ForwardFFT);
    std::vector<complex_t > fft_resfunc = MathFunctions::FastFourierTransform(resfunc, MathFunctions::ForwardFFT);

    std::vector<complex_t > fft_prod;
    fft_prod.resize(fft_signal.size());
    for(size_t i=0; i<fft_signal.size(); i++){
        fft_prod[i] = fft_signal[i] * fft_resfunc[i];
    }

    std::vector<complex_t > result = MathFunctions::FastFourierTransform(fft_prod, MathFunctions::BackwardFFT);
    return result;
}
