// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/FourierTransform.h
//! @brief     Defines class MathFunctions::FourierTransform.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include "WinDllMacros.h"
#include <fftw3.h>
#include <vector>

//! Fourier transform of vectors (in 1D or 2D) using Fast Fourier Transform.
//!
//! Usage:
//! std::vector<double> signal, result;
//! FourierTransform ft;
//! ft.fft(signal, result)
//!
//! Given code rely on code from Jeremy Fix page, http://jeremy.fix.free.fr/spip.php?article15,
//! see also "Efficient convolution using the Fast Fourier Transform, Application in C++"
//! by Jeremy Fix, May 30, 2011
//!
//! @ingroup tools_internal
class BA_CORE_API_ FourierTransform
{
public:
    //! definition of 1d vector of double
    typedef std::vector<double > double1d_t;

    //! definition of 2d vector of double
    typedef std::vector<double1d_t > double2d_t;

    FourierTransform();

    /*
    //! convolution  modes
    //! use LINEAR_SAME or CIRCULAR_SAME_SHIFTED for maximum performance
    enum EConvolutionMode { FFTW_LINEAR_FULL, FFTW_LINEAR_SAME_UNPADDED,
                            FFTW_LINEAR_SAME, FFTW_LINEAR_VALID,
                            FFTW_CIRCULAR_SAME, FFTW_CIRCULAR_SAME_SHIFTED,
                            FFTW_UNDEFINED };

    //! convolution in 1D
    void fftconvolve(const double1d_t& source, const double1d_t& kernel, double1d_t& result);

    //! convolution in 2D
    void fftconvolve(const double2d_t& source, const double2d_t& kernel, double2d_t& result);

    //! prepare arrays for 2D convolution of given vectors
    void init(int h_src, int w_src, int h_kernel, int w_kernel);


    //! Sets convolution mode
    void setMode(EConvolutionMode mode) { m_mode = mode; }
    */

    //! FT in 1D
    void fft(const double1d_t& source, double1d_t& result);

    //! FT in 2D
    void fft(const double2d_t& source, double2d_t& result);

    //! prepare arrays for 2D Fourier Transformation (FT) of the given vector
    void init(int h_src, int w_src);

private:
    //! compute FT of source using Fast Fourier transformation from fftw
    void fftw_forward_FT(const double2d_t& source);

    //void fftw_back_FT(const double2d_t& out);

    //! find closest number X>n that can be factorised according to fftw3 favorite factorisation
    int find_closest_factor(int n);

    //! if a number can be factorised using only favorite fftw3 factors
    bool is_optimal(int n);

    //! Workspace for Fourier Transform.

    //! Workspace contains input (src), intermediate and output (out)
    //! arrays to run FT via fft; 'source' is our signal
    //! Sizes of input arrays are adjusted; output arrays are allocated via
    //! fftw3 allocation for maximum performance.
    class Workspace
    {
    public:
        Workspace();
        ~Workspace();
        void clear();
        friend class FourierTransform;
    private:
        int h_src, w_src; // size of original 'source' array in 2 dimensions
        // size of adjusted source arrays (in_src, out_src)
        int w_fftw, h_fftw;
        //! adjusted input 'source' array
        double *in_src;
        //! result of Fourier transformation of source
        double *out_src;
        //! result of back Fourier transformation FFT(source)
        //double *dst_fft;
        int h_dst, w_dst;                 // size of resulting array
        //int h_offset, w_offset;           // offsets to copy result into output arrays

        fftw_plan p_forw_src;
        //fftw_plan p_back;
    };

    //! input and output data for fftw3
    Workspace ws;
    //! convolution mode
    //EConvolutionMode m_mode;
    std::vector<size_t > m_implemented_factors; // favorite factorization terms of fftw3
};

#endif // FOURIERTRANSFORM_H
