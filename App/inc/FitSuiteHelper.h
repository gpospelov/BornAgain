#ifndef FITSUITEHELPER_H
#define FITSUITEHELPER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitSuiteHelper.h
//! @brief  Collection of helper classes for fitting from App
//! @author Scientific Computing Group at FRM II
//! @date   08.10.2012


#include "IObserver.h"
#include "OutputData.h"
#include "IChiSquaredModule.h"
#include <string>
#include <vector>
#include <time.h>
#include <sys/time.h>


class TPaveText;

//- -------------------------------------------------------------------
//! @class FitSuiteObserverPrint
//! @brief Print fit progress at the end of each FitSuite's iteration
//- -------------------------------------------------------------------
class FitSuiteObserverPrint : public IObserver
{
public:
    FitSuiteObserverPrint() : m_wall_time(0.0), m_last_call_clock(clock()), m_last_call_time() {
        gettimeofday(&m_last_call_time, 0);
    }
    void update(IObservable *subject);
private:
    double m_wall_time;
    clock_t m_last_call_clock;
    timeval m_last_call_time;
};


//- -------------------------------------------------------------------
//! @class FitSuiteObserverDraw
//! @brief Draw fit progress at the end of each FitSuite's iteration
//- -------------------------------------------------------------------
class FitSuiteObserverDraw : public IObserver
{
public:
    FitSuiteObserverDraw( int draw_every_nth = 20, const std::string &canvas_name = std::string("FitSuiteObserverDraw_c1") ) : m_draw_every_nth(draw_every_nth), m_canvas_name(canvas_name) , m_ptext(0) {}
    void update(IObservable *subject);

    //! return output data which contains relative difference between simulation and real data
    OutputData<double > *getRelativeDifferenceMap(const OutputData<double> *p_simu_data, const OutputData<double> *p_real_data);

private:
    int m_draw_every_nth; //! update canvas every nth iteration
    std::string m_canvas_name; //! canvas name were to draw
    TPaveText *m_ptext;
};


//- -------------------------------------------------------------------
//! @class FitSuiteObserverWrite
//! @brief Save results of each fit iteration to the disk in the form of ROOT tree
//! If tree exist, data will be appended to it
//- -------------------------------------------------------------------
class FitSuiteObserverWriteTree : public IObserver
{
public:
    FitSuiteObserverWriteTree(const std::string &file_name = std::string("fitsuite.root")) : m_file_name(file_name) {}
    void update(IObservable *subject);
private:
    std::string m_file_name; //! canvas name were to draw
};




#endif // FITSUITEHELPER_H
