// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestRoughness.cpp
//! @brief     Implements class TestRoughness.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestRoughness.h"
#include "LayerRoughness.h"
#include "MathFunctions.h"

#include <stdexcept>
#include <sstream>
#include <iomanip>

#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TRandom.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompChol.h"
#include "TLatex.h"
#include "TLegend.h"

#include <fftw3.h>


void TestRoughness::execute()
{
    //test_FFT();

    // draw surface profile using different methods for calculation of correlated random numbers
    m_TestMethods.push_back(& TestRoughness::GetProfileXZ_MatrixMethod );
    m_TestMethods.push_back(& TestRoughness::GetProfileXZ_FFTMethod );
    DrawProfile();
}


/* ************************************************************************* */
// Draw surface profile for several different roughness parameters using
// known correlation function of roughness profile.
/* ************************************************************************* */
void TestRoughness::DrawProfile()
{
    // our roughness
    m_roughness = new LayerRoughness();

    // several sets of parameters describing roughness of surface
    const double sigma = 1.0;
    struct RoughnessData {
        double sigma;
        double hurst;
        double clength;
    };
    RoughnessData roughnessSet[] = { {sigma, 0.2, 100.}, {sigma, 0.5, 100.}, {sigma, 0.8, 100.},
                                     {sigma, 0.8,   25.}, {sigma, 0.8,  100.}, {sigma, 0.8,  500.} };

    // defining x-grid for surface
    double xmin(-500.0);
    double xmax(500.0);
    int npx = 201;
    double dx = (xmax-xmin)/(npx-1);

    // filling arrays for surface with x-coordinates and uncorrelated random z-heights
    TRandom mr(1);
    m_vx.clear();
    m_vx.resize(npx, 0);
    m_vzuncorr.clear();
    m_vzuncorr.resize(npx, 0);
    for(int i=0; i<npx; i++) {
        m_vx[i] = xmin + i*dx;
        m_vzuncorr[i] = mr.Gaus(0,sigma);
    }

    // run through different sets of roughnes parameters and calculation methods
    // and calculate z-profile of surface
    size_t nsets = int(sizeof(roughnessSet)/sizeof(RoughnessData));
    size_t nmethods = m_TestMethods.size();

    std::vector<std::vector<TGraph *> > vgr_profile; // [nmethods][nsets]
    vgr_profile.resize(nmethods);
    for(size_t i_method=0; i_method<nmethods; i_method++) {
        vgr_profile[i_method].resize(nsets, 0);
        for(size_t i_set=0; i_set<nsets; i_set++) {
            m_roughness->setSigma( roughnessSet[i_set].sigma );
            m_roughness->setHurstParameter( roughnessSet[i_set].hurst );
            m_roughness->setLatteralCorrLength( roughnessSet[i_set].clength );

            TestMethod method = m_TestMethods[i_method];
            (this->*method)();

            vgr_profile[i_method][i_set] = new TGraph(npx, &m_vx[0], &m_vzcorr[0]);
        }
    }

    // making drawing
    TCanvas *c1 = new TCanvas("c1_test_roughness","Surface Roughness Profile",1024, 768);
    c1->Divide(2,3);

    TH1F *href = new TH1F("h1","h1",npx, xmin, xmax);
    href->SetMinimum(-sigma*4);
    href->SetMaximum(sigma*4);
    href->SetStats(0);
    href->SetTitle("");
    href->GetXaxis()->SetTitle("X, [A]");
    href->GetYaxis()->SetTitle("Z, [A]");
    href->SetLineWidth(0);

    TLatex tex;
    tex.SetNDC();
    tex.SetTextSize(0.08);
    tex.SetTextColor(kBlue);

    TLegend *leg = new TLegend(0.2,0.25,0.425,0.4);
    leg->SetTextSize(0.04);
    leg->SetBorderSize(1);
    leg->SetFillStyle(0);
    leg->AddEntry(vgr_profile[0][0], "matrix method","pl");
    leg->AddEntry(vgr_profile[1][0], "FFT method","pl");

    // loop over test methods and set of roughnesses
    int a_colors[]={kBlue, kRed, kGreen+1, kBlue, kRed, kGreen+1};
    for(size_t i_method=0; i_method<nmethods; i_method++){
        for(size_t i_set=0; i_set<nsets; i_set++) {
            if(i_set<3) {
                c1->cd(1+(int)i_set*2); // i_set=0,1,2 will be on the left side of canvas
            }else{
                c1->cd(2+((int)i_set-3)*2); // i_set=3,4,5 will be on the right side of canvas
            }

            if(i_method==0) { // draw reference histogram per set only once
                std::ostringstream out;
                out << "#sigma: " << std::setprecision(3) << roughnessSet[i_set].sigma
                    << "   H: " << std::setprecision(3) << roughnessSet[i_set].hurst
                    << "   L_{c}:" << std::setprecision(5) << roughnessSet[i_set].clength;
                href->Draw("][");
                tex.DrawLatex(0.58,0.8, out.str().c_str());
                leg->Draw();
            }
            TGraph *gr = vgr_profile[i_method][i_set];
            gr->SetLineColor( a_colors[i_method] );
            gr->SetMarkerColor( a_colors[i_method] );
            gr->Draw("l");
        } // i_set
    } // i_method


    // ---------------------
    int i_method_sel = 1;
//    TCanvas *c2 = new TCanvas("c2_test_roughness","Surface Roughness Profile",900, 600);
    TCanvas *c2 = new TCanvas("c2_test_roughness","Surface Roughness Profile",550, 500);
    c2->Divide(1,2);

    std::vector<TLegend *> legends;
    for(size_t i=0; i<2; ++i) {
//        TLegend *leg = new TLegend(0.725,0.6,0.915,0.9);
        TLegend *leg = new TLegend(0.65,0.6,0.92,0.9);
        leg->SetTextSize(0.05);
        leg->SetBorderSize(1);
        leg->SetFillStyle(0);
        legends.push_back(leg);

        c2->cd(1+i);
        gPad->SetLeftMargin(0.05);
        gPad->SetRightMargin(0.05);
        gPad->SetTopMargin(0.05);
        href->Draw("][");
        leg->Draw();
    }


    for(size_t i_set=0; i_set<nsets; i_set++) {
        int ncomp = i_set/3;
        c2->cd(1+ncomp);
        TGraph *gr = vgr_profile[i_method_sel][i_set];
        gr->SetLineColor( a_colors[i_set] );
        gr->SetMarkerColor( a_colors[i_set] );
        gr->Draw("l");



        std::ostringstream out;
        out << "#sigma: " << std::setprecision(3) << roughnessSet[i_set].sigma
            << "   H: " << std::setprecision(3) << roughnessSet[i_set].hurst
            << "   L_{c}:" << std::setprecision(5) << roughnessSet[i_set].clength;

        std::cout << "XXX" << ncomp << " " << out.str() << std::endl;
        legends[ncomp]->AddEntry(gr, out.str().c_str(),"pl");


    }





    delete m_roughness;
    m_roughness = 0;
}


/* ************************************************************************* */
// Matrix method to obtain correlated sequence of random numbers.
// ROOT library used for matrix algebra.
//
// C our covariance matrix, it can be decomposed C=A^{T}*A
// then for uncorrelated variables W, correlated values Z are obtained with
// Z = A*W
/* ************************************************************************* */
void TestRoughness::GetProfileXZ_MatrixMethod()
{
    int npx = (int)m_vx.size();
    m_vzcorr.clear();
    m_vzcorr.resize(npx, 0);

    TMatrixD Corr(npx,npx);
    for(int i=0; i<npx; i++){
        kvector_t k1(m_vx[i], 0, 0);
        for(int k=0; k<npx; k++){
            kvector_t k2(m_vx[k], 0, 0);
            Corr[i][k]=m_roughness->getCorrFun(k2-k1);
            //Corr[i][k]=sigma*sigma*std::exp(-std::pow( std::abs(vx[i]-vx[k])/clength, 2*hurst) );
        }
    }

    TDecompChol chol(Corr);
    if( !chol.Decompose() ) {
        std::cout << "TestRoughness::GetProfileXZ() -> Panic! Can't decompose matrix." << std::endl;
        throw std::runtime_error("TestRoughness::GetProfileXZ() -> Panic! Can't decompose matrix.");
    }

    TVectorD zUnCorr(npx, &m_vzuncorr[0]);
    TVectorD zCorr(npx);
    zCorr = (chol.GetU()) * zUnCorr;

    for(int i=0; i<npx; i++) m_vzcorr[i] = zCorr[i];
}


/* ************************************************************************* */
// Fast Fourier Transform method to obtain correlated sequence of random numbers.
// fftw3 library is used for Fourier analysis.
//
// Algorithm is described in:
// The FFT Moving Average (FFT-MA) Generator:
// An Efficient Numerical Method for Generating and Conditioning Gaussian Simulations
// Mickaele Le Ravalec, Benoit Noetinger, Lin Y. Hu
// Mathematical Geology, Vol.32, No.6, 2000
/* ************************************************************************* */
void TestRoughness::GetProfileXZ_FFTMethod()
{
    // preparing array for rezults
    size_t npx = m_vx.size();
    m_vzcorr.clear();
    m_vzcorr.resize(npx, 0);

    // generating symmetric covariance function
    std::vector<double > cov;
    cov.resize(npx, 0);
    kvector_t k1(m_vx[0], 0, 0);
    for(size_t i=0; i<=npx/2; i++) {
        kvector_t k2(m_vx[i], 0, 0);
        cov[i] =m_roughness->getCorrFun(k2-k1);
        cov[npx-1-i] = cov[i];
    }

    // making Fourier transform of covariance and z values
    std::vector<complex_t > ft_cov = MathFunctions::FastFourierTransform(cov, MathFunctions::FORWARD_FFT);
    std::vector<complex_t> ft_z = MathFunctions::FastFourierTransform(m_vzuncorr, MathFunctions::FORWARD_FFT);

    std::vector<complex_t > ft_result;
    ft_result.resize(npx);
    for(size_t i=0; i<npx; i++) {
        ft_result[i] = ft_z[i] * std::sqrt(ft_cov[i]);
    }

    // inverse transform to find correlated sequenced of random numbers
    std::vector<complex_t > ift_result = MathFunctions::FastFourierTransform(ft_result, MathFunctions::BACKWARD_FFT);

    for(size_t i=0; i<npx; i++){
        m_vzcorr[i] = ift_result[i].real();
    }
}



//double TestRoughness::SurfaceFractalCurve1(double *xargs, double *pars)
//{
//    double x = xargs[0];
//    unsigned kmax = int(pars[0]);

//    double sum(0);
//    for(size_t k=0; k<kmax; k++)
//    {
//        sum += std::pow((3./2.), -1*double(k)/2.)*std::sin(  std::pow((3./2.), double(k))*x);
//    }
//    std::cout << "x:" << x << " kmax:" << kmax << " sum:" << sum << std::endl;
//    return sum;
//}



/* ************************************************************************* */
// test of Fast Fourier Transform by fftw3 library
/* ************************************************************************* */
void TestRoughness::test_FFT()
{
    double lambda=1.0;
    TCanvas *c1 = new TCanvas("c1", "c1", 1024, 768);
    c1->Divide(3,3);

    c1->cd(1);
    double xmin(-10.0), xmax(10.0);
    size_t npx(101);
    double dx1 = (xmax-xmin)/(npx-1);
    //double df1 = 1/double(npx-1)/dx1;
    double df1 = 1/(2.*dx1*(npx-1));
    TF1 *fcor = new TF1("fcor","exp(-x*x*[0])", xmin, xmax);
    fcor->SetParameter(0, lambda);
    fcor->SetNpx((int)npx);
    fcor->Draw();

    double fmin(-1./2./dx1), fmax(1./2./dx1);
    TF1 *FT_fcor = new TF1("FT_fcor","0.5*sqrt(3.1415926/[0])*exp(-(2*3.1415926*x)*(2*3.1415926*x)/4/[0])", fmin, fmax); //  0.5*sqrt(pi/a)*exp(-(2.*pi*f)**2/(4.*a))
    lambda=1;
    FT_fcor->SetParameter(0, lambda);
    FT_fcor->SetNpx((int)npx);
    c1->cd(2);
    FT_fcor->Draw();

    fftw_complex *data, *fft_result, *ifft_result;
    fftw_plan plan_forward, plan_backward;

    data = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * npx);
    fft_result = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * npx);
    ifft_result = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * npx);

    memset(data, 0, sizeof(fftw_complex) * npx);
    memset(fft_result, 0, sizeof(fftw_complex) * npx);
    memset(ifft_result, 0, sizeof(fftw_complex) * npx);
    for(size_t i=0; i<npx; i++){
        double x = xmin + i*(xmax-xmin)/(npx-1);
        data[i][0] = fcor->Eval(x);
    }

    std::cout << "forward" << std::endl;
    plan_forward  = fftw_plan_dft_1d( (int)npx, data, fft_result, FFTW_FORWARD, FFTW_ESTIMATE );
    plan_backward = fftw_plan_dft_1d( (int)npx, fft_result, ifft_result, FFTW_BACKWARD, FFTW_ESTIMATE );

    fftw_execute(plan_forward);

    for(size_t i=0; i<npx; i++){
        complex_t c_out(fft_result[i][0], fft_result[i][1]);
        std::cout << i << " " << " data:"  << data[i][0] << " " << data[i][1] << " result:" << c_out << std::endl;
    }

    TGraph *gr_fftw_fcor = new TGraph();
    for(size_t i=0; i<npx; i++){
        complex_t c_out(fft_result[i][0]/sqrt(npx), fft_result[i][1]/sqrt(npx));
        gr_fftw_fcor->SetPoint((int)i, double(i)*df1, std::abs(c_out));
    }
    c1->cd(3);
    gr_fftw_fcor->Draw("apl");

    fftw_execute(plan_backward);

    std::cout << "---" << std::endl;
    for(size_t i=0; i<npx; i++){
        complex_t c_out(ifft_result[i][0]/npx, ifft_result[i][1]/npx);
        std::cout << i << " " << " data:"  << data[i][0] << " " << data[i][1] << " result:" << c_out << " " << std::abs(c_out) << std::endl;
    }

    TGraph *gr_ifftw_fcor = new TGraph();
    for(size_t i=0; i<npx; i++){
        complex_t c_out(ifft_result[i][0]/npx, ifft_result[i][1]/npx);
        gr_ifftw_fcor->SetPoint((int)i, double(i), std::abs(c_out));
    }
    c1->cd(4);
    gr_ifftw_fcor->Draw("apl");

    fftw_destroy_plan(plan_forward);
    fftw_destroy_plan(plan_backward);
    fftw_free(data);
    fftw_free(fft_result);
    fftw_free(ifft_result);
}


