// Print values of parameters after each change of strategy
//
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TSystem.h"
#include "TPaveText.h"
#include "TProfile2D.h"


using namespace std;
#include "FitData.C"

typedef std::vector<double > vdouble1d_t;
typedef std::vector<vdouble1d_t > vdouble2d_t;


struct FitResults
{
    double chi2;
    vdouble1d_t pars;
    std::vector<bool > fixed;
};


/* ************************************************************************* */
// main analysis: read all fit iterations and nicely draw real/fit data
/* ************************************************************************* */
void fitlog(const char *file_name = "../../../../fitsuite.root")
{
    const char *tree_name = "FitSuiteTree";
    TChain *chain = new TChain(tree_name);
    chain->Add(file_name);

    FitData *event = new FitData(chain);
    // reading first event to load event with the content of first iteration
    chain->GetEntry(0);
    //chain->Print();

    FitResults fitResults;
    FitResults fitResultsPrev;
    std::vector<FitResults > FitHistory;

    std::cout << "Number of entries: " << chain->GetEntries() << std::endl;
    int i_entry(0);
    int n_prev_strategy(-1);
    while(chain->GetEntry(i_entry++)){
        if(i_entry%100 == 0) std::cout << i_entry << std::endl;

        fitResults.chi2 = event->chi2;
        fitResults.fixed = event->parfixed;
        fitResults.pars = event->parvalues;

        if(event->nstrategy != n_prev_strategy) {
            std::cout << "i_entry: " << i_entry << " strategy:" << event->nstrategy << std::endl;
            if(n_prev_strategy==-1) {
                FitHistory.push_back(fitResults); // initial values of pars
            } else {
                FitHistory.push_back(fitResultsPrev);
            }
        }

        n_prev_strategy = event->nstrategy;
        fitResultsPrev = fitResults;
    } // loop over recorder events

    for(size_t i_par=0; i_par < event->parvalues.size(); ++i_par) {
        std::string parname = event->parnames[i_par];
        parname.resize(25,' ');
        std::cout << parname << " ";
       for(size_t i_hist=0; i_hist<FitHistory.size(); ++i_hist) {
            std::cout << std::scientific << std::setprecision(4) << FitHistory[i_hist].pars[i_par];
            if(FitHistory[i_hist].fixed[i_par]) {
                std::cout << "* ";
            }else{
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "chi2                      ";
    for(size_t i_hist=0; i_hist<FitHistory.size(); ++i_hist) {
        std::cout << std::scientific << std::setprecision(4) << FitHistory[i_hist].chi2 << "  ";
    }
    std::cout << std::endl;

    
//     std::cout << "XXX " << pars.size() << std::endl;
//     for(size_t i_par=0; i_par < pars.size(); ++i_par) {
//         for(size_t i_hist=0; i_hist<parshistory.size(); ++i_hist) {
//             std::cout << i_par << " " << i_hist << " " << parshistory.size() << " " << parshistory[i_hist].size() << std::endl;
//             std::cout << std::scientific << std::setprecision(4) << parshistory[i_hist][i_par] << " ";
//         }
//         std::cout << std::endl;
//     }
} 


