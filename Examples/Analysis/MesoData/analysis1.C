// simple drawing of meso data stored in the form of TTree
// Usage:
// First produce root tree using : ../../../App/App roottree
//
// Way #1 (script mode)
// root -l analysis1.C                                # start root and execute script
//
// Way #2 (precompiled mode)
// root -l                                            # start root session
// .L analysis1.C++                                   # compile script (to have it fast)
// analysis1()                                        # execute function defined in the script
//
// Way #3 (without this script at all)
// root -l testmeso.root                               # start root and open given file
// TTree *tree = (TTree *)_file0->Get("testmeso");     # read from the file tree object with given name
// tree->Draw("vi:valpha_f:vphi_f","","prof CONT4 Z"); # draw intensity as a function of phi and alpha
//
// tree->Print(); tree->Draw(); TBrowser b;...         # many other commands are usefull for interactove analysis

#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TProfile2D.h"

#include <string>


void analysis1()
{
    // open root file
    std::string filename("./testmeso.root");
    TFile *top = new TFile(filename.c_str(),"READ");
    if( !top->IsOpen() ) {
        std::cout << "Can't open file '" << filename << "'" << std::endl;
        return;
    }

    // access tree stored in the file
    std::string treename("testmeso");
    TTree *tree = (TTree *) top->Get(treename.c_str());
    if( !tree ) {
        std::cout << "Can't get tree '" << treename << "'" << std::endl;
        return;
    }

    // predefine histogram
//      int np(100);
// //     double alphaMin(-0.00698132), alphaMax(0.066), phiMin(0.00523599), phiMax(0.073);
//     double alphaMin(-0.4), alphaMax(3.78152), phiMin(0.3), phiMax(4.18259);
//     double dalpha = (alphaMax - alphaMin) / (np-1);
//     double dphi = (phiMax - phiMin) / (np-1);
//     TProfile2D *myHisto = new TProfile2D("myHisto","myHisto", np, phiMin-dphi/2., phiMax+dphi/2., np, alphaMin-dalpha/2., alphaMax+dalpha/2.);
//     myHisto->SetContour(50);

    // drawing sum of all intensities
    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->cd();
    gPad->SetLogz();

//     tree->Draw("vi:valpha_f:vphi_f>>myHisto","","prof CONT4 Z");
//     TH1 *myHisto = (TH1 *)gDirectory->Get("myHisto");
//     myHisto->SetContour(50);
//     myHisto->SetMinimum(1.0);
//     myHisto->SetStats(0);
//     c1->Update();

    // summming intensity frame by frame
    TCanvas *c2 = new TCanvas("c2","c2",1024, 768);
    c2->cd();
    gPad->SetLogz();
    for(int i=0; i<tree->GetEntries(); i++){
        char criteria[128];
        sprintf(criteria,"Entry$==%d",i);
        tree->Draw("vi:valpha_f:vphi_f>>myHisto2",criteria,"prof CONT4 Z");
        TH1 *myHisto2 = (TH1 *)gDirectory->Get("myHisto2");
        myHisto2->SetContour(50);
        myHisto2->SetMinimum(1.0);
        myHisto2->SetStats(0);
        c2->Update();
    }

    
    //h2->Draw();
}

