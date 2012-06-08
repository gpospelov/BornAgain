#ifndef CONVOLVE_H
#define CONVOLVE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Convolve.h
//! @brief  Definition of Convolve class
//! @author Scientific Computing Group at FRM II
//! @date   30.05.2012


#include <fftw3.h>
#include <vector>



namespace MathFunctions
{


//- -------------------------------------------------------------------
//! @class Convolve
//! @brief Convolution of two real vectors (1D or 2D ) using Fast Fourier Transformation.
//!
//! Usage:
//! std::vector<double> signal, kernel, result;
//! Convolve cv;
//! cv.fftconvolve(signal, kernel, result)
//!
//! Given code rely on code from Jeremy Fix page
//! http://jeremy.fix.free.fr/spip.php?article15
//! see also
//! "Efficient convolution using the Fast Fourier Transform, Application in C++"
//! by Jeremy Fix, May 30, 2011
//- -------------------------------------------------------------------
class Convolve
{
public:
    Convolve();
    ~Convolve();

    //! definition of 1d vector of double
    typedef std::vector<double> double1d_t;

    //! definition of 2d vector of double
    typedef std::vector<double1d_t> double2d_t;

    //! convolution  modes
    enum Mode { FFTW_LINEAR_FULL, FFTW_LINEAR_SAME_UNPADDED, FFTW_LINEAR_SAME, FFTW_LINEAR_VALID, FFTW_CIRCULAR_SAME, FFTW_CIRCULAR_SAME_SHIFTED, FFTW_UNDEFINED };

    //! convolution in 1D
    void fftconvolve(const double1d_t &source, const double1d_t &kernel, double1d_t &result);

    //! convolution in 2D
    void fftconvolve(const double2d_t &source, const double2d_t &kernel, double2d_t &result);

    //! prepare arrays for 2D convolution of given vectors
    void init(int h_src, int w_src, int h_kernel, int w_kernel);

    //! set convolution mode
    void setMode(Mode mode) { m_mode = mode; }

private:
    //! compute convolution of source and kernel using fast fourier transformation
    void fftw_convolve(const double2d_t &source, const double2d_t &kernel);
    //void fftw_convolve(double * src,double * kernel);

    //! compute circual convolution of source and kernel using fast fourier transformation
    //void fftw_circular_convolution(double * src, double * kernel);
    void fftw_circular_convolution(const double2d_t &source, const double2d_t &kernel);

    //! find closest number X>n,  which  can be factorised according to fftw3 favorite factorisation
    int find_closest_factor(int n);

    //! if a number can be factorised using only favorite fftw3 factors
    bool is_optimal(int n);

    //! Workspace contains input (source and kernel), intermediate and output arrays to run convolution via fft
    //! 'source' it is our signal, 'kernel' it is our resolution (or delta-responce) function
    //! Sizes of input arrays are adjusted; output arrays are alocated via fftw3 allocation for maximum performance
    class Workspace
    {
    public:
        Workspace();
        ~Workspace();
        void clear();
        friend class Convolve;
    private:
        int h_src, w_src;                 // size of original 'source' array in 2 dimensions
        int h_kernel, w_kernel;           // size of original 'kernel' array in 2 dimensions
        int w_fftw, h_fftw;               // size of adjusted source and kernel arrays (in_src, out_src, in_kernel, out_kernel)
        double *in_src;                   // adjusted input 'source' array
        double *out_src;                  // result of fourier transformation of source
        double *in_kernel;                // adjusted input 'kernel' array
        double *out_kernel;               // result of fourier transformation of kernel
        double *dst_fft;                  // result of production of FFT(source) and FFT(kernel)
        int h_dst, w_dst;                 // size of resulting array
        double *dst;                      // The array containing the result
        fftw_plan p_forw_src;
        fftw_plan p_forw_kernel;
        fftw_plan p_back;
    };

    Workspace ws; // input and output data for fftw3
    Mode m_mode;  // convolution mode
    std::vector<size_t > m_implemented_factors; // favorite factorization terms of fftw3
};


} // namespace MathFunctions


typedef enum
{
    FFTW_LINEAR_FULL,
    FFTW_LINEAR_SAME_UNPADDED,
    FFTW_LINEAR_SAME,
    FFTW_LINEAR_VALID,
    FFTW_CIRCULAR_SAME,
    FFTW_CIRCULAR_SAME_SHIFTED,
    FFTW_CIRCULAR_CUSTOM
} FFTW_Convolution_Mode;

typedef struct FFTW_Workspace
{
    //fftw_complex * in_src, *out_src;
    double * in_src, *out_src, *in_kernel, *out_kernel;
    int h_src, w_src, h_kernel, w_kernel;
    int w_fftw, h_fftw;
    FFTW_Convolution_Mode mode;
    double * dst_fft;
    double * dst; // The array containing the result
    int h_dst, w_dst; // its size ; This is automatically set by init_workspace, despite you use FFTW_CIRCULAR_CUSTOM
    fftw_plan p_forw_src;
    fftw_plan p_forw_kernel;
    fftw_plan p_back;

} FFTW_Workspace;

extern void factorize (const int n,
                int *n_factors,
                int factors[],
                int * implemented_factors);

extern bool is_optimal(int n, int * implemented_factors);
extern int find_closest_factor(int n, int * implemented_factor);
extern void init_workspace_fftw(FFTW_Workspace & ws, FFTW_Convolution_Mode mode, int h_src, int w_src, int h_kernel, int w_kernel);
extern void clear_workspace_fftw(FFTW_Workspace & ws);
extern void fftw_convolve(FFTW_Workspace &ws, double * src,double * kernel);
extern void fftw_circular_convolution(FFTW_Workspace &ws, double * src, double * kernel);





#endif // CONVOLVE_H
