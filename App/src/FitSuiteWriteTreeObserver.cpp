// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/FitSuiteWriteTreeObserver.cpp
//! @brief     Implements class FitSuiteWriteTreeObserver.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuiteWriteTreeObserver.h"
#include "FitSuite.h"
#include "TreeEventStructure.h"
#include "IsGISAXSTools.h"

#include "TFile.h"
#include "TTree.h"

FitSuiteWriteTreeObserver::FitSuiteWriteTreeObserver(const std::string &file_name)
    : m_file_name(file_name)
    , m_prev_data(0)
{ }


/* ************************************************************************* */
// Save results of each fit iteration to the disk in the form of ROOT tree
/* ************************************************************************* */
void FitSuiteWriteTreeObserver::update(IObservable *subject)
{
    std::string tree_name("FitSuiteTree");

    FitSuite *fitSuite = dynamic_cast<FitSuite *>(subject);
    if( !fitSuite ) throw NullPointerException("FitSuiteObserverWriteTree::update() -> Error! Can't cast FitSuite");

    // preparing root file for writing
    // if it is first call the file will be opened in 'recreate' mode, otherwise in 'update' mode
    TFile *top(0);
    if(fitSuite->getNumberOfIterations() == 0) {
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
    const OutputData<double > *real_data = fitSuite->getFitObjects()->getRealData();
    const OutputData<double > *simu_data = fitSuite->getFitObjects()->getSimulationData();
    IsGISAXSTools::exportOutputDataInVectors2D(*real_data, event->real_data, event->axis0, event->axis1);
    IsGISAXSTools::exportOutputDataInVectors2D(*simu_data, event->fit_data, event->axis0, event->axis1);

    // this block is to save axis information in the tree only if data shape has changed
    if(m_prev_data == 0) {
        m_prev_data = simu_data->clone();
    } else {
        if( !m_prev_data->hasSameShape(*simu_data) ) {
            delete m_prev_data;
            m_prev_data = simu_data->clone();
        } else {
            event->axis0.clear();
            event->axis1.clear();
        }
    }

    event->chi2 = fitSuite->getFitObjects()->getChiSquaredValue();
    for(FitSuiteParameters::iterator it = fitSuite->getFitParameters()->begin(); it!=fitSuite->getFitParameters()->end(); ++it) {
        event->parvalues.push_back( (*it)->getValue() );
        event->parnames.push_back( (*it)->getName().c_str() );
        event->parfixed.push_back( (*it)->isFixed() );
    }
    event->niter = (int)fitSuite->getNumberOfIterations();
    event->nstrategy = (int)fitSuite->getCurrentStrategyIndex();

    // appending data to the tree
    tree->Fill();
    tree->Write(tree_name.c_str(), TObject::kOverwrite);
    top->Close();
    delete top; // there is no need to delete tree since ROOT file takes care about all objects opened afterwards
    delete event;
}



