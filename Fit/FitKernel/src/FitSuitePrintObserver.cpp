// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/FitSuitePrintObserver.cpp
//! @brief     Implements class FitSuitePrintObserver.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuitePrintObserver.h"
#include "FitSuite.h"


FitSuitePrintObserver::FitSuitePrintObserver(int print_every_nth)
    : m_print_every_nth(print_every_nth)
    , m_start_time()
    , m_last_call_time()
{
	m_last_call_time = boost::posix_time::second_clock::local_time();
}

void FitSuitePrintObserver::update(IObservable *subject)
{
    FitSuite *fitSuite = dynamic_cast<FitSuite *>(subject);
    if( !fitSuite ) throw NullPointerException("FitSuiteObserverPrint::update() -> Error! Can't access FitSuite");

    if(fitSuite->getNCalls() == 0 ) m_start_time = boost::posix_time::second_clock::local_time();

    if( (fitSuite->getNCalls() % m_print_every_nth != 0)
            && fitSuite->getNCalls()!=0
            && !fitSuite->isLastIteration()
            ) return; // print first iteration, every n'th and last iteration

        std::cout << "FitSuitePrintObserver::update() -> Info."
                  << " NCall:" << fitSuite->getNCalls()
                  << " NStrategy:" << fitSuite->getNStrategy()
                  << " Chi2:" << std::scientific << std::setprecision(8)
                  << fitSuite->getFitObjects()->getChiSquaredValue() << std::endl;

        boost::posix_time::time_duration diff = boost::posix_time::microsec_clock::local_time() - m_last_call_time;
        std::cout << "Wall time since last call:"
                  << std::fixed << std::setprecision(2) 
                  << diff.total_milliseconds()/1000. << " sec." <<std::endl;
        m_last_call_time = boost::posix_time::microsec_clock::local_time();

        fitSuite->getFitParameters()->printParameters();

        if(fitSuite->isLastIteration()) {
            std::cout << "This was the last iteration." << std::endl;
            fitSuite->printResults();
            diff = boost::posix_time::second_clock::local_time() - m_start_time;
            std::cout << "Total time spend: "
                      << std::fixed << std::setprecision(2)
                      << diff.total_milliseconds()/1000. << " sec." <<std::endl;
        }
}
