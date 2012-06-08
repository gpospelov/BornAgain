#include "Convolve.h"
#include <iostream>
#include <stdexcept>
#include "Exceptions.h"

MathFunctions::Convolve::Convolve() : m_mode(FFTW_UNDEFINED)
{
    // storing favorite fftw3 prime factors
    const size_t FFTW_FACTORS[] = {13,11,7,5,3,2};
    m_implemented_factors.assign(FFTW_FACTORS, FFTW_FACTORS + sizeof(FFTW_FACTORS)/sizeof(FFTW_FACTORS[0]));
}



MathFunctions::Convolve::~Convolve()
{

}


MathFunctions::Convolve::Workspace::Workspace() :
    h_src(0), w_src(0), h_kernel(0), w_kernel(0),
    w_fftw(0), h_fftw(0), in_src(0), out_src(0), in_kernel(0), out_kernel(0), dst_fft(0), h_dst(0), w_dst(0), dst(0),
    p_forw_src(NULL), p_forw_kernel(NULL), p_back(NULL)
{

}


MathFunctions::Convolve::Workspace::~Workspace()
{
    clear();
}


void MathFunctions::Convolve::Workspace::clear()
{
    h_src=0;
    w_src=0;
    h_kernel=0;
    w_kernel = 0;
    if(in_src) delete[] in_src;
    in_src = 0;

    if(out_src) fftw_free((fftw_complex*)out_src);
    out_src = 0;

    if(in_kernel) delete[] in_kernel;
    in_kernel=0;

    if(out_kernel) fftw_free((fftw_complex*)out_kernel);
    out_kernel=0;

    if(dst_fft) delete[] dst_fft;
    dst_fft=0;

    if(dst) delete[] dst;
    dst=0;

    if(p_forw_src != NULL) fftw_destroy_plan(p_forw_src);
    if(p_forw_kernel != NULL) fftw_destroy_plan(p_forw_kernel);
    if(p_back != NULL)  fftw_destroy_plan(p_back);

    // this returns fftw3 into completely initial state but is dramatically slow
    //fftw_cleanup();
}


/* ************************************************************************* */
// convolution in dd
/* ************************************************************************* */
void MathFunctions::Convolve::fftconvolve(const double2d_t &source, const double2d_t &kernel, double2d_t &result)
{
    // set default convolution mode, if not defined
    if(m_mode == FFTW_UNDEFINED) {
        std::cout << "setting FFTW_LINEAR_SAME" << std::endl;
        setMode(FFTW_LINEAR_SAME);
    }

    size_t h_src = source.size();
    size_t w_src = (source.size() ? source[0].size() : 0);
    size_t h_kernel = kernel.size();
    size_t w_kernel = (kernel.size() ? kernel[0].size() : 0);

    if(!h_src || !w_src || !h_kernel || !w_kernel) {
        std::cout << "MathFunctions::Convolve::fftconvolve() -> Panic! Wrong dimensions " << h_src << " " << w_src << " " << h_kernel << " " << w_kernel << std::endl;
        throw std::runtime_error("XXX");
    }

    init(h_src, w_src, h_kernel, w_kernel);

//    double *src = new double[h_src*w_src];
//    for(size_t i=0; i<h_src; i++) {
//        for(size_t j=0; j<w_src; j++) {
//            src[i*w_src + j] = source[i][j];
//        }
//    }

//    double *krn = new double[h_kernel*w_kernel];
//    for(size_t i=0; i<h_kernel; i++) {
//        for(size_t j=0; j<w_kernel; j++) {
//            krn[i*w_kernel + j] = kernel[i][j];
//        }
//    }

//    fftw_convolve(src, krn);
    fftw_convolve(source, kernel);

//    delete [] src;
//    delete [] krn;

    // results
    result.clear();
    result.resize(ws.h_dst);
    for(int i=0; i<ws.h_dst; i++) {
        result[i].resize(ws.w_dst,0);
        for(int j=0; j<ws.w_dst; j++) {
            result[i][j]=ws.dst[i*ws.w_dst+j];
        }
    }

}


/* ************************************************************************* */
// convolution in 1d
/* ************************************************************************* */
void MathFunctions::Convolve::fftconvolve(const double1d_t &source, const double1d_t &kernel, double1d_t &result)
{
    // we simply create 2d arrays with length of first dimension equal to 1, and call 2d convolution
    double2d_t source2d, kernel2d;
    source2d.push_back(source);
    kernel2d.push_back(kernel);

    double2d_t result2d;
    fftconvolve(source2d, kernel2d, result2d);
    if(result2d.size() != 1) {
        std::cout << "MathFunctions::Convolve::fftconvolve -> Panic in 1d" << std::endl;
        throw std::runtime_error("Panic!");
    }
    result = result2d[0];
}


/* ************************************************************************* */
// initialise input and output arrays for fast fourier transformation
/* ************************************************************************* */
void MathFunctions::Convolve::init(int h_src, int w_src, int h_kernel, int w_kernel)
{
    ws.clear();
    ws.h_src = h_src;
    ws.w_src = w_src;
    ws.h_kernel = h_kernel;
    ws.w_kernel = w_kernel;
    switch(m_mode)
    {
    case FFTW_LINEAR_FULL:
        // Full Linear convolution
        ws.h_fftw = find_closest_factor(h_src + h_kernel - 1);
        ws.w_fftw = find_closest_factor(w_src + w_kernel - 1);
        ws.h_dst = h_src + h_kernel-1;
        ws.w_dst = w_src + w_kernel-1;
        break;
    case FFTW_LINEAR_SAME_UNPADDED:
        // Same Linear convolution
        ws.h_fftw = h_src + int(h_kernel/2.0);
        ws.w_fftw = w_src + int(w_kernel/2.0);
        ws.h_dst = h_src;
        ws.w_dst = w_src;
        break;
    case FFTW_LINEAR_SAME:
        // Same Linear convolution
        ws.h_fftw = find_closest_factor(h_src + int(h_kernel/2.0));
        ws.w_fftw = find_closest_factor(w_src + int(w_kernel/2.0));
        ws.h_dst = h_src;
        ws.w_dst = w_src;
        break;
    case FFTW_LINEAR_VALID:
        // Valid Linear convolution
        if(ws.h_kernel > ws.h_src || ws.w_kernel > ws.w_src)
        {
            ws.h_fftw = 0;
            ws.w_fftw = 0;
            ws.h_dst = 0;
            ws.w_dst = 0;
            std::cout << "The 'valid' convolution results in an empty matrix" << std::endl;
            throw std::runtime_error("The 'valid' convolution results in an empty matrix");
        } else {
            ws.h_fftw = find_closest_factor(h_src);
            ws.w_fftw = find_closest_factor(w_src);
            ws.h_dst = h_src - h_kernel+1;
            ws.w_dst = w_src - w_kernel+1;
        }
        break;
    case FFTW_CIRCULAR_SAME:
        // Circular convolution, modulo N
        // We don't padd with zeros because if we do, we need to padd with at least h_kernel/2; w_kernel/2 elements
        // plus the wrapp around
        // which in facts leads to too much computations compared to the gain obtained with the optimal size
        ws.h_fftw = h_src;
        ws.w_fftw = w_src;
        ws.h_dst = h_src;
        ws.w_dst = w_src;
        break;
    case FFTW_CIRCULAR_SAME_SHIFTED:
        // Circular convolution, modulo N, shifted by M/2
        // We don't padd with zeros because if we do, we need to padd with at least h_kernel/2; w_kernel/2 elements
        // plus the wrapp around
        // which in facts leads to too much computations compared to the gain obtained with the optimal size
        ws.h_fftw = h_src;
        ws.w_fftw = w_src;
        ws.h_dst = h_src;
        ws.w_dst = w_src;
        break;
    default:
        std::cout << "Unrecognized convolution mode, possible modes are FFTW_LINEAR_FULL, FFTW_LINEAR_SAME, FFTW_LINEAR_SAME_UNPADDED, FFTW_LINEAR_VALID, FFTW_CIRCULAR_SAME, FFTW_CIRCULAR_SHIFTED " << std::endl;
    }

    ws.in_src = new double[ws.h_fftw * ws.w_fftw];
    ws.out_src = (double*) fftw_malloc(sizeof(fftw_complex) * ws.h_fftw * (ws.w_fftw/2+1));
    ws.in_kernel = new double[ws.h_fftw * ws.w_fftw];
    ws.out_kernel = (double*) fftw_malloc(sizeof(fftw_complex) * ws.h_fftw * (ws.w_fftw/2+1));

    ws.dst_fft = new double[ws.h_fftw * ws.w_fftw];
    ws.dst = new double[ws.h_dst * ws.w_dst];

    // Initialization of the plans
    ws.p_forw_src = fftw_plan_dft_r2c_2d(ws.h_fftw, ws.w_fftw, ws.in_src, (fftw_complex*)ws.out_src, FFTW_ESTIMATE);
    if( ws.p_forw_src == NULL ) throw RuntimeErrorException("MathFunctions::Convolve::init() -> Error! Can't initialise p_forw_src plan.");

    ws.p_forw_kernel = fftw_plan_dft_r2c_2d(ws.h_fftw, ws.w_fftw, ws.in_kernel, (fftw_complex*)ws.out_kernel, FFTW_ESTIMATE);
    if( ws.p_forw_kernel == NULL ) throw RuntimeErrorException("MathFunctions::Convolve::init() -> Error! Can't initialise p_forw_kernel plan.");

    // The backward FFT takes ws.out_kernel as input
    ws.p_back = fftw_plan_dft_c2r_2d(ws.h_fftw, ws.w_fftw, (fftw_complex*)ws.out_kernel, ws.dst_fft, FFTW_ESTIMATE);
    if( ws.p_back == NULL ) throw RuntimeErrorException("MathFunctions::Convolve::init() -> Error! Can't initialise p_back plan.");


}


/* ************************************************************************* */
// initialise input and output arrays for fast fourier transformation
/* ************************************************************************* */
//void MathFunctions::Convolve::fftw_circular_convolution(double * src, double * kernel)
void MathFunctions::Convolve::fftw_circular_convolution(const double2d_t &src, const double2d_t &kernel)
{
    double * ptr, *ptr_end, *ptr2;

    // Reset the content of ws.in_src
    for(ptr = ws.in_src, ptr_end = ws.in_src + ws.h_fftw*ws.w_fftw ; ptr != ptr_end ; ++ptr)
        *ptr = 0.0;
    for(ptr = ws.in_kernel, ptr_end = ws.in_kernel + ws.h_fftw*ws.w_fftw ; ptr != ptr_end ; ++ptr)
        *ptr = 0.0;

    // Then we build our periodic signals
    //ptr = src;
    for(int i = 0 ; i < ws.h_src ; ++i)
        for(int j = 0 ; j < ws.w_src ; ++j, ++ptr)
            ws.in_src[(i%ws.h_fftw)*ws.w_fftw+(j%ws.w_fftw)] += src[i][j];
            //ws.in_src[(i%ws.h_fftw)*ws.w_fftw+(j%ws.w_fftw)] += src[i*ws.w_src + j];

    //ptr = kernel;
    for(int i = 0 ; i < ws.h_kernel ; ++i)
        for(int j = 0 ; j < ws.w_kernel ; ++j, ++ptr)
            ws.in_kernel[(i%ws.h_fftw)*ws.w_fftw+(j%ws.w_fftw)] += kernel[i][j];
            //ws.in_kernel[(i%ws.h_fftw)*ws.w_fftw+(j%ws.w_fftw)] += kernel[i*ws.w_kernel + j];

    // And we compute their packed FFT
    fftw_execute(ws.p_forw_src);
    fftw_execute(ws.p_forw_kernel);

    // Compute the element-wise product on the packed terms
    // Let's put the element wise products in ws.in_kernel
    double re_s, im_s, re_k, im_k;
    for(ptr = ws.out_src, ptr2 = ws.out_kernel, ptr_end = ws.out_src+2*ws.h_fftw * (ws.w_fftw/2+1); ptr != ptr_end ; ++ptr, ++ptr2)
    {
        re_s = *ptr;
        im_s = *(++ptr);
        re_k = *ptr2;
        im_k = *(++ptr2);
        *(ptr2-1) = re_s * re_k - im_s * im_k;
        *ptr2 = re_s * im_k + im_s * re_k;
    }

    // Compute the backward FFT
    // Carefull, The backward FFT does not preserve the output
    fftw_execute(ws.p_back);
    // Scale the transform
    for(ptr = ws.dst_fft, ptr_end = ws.dst_fft + ws.w_fftw*ws.h_fftw ; ptr != ptr_end ; ++ptr)
        *ptr /= double(ws.h_fftw*ws.w_fftw);

}



/* ************************************************************************* */
// initialise input and output arrays for fast fourier transformation
/* ************************************************************************* */
//void MathFunctions::Convolve::fftw_convolve(double * src,double * kernel)
void MathFunctions::Convolve::fftw_convolve(const double2d_t &src, const double2d_t &kernel)
{
    if(ws.h_fftw <= 0 || ws.w_fftw <= 0)
    {
        std::cout << "MathFunctions::Convolve::fftw_convolve() -> Panic! Initialisation is missed." << std::endl;
        throw std::runtime_error("MathFunctions::Convolve::fftw_convolve() -> Panic! Initialisation is missed.");
    }

    // Compute the circular convolution
    fftw_circular_convolution(src, kernel);

    // Depending on the type of convolution one is looking for, we extract the appropriate part of the result from out_src
    int h_offset(0), w_offset(0);

    switch(m_mode)
    {
    case FFTW_LINEAR_FULL:
        // Full Linear convolution
        // Here we just keep the first [0:h_dst-1 ; 0:w_dst-1] real part elements of out_src
        for(int i = 0 ; i < ws.h_dst  ; ++i)
            memcpy(&ws.dst[i*ws.w_dst], &ws.dst_fft[i*ws.w_fftw], ws.w_dst*sizeof(double));
        break;
    case FFTW_LINEAR_SAME_UNPADDED:
        // Same linear convolution
        // Here we just keep the first [h_filt/2:h_filt/2+h_dst-1 ; w_filt/2:w_filt/2+w_dst-1] real part elements of out_src
        h_offset = int(ws.h_kernel/2.0);
        w_offset = int(ws.w_kernel/2.0);
        for(int i = 0 ; i < ws.h_dst ; ++i)
            memcpy(&ws.dst[i*ws.w_dst], &ws.dst_fft[(i+h_offset)*ws.w_fftw+w_offset], ws.w_dst*sizeof(double));
        break;
    case FFTW_LINEAR_SAME:
        // Same linear convolution
        // Here we just keep the first [h_filt/2:h_filt/2+h_dst-1 ; w_filt/2:w_filt/2+w_dst-1] real part elements of out_src
        h_offset = int(ws.h_kernel/2.0);
        w_offset = int(ws.w_kernel/2.0);
        for(int i = 0 ; i < ws.h_dst ; ++i)
            memcpy(&ws.dst[i*ws.w_dst], &ws.dst_fft[(i+h_offset)*ws.w_fftw+w_offset], ws.w_dst*sizeof(double));
        break;
    case FFTW_LINEAR_VALID:
        // Valid linear convolution
        // Here we just take [h_dst x w_dst] elements starting at [h_kernel-1;w_kernel-1]
        h_offset = ws.h_kernel - 1;
        w_offset = ws.w_kernel - 1;
        for(int i = 0 ; i < ws.h_dst ; ++i)
            memcpy(&ws.dst[i*ws.w_dst], &ws.dst_fft[(i+h_offset)*ws.w_fftw+w_offset], ws.w_dst*sizeof(double));
        break;
    case FFTW_CIRCULAR_SAME:
        // Circular convolution
        // We copy the first [0:h_dst-1 ; 0:w_dst-1] real part elements of out_src
        for(int i = 0 ; i < ws.h_dst ; ++i)
            memcpy(&ws.dst[i*ws.w_dst], &ws.dst_fft[i*ws.w_fftw], ws.w_dst*sizeof(double) );
        break;
    case FFTW_CIRCULAR_SAME_SHIFTED:
        // Shifted Circular convolution
        // We copy the [h_kernel/2:h_kernel/2+h_dst-1 ; w_kernel/2:w_kernel/2+w_dst-1] real part elements of out_src
        for(int i = 0 ; i < ws.h_dst ; ++i)
            for(int j = 0 ; j < ws.w_dst ; ++j)
                ws.dst[i*ws.w_dst + j] = ws.dst_fft[((i+int(ws.h_kernel/2.0))%ws.h_fftw)*ws.w_fftw+(j+int(ws.w_kernel/2.0))%ws.w_fftw];
        break;
    default:
        std::cout << "Unrecognized convolution mode, possible modes are FFTW_LINEAR_FULL, FFTW_LINEAR_SAME, FFTW_LINEAR_SAME_UNPADDED, FFTW_LINEAR_VALID, FFTW_CIRCULAR_SAME, FFTW_CIRCULAR_SHIFTED " << std::endl;
    }
}



/* ************************************************************************* */
// find a number closest to the given one, which  can be factorised according
// to fftw3 favorite factorisation
/* ************************************************************************* */
int MathFunctions::Convolve::find_closest_factor(int n)
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
bool MathFunctions::Convolve::is_optimal(int n)
{
    if(n==1) return false;
    int ntest = n;
    for(size_t i=0; i<m_implemented_factors.size(); i++){
        while( (ntest%m_implemented_factors[i]) == 0 ) {
            ntest = ntest/m_implemented_factors[i];
        }
    }
    if(ntest==1) return true;
    return false;
}





/////////////////
///
///


// ******************** Begin of factorization code ***********************//
// A piece of code to determine if a number "n" can be written as products of only the integers given in implemented_factors
void factorize (const int n,
                int *n_factors,
                int factors[],
                int * implemented_factors)
{
    int nf = 0;
    int ntest = n;
    int factor;
    int i = 0;

    if (n == 0)
    {
        printf("Length n must be positive integer\n");
        return ;
    }

    if (n == 1)
    {
        factors[0] = 1;
        *n_factors = 1;
        return ;
    }

    /* deal with the implemented factors */

    while (implemented_factors[i] && ntest != 1)
    {
        factor = implemented_factors[i];
        while ((ntest % factor) == 0)
        {
            ntest = ntest / factor;
            factors[nf] = factor;
            nf++;
        }
        i++;
    }

    // Ok that's it
    if(ntest != 1)
    {
        factors[nf] = ntest;
        nf++;
    }

    /* check that the factorization is correct */
    {
        int product = 1;

        for (i = 0; i < nf; i++)
        {
            product *= factors[i];
        }

        if (product != n)
        {
            printf("factorization failed");
        }
    }

    *n_factors = nf;
}

bool is_optimal(int n, int * implemented_factors)
{
    int nf;
    int factors[64];
    int i = 0;
    factorize(n, &nf, factors,implemented_factors);

    // We just have to check if the last factor belongs to GSL_FACTORS
    while(implemented_factors[i])
    {
        if(factors[nf-1] == implemented_factors[i])
            return true;
        ++i;
    }
    return false;
}

int find_closest_factor(int n, int * implemented_factor)
{
    int j;
    if(is_optimal(n,implemented_factor))
        return n;
    else
    {
        j = n+1;
        while(!is_optimal(j,implemented_factor))
            ++j;
        return j;
    }
}
// ******************** End of factorization code ***********************//

int FFTW_FACTORS[7] = {13,11,7,5,3,2,0}; // end with zero to detect the end of the array


void init_workspace_fftw(FFTW_Workspace & ws, FFTW_Convolution_Mode mode, int h_src, int w_src, int h_kernel, int w_kernel)
{
    ws.h_src = h_src;
    ws.w_src = w_src;
    ws.h_kernel = h_kernel;
    ws.w_kernel = w_kernel;
    ws.mode = mode;

    switch(mode)
    {
    case FFTW_LINEAR_FULL:
        // Full Linear convolution
        ws.h_fftw = find_closest_factor(h_src + h_kernel - 1,FFTW_FACTORS);
        ws.w_fftw = find_closest_factor(w_src + w_kernel - 1,FFTW_FACTORS);
        ws.h_dst = h_src + h_kernel-1;
        ws.w_dst = w_src + w_kernel-1;
        break;
    case FFTW_LINEAR_SAME_UNPADDED:
        // Same Linear convolution
        ws.h_fftw = h_src + int(h_kernel/2.0);
        ws.w_fftw = w_src + int(w_kernel/2.0);
        ws.h_dst = h_src;
        ws.w_dst = w_src;
        break;
    case FFTW_LINEAR_SAME:
        // Same Linear convolution
        ws.h_fftw = find_closest_factor(h_src + int(h_kernel/2.0),FFTW_FACTORS);
        ws.w_fftw = find_closest_factor(w_src + int(w_kernel/2.0),FFTW_FACTORS);
        ws.h_dst = h_src;
        ws.w_dst = w_src;
        break;
    case FFTW_LINEAR_VALID:
        // Valid Linear convolution
        if(ws.h_kernel > ws.h_src || ws.w_kernel > ws.w_src)
        {
            printf("Warning : The 'valid' convolution results in an empty matrix\n");
            ws.h_fftw = 0;
            ws.w_fftw = 0;
            ws.h_dst = 0;
            ws.w_dst = 0;
        }
        else
        {
            ws.h_fftw = find_closest_factor(h_src, FFTW_FACTORS);
            ws.w_fftw = find_closest_factor(w_src, FFTW_FACTORS);
            ws.h_dst = h_src - h_kernel+1;
            ws.w_dst = w_src - w_kernel+1;
        }
        break;
    case FFTW_CIRCULAR_SAME:
        // Circular convolution, modulo N
        // We don't padd with zeros because if we do, we need to padd with at least h_kernel/2; w_kernel/2 elements
        // plus the wrapp around
        // which in facts leads to too much computations compared to the gain obtained with the optimal size
        ws.h_fftw = h_src;
        ws.w_fftw = w_src;
        ws.h_dst = h_src;
        ws.w_dst = w_src;
        break;
    case FFTW_CIRCULAR_SAME_SHIFTED:
        // Circular convolution, modulo N, shifted by M/2
        // We don't padd with zeros because if we do, we need to padd with at least h_kernel/2; w_kernel/2 elements
        // plus the wrapp around
        // which in facts leads to too much computations compared to the gain obtained with the optimal size
        ws.h_fftw = h_src;
        ws.w_fftw = w_src;
        ws.h_dst = h_src;
        ws.w_dst = w_src;
        break;
    case FFTW_CIRCULAR_CUSTOM:
        // We here want to compute a circular convolution modulo h_dst, w_dst
        // These two variables must have been set before calling init_workscape !!
        ws.h_fftw = ws.h_dst;
        ws.w_fftw = ws.w_dst;
        break;
    default:
        printf("Unrecognized convolution mode, possible modes are :\n");
        printf("   - FFTW_LINEAR_FULL \n");
        printf("   - FFTW_LINEAR_SAME \n");
        printf("   - FFTW_LINEAR_SAME_UNPADDED\n");
        printf("   - FFTW_LINEAR_VALID \n");
        printf("   - FFTW_CIRCULAR_SAME \n");
        printf("   - FFTW_CIRCULAR_SHIFTED\n");
        printf("   - FFTW_CIRCULAR_CUSTOM\n");
    }

    ws.in_src = new double[ws.h_fftw * ws.w_fftw];
    ws.out_src = (double*) fftw_malloc(sizeof(fftw_complex) * ws.h_fftw * (ws.w_fftw/2+1));
    ws.in_kernel = new double[ws.h_fftw * ws.w_fftw];
    ws.out_kernel = (double*) fftw_malloc(sizeof(fftw_complex) * ws.h_fftw * (ws.w_fftw/2+1));

    ws.dst_fft = new double[ws.h_fftw * ws.w_fftw];
    ws.dst = new double[ws.h_dst * ws.w_dst];

    // Initialization of the plans
    ws.p_forw_src = fftw_plan_dft_r2c_2d(ws.h_fftw, ws.w_fftw, ws.in_src, (fftw_complex*)ws.out_src, FFTW_ESTIMATE);
    ws.p_forw_kernel = fftw_plan_dft_r2c_2d(ws.h_fftw, ws.w_fftw, ws.in_kernel, (fftw_complex*)ws.out_kernel, FFTW_ESTIMATE);

    // The backward FFT takes ws.out_kernel as input !!
    ws.p_back = fftw_plan_dft_c2r_2d(ws.h_fftw, ws.w_fftw, (fftw_complex*)ws.out_kernel, ws.dst_fft, FFTW_ESTIMATE);
}

void clear_workspace_fftw(FFTW_Workspace & ws)
{
    delete[] ws.in_src;
    fftw_free((fftw_complex*)ws.out_src);
    delete[] ws.in_kernel;
    fftw_free((fftw_complex*)ws.out_kernel);

    delete[] ws.dst_fft;
    delete[] ws.dst;

    // Destroy the plans
    fftw_destroy_plan(ws.p_forw_src);
    fftw_destroy_plan(ws.p_forw_kernel);
    fftw_destroy_plan(ws.p_back);
}

// Compute the circular convolution of src and kernel modulo ws.h_fftw, ws.w_fftw
// using the Fast Fourier Transform
// The result is in ws.dst
void fftw_circular_convolution(FFTW_Workspace &ws, double * src, double * kernel)
{
    double * ptr, *ptr_end, *ptr2;

    // Reset the content of ws.in_src
    for(ptr = ws.in_src, ptr_end = ws.in_src + ws.h_fftw*ws.w_fftw ; ptr != ptr_end ; ++ptr)
        *ptr = 0.0;
    for(ptr = ws.in_kernel, ptr_end = ws.in_kernel + ws.h_fftw*ws.w_fftw ; ptr != ptr_end ; ++ptr)
        *ptr = 0.0;

    // Then we build our periodic signals
    //ptr = src;
    for(int i = 0 ; i < ws.h_src ; ++i)
        for(int j = 0 ; j < ws.w_src ; ++j, ++ptr)
            ws.in_src[(i%ws.h_fftw)*ws.w_fftw+(j%ws.w_fftw)] += src[i*ws.w_src + j];
    //ptr = kernel;
    for(int i = 0 ; i < ws.h_kernel ; ++i)
        for(int j = 0 ; j < ws.w_kernel ; ++j, ++ptr)
            ws.in_kernel[(i%ws.h_fftw)*ws.w_fftw+(j%ws.w_fftw)] += kernel[i*ws.w_kernel + j];

    // And we compute their packed FFT
    fftw_execute(ws.p_forw_src);
    fftw_execute(ws.p_forw_kernel);

    // Compute the element-wise product on the packed terms
    // Let's put the element wise products in ws.in_kernel
    double re_s, im_s, re_k, im_k;
    for(ptr = ws.out_src, ptr2 = ws.out_kernel, ptr_end = ws.out_src+2*ws.h_fftw * (ws.w_fftw/2+1); ptr != ptr_end ; ++ptr, ++ptr2)
    {
        re_s = *ptr;
        im_s = *(++ptr);
        re_k = *ptr2;
        im_k = *(++ptr2);
        *(ptr2-1) = re_s * re_k - im_s * im_k;
        *ptr2 = re_s * im_k + im_s * re_k;
    }

    // Compute the backward FFT
    // Carefull, The backward FFT does not preserve the output
    fftw_execute(ws.p_back);
    // Scale the transform
    for(ptr = ws.dst_fft, ptr_end = ws.dst_fft + ws.w_fftw*ws.h_fftw ; ptr != ptr_end ; ++ptr)
        *ptr /= double(ws.h_fftw*ws.w_fftw);

    // That's it !
}

void fftw_convolve(FFTW_Workspace &ws, double * src,double * kernel)
{
    if(ws.h_fftw <= 0 || ws.w_fftw <= 0)
        return;

    // Compute the circular convolution
    fftw_circular_convolution(ws, src, kernel);

    // Depending on the type of convolution one is looking for, we extract the appropriate part of the result from out_src
    int h_offset, w_offset;

//    double * dst_ptr;
//    double * src_ptr;
    switch(ws.mode)
    {
    case FFTW_LINEAR_FULL:
        // Full Linear convolution
        // Here we just keep the first [0:h_dst-1 ; 0:w_dst-1] real part elements of out_src
        for(int i = 0 ; i < ws.h_dst  ; ++i)
            memcpy(&ws.dst[i*ws.w_dst], &ws.dst_fft[i*ws.w_fftw], ws.w_dst*sizeof(double));
        break;
    case FFTW_LINEAR_SAME_UNPADDED:
        // Same linear convolution
        // Here we just keep the first [h_filt/2:h_filt/2+h_dst-1 ; w_filt/2:w_filt/2+w_dst-1] real part elements of out_src
        h_offset = int(ws.h_kernel/2.0);
        w_offset = int(ws.w_kernel/2.0);
        for(int i = 0 ; i < ws.h_dst ; ++i)
            memcpy(&ws.dst[i*ws.w_dst], &ws.dst_fft[(i+h_offset)*ws.w_fftw+w_offset], ws.w_dst*sizeof(double));
            //for(int j = 0 ; j < ws.w_dst ; ++j)
             //   ws.dst[i*ws.w_dst + j] = ws.out_src[2*((i+h_offset)*ws.w_fftw+j+w_offset)+0]/double(ws.w_fftw * ws.h_fftw);
        break;
    case FFTW_LINEAR_SAME:
        // Same linear convolution
        // Here we just keep the first [h_filt/2:h_filt/2+h_dst-1 ; w_filt/2:w_filt/2+w_dst-1] real part elements of out_src
        h_offset = int(ws.h_kernel/2.0);
        w_offset = int(ws.w_kernel/2.0);
        for(int i = 0 ; i < ws.h_dst ; ++i)
            memcpy(&ws.dst[i*ws.w_dst], &ws.dst_fft[(i+h_offset)*ws.w_fftw+w_offset], ws.w_dst*sizeof(double));
        break;
    case FFTW_LINEAR_VALID:
        // Valid linear convolution
        // Here we just take [h_dst x w_dst] elements starting at [h_kernel-1;w_kernel-1]
        h_offset = ws.h_kernel - 1;
        w_offset = ws.w_kernel - 1;
        for(int i = 0 ; i < ws.h_dst ; ++i)
            memcpy(&ws.dst[i*ws.w_dst], &ws.dst_fft[(i+h_offset)*ws.w_fftw+w_offset], ws.w_dst*sizeof(double));
        break;
    case FFTW_CIRCULAR_SAME:
        // Circular convolution
        // We copy the first [0:h_dst-1 ; 0:w_dst-1] real part elements of out_src
        for(int i = 0 ; i < ws.h_dst ; ++i)
            memcpy(&ws.dst[i*ws.w_dst], &ws.dst_fft[i*ws.w_fftw], ws.w_dst*sizeof(double) );
        break;
    case FFTW_CIRCULAR_SAME_SHIFTED:
        // Shifted Circular convolution
        // We copy the [h_kernel/2:h_kernel/2+h_dst-1 ; w_kernel/2:w_kernel/2+w_dst-1] real part elements of out_src
        for(int i = 0 ; i < ws.h_dst ; ++i)
            for(int j = 0 ; j < ws.w_dst ; ++j)
                ws.dst[i*ws.w_dst + j] = ws.dst_fft[((i+int(ws.h_kernel/2.0))%ws.h_fftw)*ws.w_fftw+(j+int(ws.w_kernel/2.0))%ws.w_fftw];
        break;
    case FFTW_CIRCULAR_CUSTOM:
        for(int i = 0 ; i < ws.h_dst ; ++i)
            memcpy(&ws.dst[i*ws.w_dst], &ws.dst_fft[i*ws.w_fftw], ws.w_dst*sizeof(double) );
        break;
    default:
        printf("Unrecognized convolution mode, possible modes are :\n");
        printf("   - FFTW_LINEAR_FULL \n");
        printf("   - FFTW_LINEAR_SAME \n");
        printf("   - FFTW_LINEAR_SAME_UNPADDED\n");
        printf("   - FFTW_LINEAR_VALID \n");
        printf("   - FFTW_CIRCULAR_SAME \n");
        printf("   - FFTW_CIRCULAR_SHIFTED\n");
        printf("   - FFTW_CIRCULAR_CUSTOM\n");
    }
}

