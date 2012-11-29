// Drawing of fit data stored in the FitSuiteTree (using FitData class)
// (data produced by FitSuiteObserverWriteTree un TestFittingModule)
// Usage:
//
// Way #1 (script mode)
// > root -l analyse_fitdata2.C
//
// Way #2 (precompiled mode)
// > root -l
// > .L analyse_fitdata2.C++
// analyse_fitdata2("../fitsuit.root")

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#include "TObject.h"
#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TSystem.h"
#include "TPaveText.h"
#include "TProfile2D.h"


using namespace std;
#include "FitData.C"

typedef std::vector<std::vector<double > > vdouble2d_t;

TH2D *create_histogram(const char *name, const char *title, FitData *event);
void getRelativeDifference(const vdouble2d_t &fit_data, const vdouble2d_t &real_data, vdouble2d_t &difference);
void getChi2Difference(const vdouble2d_t &fit_data, const vdouble2d_t &real_data, vdouble2d_t &difference);
void drawParametersInfo(TPaveText &pt, FitData *event);


/* ************************************************************************* */
// main analysis: read all fit iterations and nicely draw real/fit data
/* ************************************************************************* */
void analyse_fitdata2(const char *file_name = "../../../../fitsuite.root")
{
    const char *tree_name = "FitSuiteTree";
    TChain *chain = new TChain(tree_name);
    chain->Add(file_name);

    FitData *event = new FitData(chain);
    // reading first event to load event with the content of first iteration
    chain->GetEntry(0);
    //chain->Print();

    // create histogram to represent output data class content
    TH2D *histReal = create_histogram("histReal", "real data", event);
    TH2D *histFit = create_histogram("histFit", "simulated data", event);
    TH2D *histRelativeDiff = create_histogram("histRelativeDiff", "relative diff", event);
    TH2D *histChi2Diff = create_histogram("histChi2Diff", "chi2 diff", event);

    TCanvas *c1 = new TCanvas("c1","c1", 768, 1024);
    c1->Divide(2,3);
    // loop over entries
    std::cout << "Number of entries: " << chain->GetEntries() << std::endl;
    int i_entry(0);
    while(chain->GetEntry(i_entry++)){
        histReal->Reset();
        histFit->Reset();
        histRelativeDiff->Reset();
        histChi2Diff->Reset();

        vdouble2d_t relative_diff;
        getRelativeDifference(event->fit_data, event->real_data, relative_diff);
        vdouble2d_t chi2_diff;
        getChi2Difference(event->fit_data, event->real_data, chi2_diff);

        for(size_t i=0; i<event->real_data.size(); i++){
            for(size_t j=0; j<event->real_data[i].size(); j++) {
                histReal->Fill(event->axis0[i][j], event->axis1[i][j], event->real_data[i][j]);
                histFit->Fill(event->axis0[i][j], event->axis1[i][j], event->fit_data[i][j]);
                histRelativeDiff->Fill(event->axis0[i][j], event->axis1[i][j], relative_diff[i][j]);
                histChi2Diff->Fill(event->axis0[i][j], event->axis1[i][j], chi2_diff[i][j]);
             }
        }
//         histProf->Fill(event->parvalues[0], event->parvalues[1],event->chi2);

        c1->cd(1); gPad->SetLogz();
        histReal->SetMinimum(100);
        histReal->DrawCopy("colz");

        c1->cd(2); gPad->SetLogz();
        histFit->SetMinimum(100);
        histFit->SetMaximum(histReal->GetMaximum());
        histFit->DrawCopy("colz");

        c1->cd(3); gPad->SetLogz();
        histRelativeDiff->SetMinimum(0.01);
        histRelativeDiff->DrawCopy("colz");

        c1->cd(4); gPad->SetLogz();
        histChi2Diff->SetMinimum(0.01);
        histChi2Diff->DrawCopy("colz");

        // printing parameters
        c1->cd(5);
        TPaveText pt(.05,.1,.95,.8);
        drawParametersInfo(pt, event);

        if((i_entry-1)%10==0) c1->Update();

        if( gSystem->ProcessEvents() ) {
            std::cout << "Ctrl-c inside TCanvas has been detected" << std::endl;
            break; // ctr-c inside canvas will terminate the loop
        }

    } // loop over recorder events


    // initial parameters
    c1->cd(5);
    TPaveText *pt_initial = new TPaveText(.05,.1,.95,.8);
    chain->GetEntry(0);
    drawParametersInfo(*pt_initial, event);
    // final parameters
    c1->cd(6);
    TPaveText *pt_final = new TPaveText(.05,.1,.95,.8);
    chain->GetEntry(chain->GetEntries()-1);
    drawParametersInfo(*pt_final, event);

//     TCanvas *c2 = new TCanvas("c2","c2",800,600);
//     c2->cd();
//     histProf->Draw("colz");
} // analyse_fitdata2()


/* ************************************************************************* */
// create histogram to represent OutputData class content
// histogram limits will be taken from the current tree entry
/* ************************************************************************* */
TH2D *create_histogram(const char *name, const char *title, FitData *event)
{
    // finding histogram limits
    std::vector<double> axis0;
    for(size_t i=0; i<event->axis0.size(); ++i) axis0.push_back(event->axis0[i][0]);
    std::vector<double> axis1 = event->axis1[0];
    double dphi = (axis0.back()-axis0.front())/double(axis0.size()-1);
    double phi1 = axis0.front() - dphi/2.;
    double phi2 = axis0.back() + dphi/2.;
    double dalpha = (axis1.back()-axis1.front())/double(axis1.size()-1);
    double alpha1 = axis1.front() - dalpha/2.;
    double alpha2 = axis1.back() + dalpha/2.;
    //std::cout << "dphi: " << dphi << " phi1:" << phi1 << " phi2:" << phi2 << std::endl;
    //std::cout << "dalpha: " << dalpha << " alpha1:" << alpha1 << " alpha2:" << alpha2 << std::endl;

    TH2D *myHisto = new TH2D(name, title, axis0.size(), phi1, phi2, axis1.size(), alpha1, alpha2);
    myHisto->SetContour(50);
    myHisto->SetTitle("");
    myHisto->SetMinimum(1);
    myHisto->SetStats(0);

    return myHisto;
}


/* ************************************************************************* */
// calculate relative difference between data and fit
/* ************************************************************************* */
void getRelativeDifference(const vdouble2d_t &fit_data, const vdouble2d_t &real_data, vdouble2d_t &difference)
{
  difference.clear();
  if(real_data.size() != fit_data.size() ) {
      std::cout << "getRelativeDifference() -> Unconsistent size of real and simulated data." << std::endl;
      return;
  }
  difference.resize(real_data.size());
  for(size_t i=0; i<real_data.size(); ++i) {
      if(real_data[i].size() != fit_data[i].size() ) {
          std::cout << "getRelativeDifference() -> Unconsistent size of real and simulated data." << std::endl;
          return;
      }
      difference[i].resize(real_data[i].size(), 0.0);
      for(size_t j = 0; j<real_data[i].size(); ++j) {
          if(real_data[i][j] > 0) {
            difference[i][j] = std::fabs((fit_data[i][j] - real_data[i][j]))/real_data[i][j];
          } else {
            std::cout << "???" << std::endl;
          }
      }
  }


}


/* ************************************************************************* */
// calculate chi2 difference between data and fit
/* ************************************************************************* */
void getChi2Difference(const vdouble2d_t &fit_data, const vdouble2d_t &real_data, vdouble2d_t &difference)
{
  difference.clear();
  if(real_data.size() != fit_data.size() ) {
      std::cout << "getRelativeDifference() -> Unconsistent size of real and simulated data." << std::endl;
      return;
  }
  difference.resize(real_data.size());
  for(size_t i=0; i<real_data.size(); ++i) {
      if(real_data[i].size() != fit_data[i].size() ) {
          std::cout << "getRelativeDifference() -> Unconsistent size of real and simulated data." << std::endl;
          return;
      }
      difference[i].resize(real_data[i].size(), 0.0);
      for(size_t j = 0; j<real_data[i].size(); ++j) {
          //double normalization = std::max(std::abs(real_data[i][j]), 1.0);
          double normalization = 1;
          difference[i][j] = (fit_data[i][j] - real_data[i][j])*(fit_data[i][j] - real_data[i][j])/normalization;
      }
  }
}


/* ************************************************************************* */
// draw parameters info
/* ************************************************************************* */
void drawParametersInfo(TPaveText &pt, FitData *event)
{
    pt.SetTextAlign(11);
    std::ostringstream ostr;
    ostr << "Iter " << event->niter << " Strat " << event->nstrategy << " chi2:" << event->chi2 << std::endl;
    pt.AddText(ostr.str().c_str());

    for(size_t i =0; i<event->parvalues.size(); ++i) {
        ostr.str(""); ostr.clear();
        ostr << event->parnames[i].c_str() << " " << event->parvalues[i];
        if(event->parfixed[i]) ostr << "(F)";
        pt.AddText(ostr.str().c_str());
    }
    pt.Draw();

}

