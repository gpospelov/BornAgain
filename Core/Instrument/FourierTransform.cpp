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
#include <math.h>
#include <algorithm>

FourierTransform::FourierTransform()
{
    // storing favorite fftw3 prime factors
    const size_t FFTW_FACTORS[] = {13,11,7,5,3,2};
    m_implemented_factors.assign(
        FFTW_FACTORS, FFTW_FACTORS + sizeof(FFTW_FACTORS)/sizeof(FFTW_FACTORS[0]));

}

FourierTransform::Workspace::Workspace() :
    h_src(0), w_src(0), h_fftw(0), w_fftw(0),
    in_src(0), out_fftw(0),
    //h_dst(0), w_dst(0),
    //dst_fft(0),
    //dst(0), //not needed
    //h_offset(0), w_offset(0),
    //p_back(nullptr),
    p_forw_src(nullptr)
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

    if(out_fftw) fftw_free((fftw_complex*)out_fftw);
    out_fftw = 0;

    /*
    if(dst_fft) delete[] dst_fft;
    dst_fft=0;
    */

    //not needed
    //if(dst) delete[] dst;
    //dst=0;

    //h_offset = 0;
    //w_offset = 0;

    if(p_forw_src != nullptr) fftw_destroy_plan(p_forw_src);
    //if(p_back != nullptr)  fftw_destroy_plan(p_back);

    // this returns fftw3 into completely initial state but is dramatically slow
    //fftw_cleanup();
}


/* ************************************************************************* */
// Fourier Transform in 2d
/* ************************************************************************* */
void FourierTransform::fft(const double2d_t& source, double2d_t& result)
{
    int h_src = static_cast<int>(source.size());
    int w_src = static_cast<int>((source.size() ? source[0].size() : 0));

    // initialisation
    init(h_src, w_src);

    // Compute the forward FT
    fftw_forward_FT(source);

    double *ptr = ws.out_fftw;
    result.clear();
    result.resize(static_cast<size_t>(ws.h_fftw));
    for(size_t i = 0; i < static_cast<size_t>(ws.h_fftw); i++)
    {
        result[i].resize(static_cast<size_t>(ws.w_fftw),0);
        for(size_t j = 0, mirror = 0; j < static_cast<size_t>(ws.w_fftw); j++)
        {
            if(j < static_cast<size_t>(ws.w_fftw/2+1))
            {
                result[i][j] = *ptr;
                ptr += 2;
            }
            else
            {
                result[i][j] = result[i][j-(2*mirror)-2];
                mirror++;
            }

            //result[i][j] = *ptr;
            //ptr = ptr + 2;
            //ptr = ptr + 1;
        }
    }


    // if we have padded rows (bottom) and columns (right) due to nearest factors,
    // we drop them from result
    int rows_to_del = ws.h_fftw - ws.h_src;
    if(rows_to_del != 0)
    {
        int last_row = ws.h_fftw;
        for(int i = 0; i < rows_to_del; i++)
        {
            result.erase(result.begin() + last_row );
            last_row = last_row-1;
        }
    }

    int cols_to_del = ws.w_fftw - ws.w_src;
    if(cols_to_del != 0)
    {
        int last_col = ws.w_fftw;
        for(int i=0; i<cols_to_del; i++)
        {
            std::for_each(result.begin(), result.end(),
                [&](std::vector<double>& row) {
                    row.erase(std::next(row.begin(), last_col-1));
                });
            last_col = last_col-1;
        }
    }
}


/* ************************************************************************* */
// Fourier Transform in 1d
/* ************************************************************************* */
void FourierTransform::fft(
    const double1d_t& source, double1d_t& result)
{
    // we simply create 2d arrays with length of first dimension equal to 1, and call 2d FT
    double2d_t source2d;
    source2d.push_back(source);

    double2d_t result2d;
    fft(source2d, result2d);
    /*
    if(result2d.size() != 1)
        throw Exceptions::RuntimeErrorException(
            "FourierTransform::fft -> Panic in 1d");
            */
    result = result2d[0];
}


/* ************************************************************************* */
// initialise input and output arrays for fast Fourier transformation
/* ************************************************************************* */
void FourierTransform::init(int h_src, int w_src)
{
    if(!h_src || !w_src) {
        std::ostringstream os;
        os << "FourierTransform::init() -> Panic! Wrong dimensions " <<
            h_src << " " << w_src << std::endl;
        throw Exceptions::RuntimeErrorException(os.str());
    }

    ws.clear();
    ws.h_src = h_src;
    ws.w_src = w_src;

    // Similar to Full Linear Convolution from Convolve.cpp
    ws.h_fftw = find_closest_factor(h_src);
    ws.w_fftw = find_closest_factor(w_src);

    //ws.h_dst = h_src;
    //ws.w_dst = w_src;
    // Here we just keep the first [0:h_dst-1 ; 0:w_dst-1] real part elements of out_src
    //ws.h_offset = 0;
    //ws.w_offset = 0;

    ws.in_src = new double[static_cast<size_t>(ws.h_fftw * ws.w_fftw)];
    ws.out_fftw = static_cast<double*>(fftw_malloc(sizeof(fftw_complex)*
                                                  static_cast<size_t>(ws.h_fftw*(ws.w_fftw/2+1))));

    //ws.dst_fft = new double[ws.h_fftw * ws.w_fftw];
    //ws.dst = new double[ws.h_dst * ws.w_dst];

    // Initialization of the plans
    ws.p_forw_src = fftw_plan_dft_r2c_2d(ws.h_fftw, ws.w_fftw, ws.in_src,
                                         (fftw_complex*)ws.out_fftw, FFTW_ESTIMATE);
    //ws.p_forw_src = fftw_plan_dft_r2c_2d(ws.h_fftw, ws.w_fftw, ws.in_src,
    //                                     static_cast<double*>(ws.out_src), FFTW_ESTIMATE);

    if( ws.p_forw_src == nullptr )
        throw Exceptions::RuntimeErrorException(
            "FourierTransform::init() -> Error! Can't initialise p_forw_src plan.");

    /*
    // The backward FFT takes ws.out_src as input
    ws.p_back = fftw_plan_dft_c2r_2d(
        ws.h_fftw, ws.w_fftw, (fftw_complex*)ws.out_src, ws.dst_fft, FFTW_ESTIMATE);
    if( ws.p_back == nullptr )
        throw Exceptions::RuntimeErrorException(
            "FourierTransform::init() -> Error! Can't initialise p_back plan.");
     */
}


/* ************************************************************************* */
// initialise input and output arrays for fast Fourier transformation
/* ************************************************************************* */

void FourierTransform::fftw_forward_FT(const double2d_t& src)
{
    if(ws.h_fftw <= 0 || ws.w_fftw <= 0)
        throw Exceptions::RuntimeErrorException(
            "FourierTransform::fftw_forward_FT() -> Panic! Initialisation is missed.");

    double *ptr, *ptr_end;

    // Initializing the content of ws.in_src to zero for all elements
    for(ptr = ws.in_src, ptr_end = ws.in_src + ws.h_fftw*ws.w_fftw ; ptr != ptr_end ; ++ptr)
        *ptr = 0.0;

    // Then we build our input signal for FFTW algorihm i.e. in_src (pointer) from src (double2d_t)
    // where we arrange in_src in a manner such that the FFTW algorithm gives a centered-origin
    // (low freqency) at the center output - multiplying the original 2d array's each input
    // element by -1^(row+col) where row and col are the corresponding indices
    for(size_t row = 0; row < static_cast<size_t>(ws.h_src) ; ++row)
        for(size_t col = 0 ; col < static_cast<size_t>(ws.w_src) ; ++col)
            ws.in_src[(static_cast<int>(row)%ws.h_fftw)*ws.w_fftw
                    +(static_cast<int>(col)%ws.w_fftw)] += src[row][col] * pow(-1,row+col);

    // And we compute the FFT
    fftw_execute(ws.p_forw_src);

    double re_out, im_out;
    for(ptr = ws.out_fftw, ptr_end = ws.out_fftw+2*ws.h_fftw*(ws.w_fftw/2+1); ptr != ptr_end ; ++ptr)
    {
        re_out = *ptr;
        im_out = *(++ptr);
        // magnitude
        *(ptr-1) = sqrt(re_out * re_out + im_out * im_out);
        //phase
        *ptr = atan2(im_out, re_out);
    }
}

/*
void FourierTransform::fftw_back_FT(const double2d_t& out)
{
    if(ws.h_fftw <= 0 || ws.w_fftw <= 0)
        throw Exceptions::RuntimeErrorException(
            "FourierTransform::fftw_back_FT() -> Panic! Initialisation is missed.");

    double * ptr, *ptr_end;

    // Compute the backward FFT
    // Careful, The backward FFT does not preserve the output
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
    size_t ntest = static_cast<size_t>(n);
    for(size_t i=0; i<m_implemented_factors.size(); i++){
        while( (ntest%m_implemented_factors[i]) == 0 ) {
            ntest = ntest/m_implemented_factors[i];
        }
    }
    return ntest==1;
}
