#include "FitSuitePrintObserver.h"
#include "FitSuite.h"


FitSuitePrintObserver::FitSuitePrintObserver(int print_every_nth)
    : m_print_every_nth(print_every_nth)
    , m_last_call_clock(clock())
    , m_last_call_time()
{
    gettimeofday(&m_last_call_time, 0);
}

void FitSuitePrintObserver::update(IObservable *subject)
{
    FitSuite *fitSuite = dynamic_cast<FitSuite *>(subject);
    if( !fitSuite ) throw NullPointerException("FitSuiteObserverPrint::update() -> Error! Can't access FitSuite");

    if(fitSuite->isLastIteration()) {
        std::cout << std::endl;
        std::cout << "FitSuiteObserverPrint::update() -> Info. Printing results" << std::endl;
        fitSuite->printResults();
    } else {
        if( (fitSuite->getNCalls() % m_print_every_nth != 0) && fitSuite->getNCalls()!=0) return; // print first iteration and then every n'th

        std::cout << "FitSuitePrintObserver::update() -> Info."
                  << " NCall:" << fitSuite->getNCalls()
                  << " NStrategy:" << fitSuite->getNStrategy()
                  << " Chi2:" << std::scientific << std::setprecision(8)
                  << fitSuite->getFitObjects()->getChiSquaredValue() << std::endl;

        std::cout << "Time spend since last call, cpu:"
                  << std::fixed << std::setprecision(2) << getCpuTimeSinceLastCall()
                  << " sec, wall time " << getWallTimeSinceLastCall() << "sec" << std::endl;

        fitSuite->getFitParameters()->printParameters();
    }
}

double FitSuitePrintObserver::getCpuTimeSinceLastCall()
{
    clock_t call_clock = clock();
    double result = double(call_clock-m_last_call_clock)/CLOCKS_PER_SEC;
    m_last_call_clock = call_clock;
    return result;
}


double FitSuitePrintObserver::getWallTimeSinceLastCall()
{
    timeval call_time;
    gettimeofday(&call_time, 0);
    double result = (call_time.tv_sec - m_last_call_time.tv_sec) + double(call_time.tv_usec - m_last_call_time.tv_usec)/1e+06;
    m_last_call_time = call_time;
    return result;
}



