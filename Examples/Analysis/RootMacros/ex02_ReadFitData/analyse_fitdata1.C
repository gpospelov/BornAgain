// Simple drawing of fit data stored in the FitSuiteTree using TTree::Draw() method
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
#include "TTree.h"
#include "TCanvas.h"

#include "FitData.h"


void analyse_fitdata1()
{
    const char *file_name ="../../../../fitsuite.root";
    const char *tree_name = "FitSuiteTree";

    // opening root file
    TFile *top = new TFile(file_name,"READ");
    if( !top->IsOpen() ) {
        std::cout << "Can't open file '" << file_name << "'" << std::endl;
        return;
    }

    // access tree stored in the file
    TTree *tree = (TTree *) top->Get(tree_name);
    if( !tree ) {
        std::cout << "Can't get tree '" << tree_name << "'" << std::endl;
        return;
    }

    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->Divide(2,2);

    // loop over tree entries and drawing
    for(int i=0; i<tree->GetEntries(); i++){
        // defining criteria for Draw method -> it will draw only data corresponding to the event with given number
        char criteria[128];
        sprintf(criteria,"Entry$==%d",i);        
        c1->cd(1); gPad->SetLogz();
        tree->Draw("real_data:axis1:axis0",criteria,"prof COLZ");
        c1->cd(2); gPad->SetLogz();
        tree->Draw("fit_data:axis1:axis0",criteria,"prof COLZ");
        c1->Update();
    }



}

    
