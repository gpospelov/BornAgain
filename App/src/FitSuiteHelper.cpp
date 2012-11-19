#include "FitSuite.h"
#include "FitSuiteHelper.h"
#include "TreeEventStructure.h"
#include "IsGISAXSTools.h"
#include "ROOTMinimizer.h"
#include "FitSuiteParameters.h"

#include "TCanvas.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "Utils.h"
#include "TGraph.h"
#include "TPolyMarker.h"


#include <iomanip>
#include <sstream>


/* ************************************************************************* */
// print results of fit iteration
/* ************************************************************************* */
void FitSuiteObserverPrint::update(IObservable *subject)
{
    FitSuite *fitSuite = dynamic_cast<FitSuite *>(subject);
    if( !fitSuite ) throw NullPointerException("FitSuiteObserverPrint::update() -> Error! Can't cast FitSuite");

    // printing parameter values
    std::cout << "FitSuiteObserverPrint::update() -> Info."
              << " NumberOfVariables:" << fitSuite->getMinimizer()->getNumberOfVariables()
              << " NCall:" << fitSuite->getNCall()
              << " NStrategy:" << fitSuite->getNStrategy()
              << " Chi2:" << std::scientific << std::setprecision(8) << fitSuite->getSuiteKit()->getChiSquaredModule()->getValue() << std::endl;
    timeval call_time;
    gettimeofday(&call_time, 0);
    clock_t call_clock = clock();
    double timediff = (call_time.tv_sec - m_last_call_time.tv_sec) + double(call_time.tv_usec - m_last_call_time.tv_usec)/1e+06;
    std::cout << "Time spend since last call, cpu:" << std::fixed << std::setprecision(2) << double(call_clock-m_last_call_clock)/CLOCKS_PER_SEC << " " << "sec, wall time " << timediff << "sec" << std::endl;
    m_last_call_clock = call_clock;
    m_last_call_time = call_time;

    int npar(0);
    for(FitSuiteParameters::iterator it = fitSuite->getFitParameters()->begin(); it!=fitSuite->getFitParameters()->end(); ++it, ++npar) {
        std::cout << "   # "<< npar << " " << (*(*it)) << std::endl;
    }

    if(fitSuite->isLastIteration()) {
        std::cout << std::endl;
        std::cout << "FitSuiteObserverPrint::update() -> Info. Printing results" << std::endl;
        fitSuite->getMinimizer()->printResults();
    }
}


/* ************************************************************************* */
// draw results of fit iteration in ROOT's canvas
/* ************************************************************************* */
void FitSuiteObserverDraw::update(IObservable *subject)
{
    FitSuite *fitSuite = dynamic_cast<FitSuite *>(subject);
    if( !fitSuite ) throw NullPointerException("FitSuiteObserverDraw::update() -> Error! Can't cast FitSuite");

    if( !fitSuite->isLastIteration() && (fitSuite->getNCall() % m_draw_every_nth != 0) ) return;

    TCanvas *c1 = dynamic_cast<TCanvas *>( gROOT->FindObject(m_canvas_name.c_str()) );
    if(!c1) {
        std::cout << " FitSuiteObserverDraw::update() -> Info. No canvas with name '" << m_canvas_name << "', creating one" << std::endl;
        c1 = new TCanvas(m_canvas_name.c_str(), m_canvas_name.c_str(), 768, 1024);
        c1->Divide(2,3);
    }
    IsGISAXSTools::resetMinimumAndMaximum();
    // drawing real data
    c1->cd(1);
    gPad->SetLogz();
    gPad->SetLeftMargin(0.12);
    gPad->SetRightMargin(0.12);
    IsGISAXSTools::drawOutputDataInPad(*fitSuite->getSuiteKit()->getRealData(), "colz", "Real data");
    // drawing simulated data
    c1->cd(2);
    gPad->SetLogz();
    gPad->SetLeftMargin(0.12);
    gPad->SetRightMargin(0.12);
    IsGISAXSTools::drawOutputDataInPad(*fitSuite->getSuiteKit()->getSimulatedData(), "colz", "current simulated data");
    // simple difference
    c1->cd(3);
    gPad->SetLogz();
    gPad->SetLeftMargin(0.12);
    gPad->SetRightMargin(0.12);
    //IsGISAXSTools::drawOutputDataRelativeDifference2D(*fitSuite->getChiSquaredModule()->getSimulationData(), *fitSuite->getChiSquaredModule()->getRealData(), "COLZ", "relative difference");
    OutputData<double > *diff_map_relative = getRelativeDifferenceMap(fitSuite->getSuiteKit()->getSimulatedData(), fitSuite->getSuiteKit()->getRealData());
    gPad->SetRightMargin(0.12);
    IsGISAXSTools::drawOutputDataInPad(*diff_map_relative, "COLZ", "relative difference map");
    delete diff_map_relative;

    // chi2 difference
    c1->cd(4);
    gPad->SetLogz();
    gPad->SetLeftMargin(0.12);
    OutputData<double > *diff_map_chi2 = fitSuite->getSuiteKit()->getChiSquaredModule()->createChi2DifferenceMap();
    gPad->SetRightMargin(0.12);
    IsGISAXSTools::drawOutputDataInPad(*diff_map_chi2, "COLZ", "chi2 difference map");
    delete diff_map_chi2;

    c1->cd(5);
    delete m_ptext;
    m_ptext = new TPaveText(.05,.1,.95,.8);
    m_ptext->SetTextAlign(11);
    std::ostringstream ostr;
    ostr << "Iteration " << fitSuite->getNCall() << " strategy " << fitSuite->getNStrategy();
    m_ptext->AddText(ostr.str().c_str());
    ostr.str(""); ostr.clear();
    ostr << "chi2 " << fitSuite->getSuiteKit()->getChiSquaredModule()->getValue() << std::endl;
    m_ptext->AddText(ostr.str().c_str());

    for(FitSuiteParameters::iterator it = fitSuite->getFitParameters()->begin(); it!=fitSuite->getFitParameters()->end(); ++it) {
        ostr.str(""); ostr.clear();
        ostr << (*it)->getName() << " " << (*it)->getValue();
        if( (*it)->isFixed() ) ostr << " (F)";
        m_ptext->AddText(ostr.str().c_str());
    }
    m_ptext->Draw();

    if(fitSuite->isLastIteration()) {
//        TCanvas *c2 = new TCanvas("FitSuiteObserverDraw_c2", "FitSuiteObserverDraw_c2", 1024, 768);
//        c2->Divide(2,2);
//        ROOT::Math::Minimizer *minim = (dynamic_cast<ROOTMinimizer *>(fitSuite->getMinimizer()))->getROOTMinimizer();
//        if(!minim) {
//            throw NullPointerException("FitSuiteObserverDraw::update() -> Can't get right minimizer from FitSuite");
//        }
//        int npad=1;
//        for(unsigned int i=0; i<minim->NDim(); ++i) {
//            for(unsigned int j=0; j<i; ++j) {
//                if(i != j) {
//                    c2->cd(npad++);
//                    unsigned int np=50;
//                    std::vector<double> x;
//                    std::vector<double> y;
//                    x.resize(np, 0);
//                    y.resize(np, 0);
//                    minim->Contour(i,j, np,&x[0], &y[0]);
//                    x.push_back(x.front());
//                    y.push_back(y.front());
//                    TGraph *gr = new TGraph(np+1, &x[0], &y[0]);
//                    gr->Draw("apl");
//                }
//            }
//        }
//        std::cout << "Last iteration " << std::endl;
    }


}


// return output data which contains relative difference between simulation and real data
OutputData<double > *FitSuiteObserverDraw::getRelativeDifferenceMap(const OutputData<double> *p_simu_data, const OutputData<double> *p_real_data)
{
    OutputData<double > *p_difference_map = p_simu_data->clone();
    p_difference_map->setAllTo(0.0);

    OutputData<double>::const_iterator it_sim = p_simu_data->begin();
    OutputData<double>::const_iterator it_real = p_real_data->begin();
    OutputData<double>::iterator it_diff = p_difference_map->begin();

    while (it_sim != p_simu_data->end()) {
        double value_simu = *it_sim++;
        double value_real = *it_real++;
        double value_diff(0);
        if( value_real > 0) value_diff = std::abs(value_real - value_simu)/value_real;
        *it_diff = value_diff;
        ++it_diff;
    }
    return p_difference_map;
}


/* ************************************************************************* */
// Save results of each fit iteration to the disk in the form of ROOT tree
/* ************************************************************************* */
void FitSuiteObserverWriteTree::update(IObservable *subject)
{
    std::string tree_name("FitSuiteTree");

    FitSuite *fitSuite = dynamic_cast<FitSuite *>(subject);
    if( !fitSuite ) throw NullPointerException("FitSuiteObserverWriteTree::update() -> Error! Can't cast FitSuite");

    // preparing root file for writing
    // if it is first call the file will be opened in 'recreate' mode, otherwise in 'update' mode
    TFile *top(0);
    if(fitSuite->getNCall() == 0) {
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
    const OutputData<double > *real_data = fitSuite->getSuiteKit()->getRealData();
    const OutputData<double > *simu_data = fitSuite->getSuiteKit()->getSimulatedData();
    IsGISAXSTools::exportOutputDataInVectors2D(*real_data, event->real_data, event->axis0, event->axis1);
    IsGISAXSTools::exportOutputDataInVectors2D(*simu_data, event->fit_data, event->axis0, event->axis1);
    event->chi2 = fitSuite->getSuiteKit()->getChiSquaredModule()->getValue();
    for(FitSuiteParameters::iterator it = fitSuite->getFitParameters()->begin(); it!=fitSuite->getFitParameters()->end(); ++it) {
        event->parvalues.push_back( (*it)->getValue() );
        event->parnames.push_back( (*it)->getName().c_str() );
        event->parfixed.push_back( (*it)->isFixed() );
    }
    event->niter = fitSuite->getNCall();
    event->nstrategy = fitSuite->getNStrategy();

    // appending data to the tree
    tree->Fill();
    tree->Write(tree_name.c_str(), TObject::kOverwrite);
    top->Close();
    delete top; // there is no need to delete tree since ROOT file takes care about all objects opened afterwards
    delete event;
}

