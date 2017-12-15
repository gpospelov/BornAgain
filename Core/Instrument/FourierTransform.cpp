// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/FourierTransform.cpp
//! @brief     Implements class FourierTransform.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FourierTransform.h"
#include "Exceptions.h"
#include <iostream>
#include <sstream>
#include <stdexcept> // need overlooked by g++ 5.4

FourierTransform::FourierTransform()
{
    // storing favorite fftw3 prime factors
    const size_t FFTW_FACTORS[] = {13,11,7,5,3,2};
    m_implemented_factors.assign(
        FFTW_FACTORS, FFTW_FACTORS + sizeof(FFTW_FACTORS)/sizeof(FFTW_FACTORS[0]));
}

FourierTransform::Workspace::Workspace() :
    h_src(0), w_src(0), w_fftw(0), h_fftw(0),
    in_src(0), out_src(0), dst_fft(0), h_dst(0), w_dst(0),
    //dst(0),
    h_offset(0), w_offset(0),
    p_forw_src(nullptr), p_back(nullptr)
{
}

FourierTransform::Workspace::~Workspace()
{
    clear();
}

void FourierTransform::Workspace::clear()
{
    h_src=0;
    w_src=0;

    if(in_src) delete[] in_src;
    in_src = 0;

    if(out_src) fftw_free((fftw_complex*)out_src);
    out_src = 0;

    if(dst_fft) delete[] dst_fft;
    dst_fft=0;

    //if(dst) delete[] dst;
    //dst=0;

    h_offset = 0;
    w_offset = 0;

    if(p_forw_src != nullptr) fftw_destroy_plan(p_forw_src);
    if(p_back != nullptr)  fftw_destroy_plan(p_back);

    // this returns fftw3 into completely initial state but is dramatically slow
    //fftw_cleanup();
}


/* ************************************************************************* */
// Fourier Transform in 2d
/* ************************************************************************* */
void FourierTransform::fft(const double2d_t& source, double2d_t& result)
{
    int h_src = (int)source.size();
    int w_src = (int)(source.size() ? source[0].size() : 0);

    // initialisation
    init(h_src, w_src);
    // Compute the forward FT
    fftw_forward_FT(source);

    // results
    result.clear();
    result.resize(ws.h_dst);
    for(int i=0; i<ws.h_dst; i++) {
        result[i].resize(ws.w_dst,0);
        for(int j=0; j<ws.w_dst; j++) {
            //result[i][j]=ws.dst[i*ws.w_dst+j];
            result[i][j] = ws.dst_fft[(i+ws.h_offset)*ws.w_fftw+j+ws.w_offset];
        }
    }

}


/* ************************************************************************* */
// Fourier Transform in 1d
/* ************************************************************************* */
void FourierTransform::fft(
    const double1d_t& source, double1d_t& result)
{
    // we simply create 2d arrays with length of first dimension equal to 1, and call 2d convolution
    double2d_t source2d, kernel2d;
    source2d.push_back(source);

    double2d_t result2d;
    fft(source2d, result2d);
    if(result2d.size() != 1)
        throw Exceptions::RuntimeErrorException(
            "Convolve::fftconvolve -> Panic in 1d");
    result = result2d[0];
}


/* ************************************************************************* */
// initialise input and output arrays for fast Fourier transformation
/* ************************************************************************* */
void FourierTransform::init(int h_src, int w_src)
{
    if(!h_src || !w_src) {
        std::ostringstream os;
        os << "Convolve::init() -> Panic! Wrong dimensions " <<
            h_src << " " << w_src << std::endl;
        throw Exceptions::RuntimeErrorException(os.str());
    }

    ws.clear();
    ws.h_src = h_src;
    ws.w_src = w_src;

    // Previously in switch case

    // Full Linear convolution
    ws.h_fftw = find_closest_factor(h_src);
    ws.w_fftw = find_closest_factor(w_src);
    ws.h_dst = h_src;
    ws.w_dst = w_src;
    // Here we just keep the first [0:h_dst-1 ; 0:w_dst-1] real part elements of out_src
    ws.h_offset = 0;
    ws.w_offset = 0;

    // Previously in switch case




    ws.in_src = new double[ws.h_fftw * ws.w_fftw];
    ws.out_src = (double*) fftw_malloc(sizeof(fftw_complex) * ws.h_fftw * (ws.w_fftw/2+1));


    ws.dst_fft = new double[ws.h_fftw * ws.w_fftw];
    //ws.dst = new double[ws.h_dst * ws.w_dst];

    // Initialization of the plans
    ws.p_forw_src = fftw_plan_dft_r2c_2d(ws.h_fftw, ws.w_fftw, ws.in_src,
                                         (fftw_complex*)ws.out_src, FFTW_ESTIMATE);
    if( ws.p_forw_src == nullptr )
        throw Exceptions::RuntimeErrorException(
            "Convolve::init() -> Error! Can't initialise p_forw_src plan.");

    // The backward FFT takes ws.out_src as input
    ws.p_back = fftw_plan_dft_c2r_2d(
        ws.h_fftw, ws.w_fftw, (fftw_complex*)ws.out_src, ws.dst_fft, FFTW_ESTIMATE);
    if( ws.p_back == nullptr )
        throw Exceptions::RuntimeErrorException(
            "Convolve::init() -> Error! Can't initialise p_back plan.");
}


/* ************************************************************************* */
// initialise input and output arrays for fast Fourier transformation
/* ************************************************************************* */

void FourierTransform::fftw_forward_FT(const double2d_t& src)
{
    if(ws.h_fftw <= 0 || ws.w_fftw <= 0)
        throw Exceptions::RuntimeErrorException(
            "Convolve::fftw_convolve() -> Panic! Initialisation is missed.");

    double * ptr, *ptr_end;

    // Reset the content of ws.in_src
    for(ptr = ws.in_src, ptr_end = ws.in_src + ws.h_fftw*ws.w_fftw ; ptr != ptr_end ; ++ptr)
        *ptr = 0.0;

    // Then we build our periodic signals
    //ptr = src;
    for(int i = 0 ; i < ws.h_src ; ++i)
        for(int j = 0 ; j < ws.w_src ; ++j, ++ptr)
            ws.in_src[(i%ws.h_fftw)*ws.w_fftw+(j%ws.w_fftw)] += src[i][j];

    // And we compute their packed FFT
    fftw_execute(ws.p_forw_src);
}

/*
void FourierTransform::fftw_back_FT(const double2d_t& out)
{
    if(ws.h_fftw <= 0 || ws.w_fftw <= 0)
        throw Exceptions::RuntimeErrorException(
            "Convolve::fftw_convolve() -> Panic! Initialisation is missed.");

    double * ptr, *ptr_end;

    // Compute the backward FFT
    // Carefull, The backward FFT does not preserve the output
    fftw_execute(ws.p_back);
    // Scale the transform
    for(ptr = ws.dst_fft, ptr_end = ws.dst_fft + ws.w_fftw*ws.h_fftw ; ptr != ptr_end ; ++ptr)
        *ptr /= double(ws.h_fftw*ws.w_fftw);
}
*/

/* ************************************************************************* */
// find a number closest to the given one, which  can be factorised according
// to fftw3 favorite factorisation
/* ************************************************************************* */

int FourierTransform::find_closest_factor(int n)
{
    if(is_optimal(n) ) {
        return n;
    } else {
        int j = n+1;
        while( !is_optimal(j) ) ++j;
        return j;
    }
}


/* ************************************************************************* */
// if a number can be factorised using only favorite fftw3 factors
/* ************************************************************************* */
bool FourierTransform::is_optimal(int n)
{
    if(n==1)
        return false;
    size_t ntest = n;
    for(size_t i=0; i<m_implemented_factors.size(); i++){
        while( (ntest%m_implemented_factors[i]) == 0 ) {
            ntest = ntest/m_implemented_factors[i];
        }
    }
    return ntest==1;
}
