#ifndef FITSUITEPRINTOBSERVER_H
#define FITSUITEPRINTOBSERVER_H

#include "IObserver.h"
#include <time.h>
#include <sys/time.h>

//! Print fit progress at the end of each FitSuite's iteration
class FitSuitePrintObserver : public IObserver
{
public:
    FitSuitePrintObserver(int print_every_nth = 1);
    virtual ~FitSuitePrintObserver(){}

    void update(IObservable *subject);

    double getCpuTimeSinceLastCall();

    double getWallTimeSinceLastCall();

private:
    int m_print_every_nth;
    double m_wall_time;
    clock_t m_last_call_clock;
    timeval m_last_call_time;
};

#endif // FITSUITEPRINTOBSERVER_H


