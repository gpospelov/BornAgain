#include "TestInstrument.h"
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

std::vector<double > Convolve_MyFFT1D_B(int mode, const std::vector<double> &data1, const std::vector<double> &data2);


int npeaks(30);

Double_t fpeaks(Double_t *x, Double_t *par) {
   Double_t result = par[0] + par[1]*x[0];
   for (Int_t p=0;p<npeaks;p++) {
      Double_t norm  = par[3*p+2];
      Double_t mean  = par[3*p+3];
      Double_t sigma = par[3*p+4];
      result += norm*TMath::Gaus(x[0],mean,sigma);
   }
   return result;
}




TestInstrument::TestInstrument()
{
    std::cout << "TestInstrument::TestInstrument() -> Info." << std::endl;

    m_modes.push_back( mode_pair_t("LINEAR_FULL", MathFunctions::Convolve::FFTW_LINEAR_FULL));
    m_modes.push_back( mode_pair_t("LINEAR_SAME_UNPADDED", MathFunctions::Convolve::FFTW_LINEAR_SAME_UNPADDED));
    m_modes.push_back( mode_pair_t("LINEAR_SAME", MathFunctions::Convolve::FFTW_LINEAR_SAME));
    m_modes.push_back( mode_pair_t("CIRCULAR_SAME", MathFunctions::Convolve::FFTW_CIRCULAR_SAME));
    m_modes.push_back( mode_pair_t("CIRCULAR_SAME_SHIFTED", MathFunctions::Convolve::FFTW_CIRCULAR_SAME_SHIFTED));
}


void TestInstrument::execute()
{

    test_convolve1d();
    // results are about
    // LINEAR_FULL: Real Time =   0.37 seconds Cpu Time =   0.36 seconds
    // LINEAR_SAME_UNPADDED: Real Time =   1.03 seconds Cpu Time =   1.03 seconds
    // LINEAR_SAME: Real Time =   0.23 seconds Cpu Time =   0.23 seconds
    // CIRCULAR_SAME: Real Time =   0.50 seconds Cpu Time =   0.50 seconds
    // CIRCULAR_SAME_SHIFTED: Real Time =   0.51 seconds Cpu Time =   0.51 seconds

    //test_convolve2d();
    // LINEAR_FULL: Real Time =   1.19 seconds Cpu Time =   1.18 seconds
    // LINEAR_SAME_UNPADDED: Real Time =   0.72 seconds Cpu Time =   0.72 seconds
    // LINEAR_SAME: Real Time =   0.72 seconds Cpu Time =   0.73 seconds
    // CIRCULAR_SAME: Real Time =   0.53 seconds Cpu Time =   0.54 seconds
    // CIRCULAR_SAME_SHIFTED: Real Time =   0.61 seconds Cpu Time =   0.61 seconds

}



void TestInstrument::test_convolve1d()
{
    npeaks = TMath::Abs(10);
    double xmin(0.0);
    double xmax(1000.);
    size_t npoints = 501;
    double dx = (xmax-xmin)/(npoints-1);

    double sigma0=(xmax-xmin)*0.001;

    TH1F *href = new TH1F("h","test", npoints-1, xmin, xmax);
    href->SetMinimum(0.0);
    href->SetMaximum(2.0);

    //generate n peaks at random
    Double_t par[3000];
    par[0] = 1.0;
    par[1] = -0.6/(xmax-xmin);
    Int_t p;
    for (p=0;p<npeaks;p++) {
       par[3*p+2] = 1;
       par[3*p+3] = (xmax-xmin)*0.01+gRandom->Rndm()*(xmax-xmin);
       par[3*p+4] = sigma0+sigma0*5*gRandom->Rndm();
    }
    TF1 *fspect = new TF1("f",fpeaks,0,1000,2+3*npeaks);
    fspect->SetNpx(10000);
    fspect->SetParameters(par);
    TCanvas *c1 = new TCanvas("c1_test_convolve1d","c1_test_convolve1d",1024, 768);
    c1->Divide(3,3);
    c1->cd(1);
    //href->FillRandom("f",20000);
    href->DrawCopy();
    fspect->Draw("pl same");

    c1->cd(2);
    double sigma_measure = sigma0*5;
    TH1F *hmeasured = new TH1F("hp","hp",500, xmin, xmax);
//    double sigma_measure=sigma0*3;
    for(int i=0; i<1000000; i++) {
        hmeasured->Fill(fspect->GetRandom(xmin, xmax) + gRandom->Gaus(0.0,sigma_measure));
    }
    hmeasured->Scale(1./hmeasured->GetEntries());
    hmeasured->SetLineColor(kRed);
    hmeasured->Draw();

    std::vector<double> xspect;
    xspect.resize(npoints);
    for(size_t i=0; i<npoints; i++) {
        double x = xmin + i*dx;
        xspect[i] = fspect->Eval(x);
        std::cout << i << " " << x << " " << xspect[i] << std::endl;
    }

    // building responce function
    std::vector<double> xresp;
    xresp.resize(npoints);
//    for(size_t i=0; i<npoints/2; i++) {
//        double x = i*dx;
//        double y = std::exp(-x*x/sigma_measure/sigma_measure);
//        xresp[i] = y;
//        xresp[npoints-1-i] = xresp[i];
//    }

    for(size_t i=0; i<npoints; i++) {
        double x = -(xmax-xmin)/2.+i*dx;
        double y = std::exp(-x*x/sigma_measure/sigma_measure);
        xresp[i] = y;
    }

    TGraph *gr_resp = new TGraph(npoints);
    for(size_t i=0; i<xresp.size(); i++){
        double x = xmin + i*dx;
        gr_resp->SetPoint(i,x,xresp[i]);
    }
    c1->cd(3);
    href->DrawCopy();
    gr_resp->Draw("pl same");


    TBenchmark benchmark;
    for(size_t i_mode=0; i_mode<m_modes.size(); i_mode++) {
        std::string sname = m_modes[i_mode].first;
        MathFunctions::Convolve::Mode mode = m_modes[i_mode].second;

        // result
        TGraph *gr_result = new TGraph(npoints);
        benchmark.Start(sname.c_str());

        MathFunctions::Convolve cv;
        cv.setMode(mode);
        std::vector<double> xresult;
        for(int i=0; i<1000; i++) {
            //int mm = (int)modes[i_mode];
     //       xresult = Convolve_MyFFT1D_B(mm, xspect, xresp);
            cv.fftconvolve(xspect, xresp, xresult);
        }
        benchmark.Stop(sname.c_str());
        benchmark.Show(sname.c_str());
        for(size_t i=0; i<xresult.size(); i++) {
            double x = xmin + i*dx;
            gr_result->SetPoint(i,x,xresult[i]);
        }
        c1->cd(4+i_mode);
        href->SetMaximum(20.0);
        href->DrawCopy();
        gr_result->Draw("pl same");
    }
    float_t rp, cp;
    std::cout << "--------------" << std::endl;
    benchmark.Summary(rp, cp);

}


/* ************************************************************************* */
//
/* ************************************************************************* */
void TestInstrument::test_convolve2d()
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
                    std::cout << ix << " " << iy << std::endl;
                    source[ix][iy]+=5;
                }
            }
        } // iy
    } // ix
    // signal histogram
    TH2F *h2_signal = new TH2F("h2_signal","h2_signal", npx, xmin, xmax, npy, ymin, ymax);
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
    TH2F *h2_kernel = new TH2F("h2_kernel","h2_kernel", npx, xmin, xmax, npy, ymin, ymax);
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
    TH2F *h2_measured = new TH2F("h2_measured","h2_measured", npx, xmin, xmax, npy, ymin, ymax);
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
    DrawHelper::instance().SetMagnifier(c1);
    gStyle->SetPalette(1);

    c1->Divide(3,3);
    c1->cd(1); gPad->SetRightMargin(0.15);
    h2_signal->Draw("colz");

    c1->cd(2); gPad->SetRightMargin(0.15);
    h2_signal->Draw("lego");

    c1->cd(3); gPad->SetRightMargin(0.15);
    h2_kernel->Draw("lego");

    c1->cd(4); gPad->SetRightMargin(0.15);
    h2_measured->Draw("colz");

    // calculation of convolution
    std::vector<std::vector<double> > result;
    TBenchmark benchmark;
    for(size_t i_mode=0; i_mode<m_modes.size(); i_mode++) {
        std::string sname = m_modes[i_mode].first;
        MathFunctions::Convolve::Mode mode = m_modes[i_mode].second;

        // running convolution several times to get statistics for benchmarking
        benchmark.Start(sname.c_str());
        MathFunctions::Convolve cv;
        cv.setMode(mode);
        for(int i=0; i<1000; i++) {
            cv.fftconvolve(source, kernel, result);
        }
        benchmark.Stop(sname.c_str());

        // drawing results of last convolution
        c1->cd(5+i_mode);
        TH2F h2_result("h2_result","h2_result", npx, xmin, xmax, npy, ymin, ymax);
        h2_result.SetStats(0);
        for(size_t ix=0; ix<npx; ix++) {
            double x = xmin +  dx*ix;
            for(size_t iy=0; iy<npy; iy++){
                double y = ymin + dy*iy;
                h2_result.Fill(x,y, result[ix][iy]);
            }
        }
        h2_result.SetTitle(sname.c_str());
        h2_result.DrawCopy("colz");
    }

    // benchmark summary
    float_t rp, cp;
    std::cout << "--------------" << std::endl;
    benchmark.Summary(rp, cp);

}




std::vector<double> Convolve_MyFFT1D_B(int mode, const std::vector<double> &data1, const std::vector<double> &data2)
{
    size_t Ns = data1.size();
    double * src = new double[Ns];
    for(size_t i=0; i<Ns; i++) {
        src[i] = data1[i];
    }

    size_t Nk = data2.size();
    double * kernel = new double[Nk];
    for(size_t i=0; i<Nk; i++) {
        kernel[i] = data2[i];
    }

    FFTW_Workspace ws;
//    init_workspace_fftw(ws, FFTW_LINEAR_FULL, 1,Ns,1,Nk);
//    init_workspace_fftw(ws, FFTW_LINEAR_SAME_UNPADDED, 1,Ns,1,Nk);
//    init_workspace_fftw(ws, FFTW_LINEAR_SAME, 1,Ns,1,Nk);
//    init_workspace_fftw(ws, FFTW_LINEAR_VALID, 1,Ns,1,Nk);
//    init_workspace_fftw(ws, FFTW_CIRCULAR_SAME, 1,Ns,1,Nk);
//    init_workspace_fftw(ws, FFTW_CIRCULAR_SAME_SHIFTED, 1,Ns,1,Nk);

    FFTW_Convolution_Mode xm = (FFTW_Convolution_Mode)mode;
    init_workspace_fftw(ws, xm, 1,Ns,1,Nk);


    fftw_convolve(ws, src, kernel);

//    std::cout << "!!! " << ws.w_dst << std::endl;
//    for(int j = 0 ; j < ws.w_dst ; ++j) std::cout << ws.dst[j] << " ";

    std::vector<double > fft_result;
    fft_result.resize(ws.w_dst);
    for(size_t i=0; i<data1.size(); i++){
        fft_result[i] = ws.dst[i];
    }

    clear_workspace_fftw(ws);
    return fft_result;
}





