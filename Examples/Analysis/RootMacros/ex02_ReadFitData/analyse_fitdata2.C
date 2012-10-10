// Simple drawing of fit data stored in the FitSuiteTree (using FitData class)
// (data produced by FitSuiteObserverWriteTree un TestFittingModule)
// Usage:
//
// Way #1 (script mode)
// > root -l analyse_fitdata1.C
//
// Way #2 (precompiled mode)
// > root -l
// > .L analyse_fitdata1.C++
// analyse_fitdata1()

#include <iostream>
#include <string>
#include <vector>
#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TSystem.h"
#include "TPaveText.h"

using namespace std;
#include "FitData.C"


void analyse_fitdata2()
{
    const char *file_name ="../../../../fitsuite.root";
    const char *tree_name = "FitSuiteTree";

    TChain *chain = new TChain(tree_name);
    chain->Add(file_name);

    FitData *event = new FitData(chain);

    // reading first event
    chain->GetEntry(0);

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
    std::cout << "dphi: " << dphi << " phi1:" << phi1 << " phi2:" << phi2 << std::endl;
    std::cout << "dalpha: " << dalpha << " alpha1:" << alpha1 << " alpha2:" << alpha2 << std::endl;

    TH2D *myHisto = new TH2D("myHisto","myHisto", axis0.size(), phi1, phi2, axis0.size(), alpha1, alpha2);
    myHisto->SetContour(50);
    myHisto->SetTitle("");
    myHisto->SetMinimum(1);
    myHisto->SetStats(0);

    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->Divide(2,2);
    // loop over entries
    int i_entry(0);
    while(chain->GetEntry(i_entry++)){
        for(size_t i=0; i<axis0.size(); i++){
            for(size_t j=0; j<axis1.size(); j++) {
                myHisto->Fill(event->axis0[i][j], event->axis1[i][j], event->real_data[i][j]);
             }
        }
        c1->cd(1); gPad->SetLogz();
        myHisto->DrawCopy("colz");
        myHisto->Reset();
        for(size_t i=0; i<axis0.size(); i++){
            for(size_t j=0; j<axis1.size(); j++) {
                myHisto->Fill(event->axis0[i][j], event->axis1[i][j], event->fit_data[i][j]);
             }
        }
        c1->cd(2); gPad->SetLogz();
        myHisto->DrawCopy("colz");
        myHisto->Reset();

        // printing parameters
        c1->cd(3);
        TPaveText *pt = new TPaveText(.05,.1,.95,.8);
        char str[256];
        sprintf(str,"Iteration %d",event->niter);
        pt->AddText(str);
        sprintf(str,"chi2 %e",event->chi2);
        pt->AddText(str);
        for(size_t i =0; i<event->params.size(); ++i) {
            sprintf(str,"%s %f", event->parnames[i].c_str(),  event->params[i]);
            pt->AddText(str);
        }
        pt->Draw();

        c1->Update();
        gSystem->Sleep(5); // wait a bit for smooth animation
    } // loop over recorder events



}

    
