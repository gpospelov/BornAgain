#include "FittingHelper.h"
#include "FitSuite.h"
#include "IsGISAXSTools.h"

#include "TCanvas.h"
#include "TPaveText.h"
#include "ChiSquaredModule.h"
#include "TROOT.h"

void FittingHelper::ObserveAndDraw::update(IObservable *subject)
{
    FitSuite *fitSuite = dynamic_cast<FitSuite *>(subject);
    if( !fitSuite ) throw NullPointerException("LocalFitObserver::IObserver() -> Error! Can't cast FitSuite");

    std::cout << "FitObserver: " << " ncall" << m_ncall << " chi2:" << fitSuite->getChiSquaredModule()->getValue();
    // printing parameter values
    for(FitSuite::fitparameters_t::iterator it = fitSuite->fitparams_begin(); it!=fitSuite->fitparams_end(); ++it) {
        std::cout << " " << (*it)->getName() << " " << (*it)->getValue();
        //            std::cout << *(*it);
    }
    std::cout << std::endl;

    TCanvas *c1 = dynamic_cast<TCanvas *>( gROOT->FindObject(m_canvas_name.c_str()) );
    if(!c1) throw NullPointerException("LocalFitIbserver::update() -> No access to canvas");
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


