// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestConvolution.cpp
//! @brief     Implements class TestConvolution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestConvolution.h"
#include "MathFunctions.h"
#include "Convolve.h"
#include "DrawHelper.h"

#include <iostream>

#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TF2.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TGraph.h"
#include "TBenchmark.h"
#include "TStyle.h"
#include "TText.h"

TestConvolution::TestConvolution()
: m_npeaks(0)
{
    std::cout << "TestConvolution::TestConvolution() -> Info." << std::endl;

    m_modes.push_back( mode_pair_t("LINEAR_FULL", MathFunctions::Convolve::FFTW_LINEAR_FULL));
    m_modes.push_back( mode_pair_t("LINEAR_SAME_UNPADDED", MathFunctions::Convolve::FFTW_LINEAR_SAME_UNPADDED));
    m_modes.push_back( mode_pair_t("LINEAR_SAME", MathFunctions::Convolve::FFTW_LINEAR_SAME));
    m_modes.push_back( mode_pair_t("CIRCULAR_SAME", MathFunctions::Convolve::FFTW_CIRCULAR_SAME));
    m_modes.push_back( mode_pair_t("CIRCULAR_SAME_SHIFTED", MathFunctions::Convolve::FFTW_CIRCULAR_SAME_SHIFTED));
}

void TestConvolution::execute()
{

    test_convolve1d();

    test_convolve2d();

    /*
    --- TestConvolution::test_convolve_1d() -> Peformance.
    LINEAR_FULL: Real Time =   0.37 seconds Cpu Time =   0.37 seconds
    LINEAR_SAME_UNPADDED: Real Time =   0.98 seconds Cpu Time =   0.98 seconds
    LINEAR_SAME: Real Time =   0.22 seconds Cpu Time =   0.22 seconds
    CIRCULAR_SAME: Real Time =   0.51 seconds Cpu Time =   0.50 seconds
    CIRCULAR_SAME_SHIFTED: Real Time =   0.51 seconds Cpu Time =   0.51 seconds

    --- TestConvolution::test_convolve_2d() -> Peformance.
    LINEAR_FULL: Real Time =   1.26 seconds Cpu Time =   1.26 seconds
    LINEAR_SAME_UNPADDED: Real Time =   0.76 seconds Cpu Time =   0.76 seconds
    LINEAR_SAME: Real Time =   0.73 seconds Cpu Time =   0.73 seconds
    CIRCULAR_SAME: Real Time =   0.57 seconds Cpu Time =   0.57 seconds
    CIRCULAR_SAME_SHIFTED: Real Time =   0.62 seconds Cpu Time =   0.63 seconds
    */

}

//! Test of convolution of two arrays in 1d.

void TestConvolution::test_convolve1d()
{
    double xmin(0.0);
    double xmax(1000.);
    size_t npoints = 501;
    double dx = (xmax-xmin)/double(npoints-1);
    double sigmax=(xmax-xmin)*0.01; // precision of the measurement of x-value

    // generate signal (n gaus peaks at random on top of flat background)
    std::vector<double > signal;
    m_npeaks = 10;
    double *par = new double[m_npeaks*3+2];
    par[0] = 1.0;
    par[1] = -0.6/(xmax-xmin);
    for (int i_par=0; i_par<m_npeaks;i_par++) {
       par[3*i_par+2] = 1;
       par[3*i_par+3] = (xmax-xmin)*0.01+gRandom->Rndm()*(xmax-xmin);
       par[3*i_par+4] = sigmax/5.+sigmax*gRandom->Rndm();
    }
    TF1 *fsignal = new TF1("f",this, &TestConvolution::fpeaks, xmin, xmax,2+3*m_npeaks, "TestConvolution","fpeaks");
    fsignal->SetNpx(10000);
    fsignal->SetParameters(par);
    signal.resize(npoints);
    for(size_t i=0; i<npoints; i++) {
        double x = xmin + i*dx;
        signal[i] = fsignal->Eval(x);
    }

    // building kernel
    std::vector<double> kernel;
    kernel.resize(npoints);
    TGraph *gr_kernel = new TGraph((int)npoints);
//    for(size_t i=0; i<npoints/2; i++) {
//        double x = i*dx;
//        double y = std::exp(-x*x/sigma_measure/sigma_measure);
//        kernel[i] = y;
//        kernel[npoints-1-i] = kernel[i];
//    }
    for(size_t i=0; i<npoints; i++) {
        double x = -(xmax-xmin)/2.+i*dx;
        double y = std::exp(-x*x/sigmax/sigmax);
        kernel[i] = y;
        gr_kernel->SetPoint((int)i,x,kernel[i]);
    }

    // --------------
    // drawing
    // --------------
    TCanvas *c1 = new TCanvas("c1_test_convolve1d","c1_test_convolve1d",1024, 768);
    DrawHelper::SetMagnifier(c1);
    c1->Divide(3,3);

    // drawing signal
    c1->cd(1);
    gPad->SetTopMargin(0.1);
    TH1F *href = new TH1F("h","test", (int)npoints-1, xmin, xmax);
    href->SetMinimum(0.0);
    href->SetMaximum(2.0);
    href->SetStats(0);
    href->DrawCopy();
    href->SetBit(TH1::kNoTitle, false);
    fsignal->SetTitle("signal");
    fsignal->Draw("pl same");

    // drawing measured signal
    c1->cd(2);
    gPad->SetTopMargin(0.1);
    TH1F *hmeasured = new TH1F("hmeasured","hmeasured",500, xmin, xmax);
    for(int i=0; i<1000000; i++) {
        hmeasured->Fill(fsignal->GetRandom(xmin, xmax) + gRandom->Gaus(0.0,sigmax));
    }
    hmeasured->Scale(1./hmeasured->GetEntries());
    hmeasured->SetLineColor(kRed);
    hmeasured->SetStats(0);
    hmeasured->SetBit(TH1::kNoTitle, false);
    hmeasured->Draw();

    // drawing kernel
    c1->cd(3);
    gPad->SetTopMargin(0.1);
    gr_kernel->SetTitle("kernel");
    gr_kernel->Draw("apl");

    // calculation of convolution
    TBenchmark benchmark;
    for(size_t i_mode=0; i_mode<m_modes.size(); i_mode++) {
        std::string sname = m_modes[i_mode].first;
        MathFunctions::Convolve::EConvolutionMode mode = m_modes[i_mode].second;

        // result
        TGraph *gr_result = new TGraph((int)npoints);
        benchmark.Start(sname.c_str());

        MathFunctions::Convolve cv;
        cv.setMode(mode);
        // running convolution several times to get statistics for benchmarking
        std::vector<double> result;
        for(int i=0; i<1000; i++) {
            cv.fftconvolve(signal, kernel, result);
        }
        benchmark.Stop(sname.c_str());
        //benchmark.Show(sname.c_str());
        for(size_t i=0; i<result.size(); i++) {
            double x = xmin + i*dx;
            gr_result->SetPoint((int)i,x,result[i]);
        }
        c1->cd(4+(int)i_mode);
        gPad->SetTopMargin(0.1);
        href->SetMaximum(20.0);
        href->SetTitle(sname.c_str());
        href->DrawCopy();
        gr_result->Draw("pl same");
    }
    Float_t rp, cp;
    std::cout << "--- TestConvolution::test_convolve_1d() -> Peformance." << std::endl;
    benchmark.Summary(rp, cp);
}

//! Test of convolution of two arrays in 2d.

void TestConvolution::test_convolve2d()
{
    double xmin(0.0), xmax(100.);
    size_t npx = 100;
    double dx = (xmax-xmin)/(npx);

    double ymin(0.0), ymax(40.);
    size_t npy = 40;
    double dy = (ymax-ymin)/(npy);

    double sigmax=(xmax-xmin)*0.01;
    double sigmay=(ymax-ymin)*0.01;

    // filling signal pattern - spikes on top of flat background
    std::vector<std::vector<double> > source;
    source.resize(npx);
    for(size_t ix=0; ix<npx; ix++) {
        source[ix].resize(npy, 1);
        for(size_t iy=0; iy<npy; iy++){
            // background
            source[ix][iy] = 0.5*double(ix)/double(npx) + 0.5*double(iy)/double(npy);
            // spikes
            if(ix>1 && iy!=0) {
                if( (ix%20==0 || (ix-1)%20==0) && iy%8==0) {
                    source[ix][iy]+=5;
                }
            }
        } // iy
    } // ix
    // filling signal histogram with values from signal array
    TH2F *h2_signal = new TH2F("h2_signal","h2_signal", (int)npx, xmin, xmax, (int)npy, ymin, ymax);
    h2_signal->SetStats(0);
    h2_signal->SetMinimum(0);
    h2_signal->SetMaximum(3.0);
    for(size_t ix=0; ix<npx; ix++){
        double x = xmin +  dx*ix;
        for(size_t iy=0; iy<npy; iy++){
            double y = ymin + dy*iy;
            h2_signal->Fill(x,y,source[ix][iy]);
        }
    }

    // resolution function (two dimensional gaus)
    TF2 *fres = new TF2("fres","[0]*TMath::Gaus(x,[1],[2])*TMath::Gaus(y,[3],[4])", xmin, xmax, ymin, ymax);
    fres->SetParameters(1,xmin+(xmax-xmin)/2.,sigmax, ymin + (ymax-ymin)/2., sigmay);
    // preparing resolution kernel and histogram
    std::vector<std::vector<double> > kernel;
    TH2F *h2_kernel = new TH2F("h2_kernel","h2_kernel", (int)npx, xmin, xmax, (int)npy, ymin, ymax);
    h2_kernel->SetStats(0);
    kernel.resize(npx);
    for(size_t ix=0; ix<npx; ix++) {
        kernel[ix].resize(npy);
        double x = xmin +  dx*ix;
        for(size_t iy=0; iy<npy; iy++){
            double y = ymin + dy*iy;
            kernel[ix][iy] = fres->Eval(x,y);
            h2_kernel->Fill(x,y, kernel[ix][iy]);
        }
    }

    // simulation of measurements with smearing measurement with resolution function
    TH2F *h2_measured = new TH2F("h2_measured","h2_measured", (int)npx, xmin, xmax, (int)npy, ymin, ymax);
    h2_measured->SetStats(0);
    TRandom mr;
    for(int i_meas=0; i_meas<1000000; i_meas++) {
        // generating distribution according to our signal
        double x,y;
        h2_signal->GetRandom2(x,y);
        // smearing signal to get "measured" signal
        h2_measured->Fill(x + mr.Gaus(0,sigmax), y + mr.Gaus(0,sigmay));
    }

    // drawing
    TCanvas *c1 = new TCanvas("c1_test_convolve2d","c1_test_convolve2d",1024, 768);
    DrawHelper::SetMagnifier(c1);
    gStyle->SetPalette(1);

    c1->Divide(3,3);
    c1->cd(1);
    gPad->SetRightMargin(0.12);
    gPad->SetTopMargin(0.1);
    h2_signal->Draw("colz");

    c1->cd(2);
    gPad->SetRightMargin(0.12);
    gPad->SetTopMargin(0.1);
    h2_signal->Draw("lego");

    c1->cd(3);
    gPad->SetRightMargin(0.12);
    gPad->SetTopMargin(0.1);
    h2_kernel->Draw("lego");

    c1->cd(4);
    gPad->SetRightMargin(0.12);
    gPad->SetTopMargin(0.1);
    h2_measured->Draw("colz");

    // calculation of convolution
    std::vector<std::vector<double> > result;
    TBenchmark benchmark;
    for(size_t i_mode=0; i_mode<m_modes.size(); i_mode++) {
        std::string sname = m_modes[i_mode].first;
        MathFunctions::Convolve::EConvolutionMode mode = m_modes[i_mode].second;

        // running convolution several times to get statistics for benchmarking
        benchmark.Start(sname.c_str());
        MathFunctions::Convolve cv;
        cv.setMode(mode);
        for(int i=0; i<1000; i++) {
            cv.fftconvolve(source, kernel, result);
        }
        benchmark.Stop(sname.c_str());

        // drawing results of last convolution
        c1->cd(5+(int)i_mode);
        gPad->SetRightMargin(0.12);
        gPad->SetTopMargin(0.1);
        TH2F h2_result("h2_result","h2_result", (int)npx, xmin, xmax, (int)npy, ymin, ymax);
        h2_result.SetStats(0);
        for(size_t ix=0; ix<npx; ix++) {
            double x = xmin +  dx*ix;
            for(size_t iy=0; iy<npy; iy++){
                double y = ymin + dy*iy;
                h2_result.Fill(x,y, result[ix][iy]);
            }
        }
        h2_result.SetTitle(sname.c_str());
        h2_result.SetBit(TH1::kNoTitle, false);
        h2_result.DrawCopy("colz");
    }

    // benchmark summary
    Float_t rp, cp;
    std::cout << "--- TestConvolution::test_convolve_2d() -> Peformance." << std::endl;
    benchmark.Summary(rp, cp);

}

//! Test function for convolution.

double TestConvolution::fpeaks(double *x, double *par)
{
    Double_t result = par[0] + par[1]*x[0];
    for (Int_t p=0;p<m_npeaks;p++) {
       Double_t norm  = par[3*p+2];
       Double_t mean  = par[3*p+3];
       Double_t sigma = par[3*p+4];
       result += norm*TMath::Gaus(x[0],mean,sigma);
    }
    return result;
}


