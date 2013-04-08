// analysis of meso data stored in the form of TTree
// see also analysis1.C
//
// Usage:
// First produce root tree using : ../../../App/App roottree
//
// root -l
// .L MesoData.C++
// .L analysis2.C++
// analysis2()
//
#include <iostream>
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TProfile2D.h"
#include "TLatex.h"
#include "TSystem.h"

#include "MesoData.h"


void analysis2()
{

    TChain *chain = new TChain("testmeso");
    chain->Add("./testmeso.root");

    MesoData *event = new MesoData(chain);
    chain->GetEntry(0);

    double dphi = (event->phi_f_max-event->phi_f_min)/double(event->nphi_f-1);
    double phi1 = event->phi_f_min - dphi/2.;
    double phi2 = event->phi_f_max + dphi/2.;
    double dalpha = (event->alpha_f_max-event->alpha_f_min)/double(event->nalpha_f-1);
    double alpha1 = event->alpha_f_min - dalpha/2;
    double alpha2 = event->alpha_f_max + dalpha/2.;
    TH2D *myHisto = new TH2D("myHisto","myHisto", event->nphi_f, phi1, phi2, event->nalpha_f, alpha1, alpha2);
    myHisto->SetContour(50);
    myHisto->SetTitle("");
    myHisto->SetMinimum(1.0);
    myHisto->SetMaximum(1e+07);
    myHisto->SetStats(0);

    // preparing animated gif
    gSystem->Unlink("testmeso.gif");
    
    
    
    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->cd();
    gPad->SetLogz();
    
    TLatex tex;
    tex.SetNDC(1);
    char str[256];

    // first run drawing frame by frame, second run - accumulating
    for(int i_run=0; i_run<2; i_run++){
        int i_entry=0;
        while(chain->GetEntry(i_entry++)){
            if(i_run==0) myHisto->Reset();
            for(int i=0; i<event->nphi_f; i++){
                for(int j=0; j<event->nalpha_f; j++) {
                    myHisto->Fill(event->vphi_f[i][j], event->valpha_f[i][j], event->vi[i][j]);
                }
            }
            myHisto->Draw("CONT4 Z");

            if(i_run==0){
                sprintf(str,"R:%6.3f  phi:%6.3f alpha:%6.3f",event->npR, event->mphi, event->malpha);
            } else {
                sprintf(str,"acc -> R:%6.3f  phi:%6.3f alpha:%6.3f ",event->npR, event->mphi, event->malpha);
            }
            tex.DrawLatex(0.2, 0.92, str);
            c1->Modified();
            c1->Update();
            c1->Print("testmeso.gif+20");
            //gSystem->Sleep(200);
        }
        break;
    }

    c1->Print("testmeso.gif++");

    // now accumulating


    
}
