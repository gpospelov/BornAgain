#include "FitSuite.h"
#include "FitSuiteHelper.h"
#include "TreeEventStructure.h"
#include "IsGISAXSTools.h"

#include "TCanvas.h"
#include "TPaveText.h"
#include "ChiSquaredModule.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"


/* ************************************************************************* */
// draw results of fit iteration in ROOT's canvas
/* ************************************************************************* */
void FitSuiteObserverDraw::update(IObservable *subject)
{
    FitSuite *fitSuite = dynamic_cast<FitSuite *>(subject);
    if( !fitSuite ) throw NullPointerException("FitSuiteObserverDraw::update() -> Error! Can't cast FitSuite");

    std::cout << "FitObserver: " << " ncall" << m_ncall << " chi2:" << fitSuite->getChiSquaredModule()->getValue();
    // printing parameter values
    for(FitSuite::fitparameters_t::iterator it = fitSuite->fitparams_begin(); it!=fitSuite->fitparams_end(); ++it) {
        std::cout << " " << (*it)->getName() << " " << (*it)->getValue();
        //            std::cout << *(*it);
    }
    std::cout << std::endl;

    TCanvas *c1 = dynamic_cast<TCanvas *>( gROOT->FindObject(m_canvas_name.c_str()) );
    if(!c1) throw NullPointerException("FitSuiteObserverDraw::update() -> No access to canvas");
    c1->cd(3);
    gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*fitSuite->getChiSquaredModule()->getSimulationData(), "CONT4 Z", "current simulated data");
    c1->cd(4);
    IsGISAXSTools::drawOutputDataDifference2D(*fitSuite->getChiSquaredModule()->getSimulationData(), *fitSuite->getChiSquaredModule()->getRealData(), "CONT4 Z", "difference");
    c1->cd(5);

    TPaveText *pt = new TPaveText(.05,.1,.95,.8);
    char str[256];
    sprintf(str,"Iteration %d",m_ncall);
    pt->AddText(str);
    sprintf(str,"chi2 %e",fitSuite->getChiSquaredModule()->getValue());
    pt->AddText(str);
    //pt->AddLine(.0,.5,1.,.5);
    for(FitSuite::fitparameters_t::iterator it = fitSuite->fitparams_begin(); it!=fitSuite->fitparams_end(); ++it) {
        sprintf(str,"%s %f", (*it)->getName().c_str(),  (*it)->getValue());
        pt->AddText(str);
    }
    pt->Draw();

    m_ncall++;
}


/* ************************************************************************* */
// Save results of each fit iteration to the disk in the form of ROOT tree
/* ************************************************************************* */
void FitSuiteObserverWriteTree::update(IObservable *subject)
{
    std::string tree_name("FitSuiteTree");

    FitSuite *fitSuite = dynamic_cast<FitSuite *>(subject);
    if( !fitSuite ) throw NullPointerException("FitSuiteObserverWriteTree::update() -> Error! Can't cast FitSuite");

    std::cout << "FitObserver: " << " ncall" << m_ncall << " chi2:" << fitSuite->getChiSquaredModule()->getValue();
    // printing parameter values
    for(FitSuite::fitparameters_t::iterator it = fitSuite->fitparams_begin(); it!=fitSuite->fitparams_end(); ++it) {
        std::cout << " " << (*it)->getName() << " " << (*it)->getValue();
        //            std::cout << *(*it);
    }
    std::cout << std::endl;
    // preparing root file for writing
    // if it is first call the file will be opened in 'recreate' mode, otherwise in 'update' mode
    TFile *top(0);
    if(m_ncall == 0) {
        top = new TFile(m_file_name.c_str(),"RECREATE");
    } else {
        top = new TFile(m_file_name.c_str(),"UPDATE");
    }
    if( !top->IsOpen() ) {
        throw RuntimeErrorException("FitSuiteObserverWriteTree::update() -> Can't open file "+ m_file_name + " for writing");
    }


    // data object to write in the tree
    TreeEventFitData *event = new TreeEventFitData();

    // creating new tree
    TTree *tree = dynamic_cast<TTree *>(top->Get(tree_name.c_str()));
    if( tree == 0) {
        // tree doesn't exist due to new file, making new tree
        tree = new TTree(tree_name.c_str(),"Oh, my data");
        tree->Branch("Event",&event,16000,2);
    } else {
        // tree exists, pointing it to the new data
        tree->SetBranchAddress("Event", &event);
    }

    // filling data object with data from FitSuite
    const OutputData<double > *real_data = fitSuite->getChiSquaredModule()->getRealData();
    const OutputData<double > *simu_data = fitSuite->getChiSquaredModule()->getSimulationData();
    IsGISAXSTools::exportOutputDataInVectors2D(*real_data, event->real_data, event->axis0, event->axis1);
    IsGISAXSTools::exportOutputDataInVectors2D(*simu_data, event->fit_data, event->axis0, event->axis1);
    event->chi2 = fitSuite->getChiSquaredModule()->getValue();
    for(FitSuite::fitparameters_t::iterator it = fitSuite->fitparams_begin(); it!=fitSuite->fitparams_end(); ++it) {
        event->parvalues.push_back( (*it)->getValue() );
        event->parnames.push_back( (*it)->getName().c_str() );
    }
    event->niter = m_ncall;

    // appending data to the tree
    tree->Fill();
    tree->Write(tree_name.c_str(), TObject::kOverwrite);
    top->Close();
    delete top; // there is no need to delete tree since ROOT file takes care about all objects opened afterwards
    delete event;

    m_ncall++;
}

