// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/FitStrategyAdjustData.cpp
//! @brief     Implements class FitStrategyAdjustData.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitStrategyAdjustData.h"
#include "FitSuite.h"
#include "OutputDataFunctions.h"
#include "MessageService.h"



FitStrategyAdjustData::FitStrategyAdjustData(const FitStrategyAdjustData &other)
    : IFitStrategy(other)
    , m_power_of_two(other.m_power_of_two)
    , m_preserve_original_data(other.m_preserve_original_data)
    , m_call_minimize(other.m_call_minimize)
{

}


//! adjust (rebin) data before running fit suite minimization round
void FitStrategyAdjustData::execute()
{
    if( !m_fit_suite ) throw NullPointerException("FitStrategyAdjustData::execute() -> FitSuite doesn't exists");

    // if no data rediction was requested, just call FitSuite's minimization
    if( m_power_of_two == 0 ) {
        if(m_call_minimize) {
            m_fit_suite->minimize();
        }
        return;
    }

    // adjusting real data for every simulation defined
    std::vector<OutputData<double > *> original_data_collection;
    for(size_t i_exp = 0; i_exp<m_fit_suite->getFitObjects()->size(); ++i_exp) {
        // saving original data
        OutputData<double > *orig_data = m_fit_suite->getFitObjects()->getRealData()->clone();
        original_data_collection.push_back(orig_data);

        // create adjusted data which will have doubled (2,4,8,...) bin size
        OutputData<double> *adjusted_data = orig_data;
        for(size_t i=0; i<m_power_of_two; ++i) {
            OutputData<double> *new_data = OutputDataFunctions::doubleBinSize(*adjusted_data);
            if(i!=0) {
                delete adjusted_data;
            }
            adjusted_data = new_data;
        }
        m_fit_suite->getFitObjects()->setRealData(*adjusted_data, i_exp);
        delete adjusted_data;
    }

    // calling minimization
    if(m_call_minimize) {
        m_fit_suite->getMinimizer()->clear(); // clear minimizer's parameters and error matrixes
        m_fit_suite->minimize();
    }

    // setting back original data
    if(m_preserve_original_data) {
        msglog(MSG::INFO) << "FitSuiteStrategyAdjustData::execute() -> Returning original data back ";
        for(size_t i_exp = 0; i_exp<m_fit_suite->getFitObjects()->size(); ++i_exp) {
            m_fit_suite->getFitObjects()->setRealData(*original_data_collection[i_exp], i_exp);
            delete original_data_collection[i_exp];
        }
    }
}
