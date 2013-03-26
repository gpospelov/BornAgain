// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/FitSuiteObserverFactory.h 
//! @brief     Defines classes FitSuiteObserverFactory, FitSuiteObserverPrint, FitSuiteObserverDraw, FitSuiteObserverWriteTree
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FITSUITEHELPER_H
#define FITSUITEHELPER_H


#include "IObserver.h"
#include "OutputData.h"
#include "IChiSquaredModule.h"
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <sys/time.h>
#include <boost/shared_ptr.hpp>
#include "TH1.h"

class TPaveText;
class TCanvas;

//! Print fit progress at the end of each FitSuite's iteration.

class FitSuiteObserverPrint : public IObserver
{
 public:
    FitSuiteObserverPrint(int print_every_nth = 1)
        : m_print_every_nth(print_every_nth)
        , m_wall_time(0.0)
        , m_last_call_clock(clock())
        , m_last_call_time()
    { gettimeofday(&m_last_call_time, 0); }
    void update(IObservable *subject);
 private:
    int m_print_every_nth;
    double m_wall_time;
    clock_t m_last_call_clock;
    timeval m_last_call_time;
};

//! Draw fit progress at the end of each FitSuite's iteration.

class FitSuiteObserverDraw : public IObserver
{
 public:
    FitSuiteObserverDraw(
        int draw_every_nth = 20,
        const std::string &canvas_base_name =
        std::string("FitSuiteObserverDraw") )
        : m_draw_every_nth(draw_every_nth)
        , m_canvas_base_name(canvas_base_name)
        , m_ptext(0)
        , m_stat_canvas(0) {}

    ~FitSuiteObserverDraw() {}

    void update(IObservable *subject);

    //! Return relative difference between simulation and real data.
    OutputData<double > *getRelativeDifferenceMap(
        const OutputData<double> *p_simu_data,
        const OutputData<double> *p_real_data);

 private:
    int m_draw_every_nth; //! update canvas every nth iteration
    std::string m_canvas_base_name; //! canvas name were to draw
    TPaveText *m_ptext;
    TCanvas *m_stat_canvas;
    std::vector<TCanvas *> m_data_canvas;
};


//! Save results of each fit iteration to the disk in the form of ROOT tree.

//! If tree exist, data will be appended to it
//!
class FitSuiteObserverWriteTree : public IObserver
{
 public:
    FitSuiteObserverWriteTree(
        const std::string &file_name = std::string("fitsuite.root"))
        : m_file_name(file_name), m_prev_data(0) {}
    void update(IObservable *subject);
 private:
    std::string m_file_name; //! canvas name were to draw
    OutputData<double> *m_prev_data;
};

//! ?

class FitSuiteObserverFactory
{
 public:
    typedef boost::shared_ptr<FitSuiteObserverPrint > observer_print_t;
    typedef boost::shared_ptr<FitSuiteObserverDraw > observer_draw_t;
    typedef boost::shared_ptr<FitSuiteObserverWriteTree > observer_tree_t;

    static observer_print_t createPrintObserver(int run_every_nth=20) {
        return observer_print_t( new FitSuiteObserverPrint(run_every_nth) );
    }

    static observer_draw_t createDrawObserver(int run_every_nth=20) {
        return observer_draw_t( new FitSuiteObserverDraw(run_every_nth) );
    }

    static observer_tree_t createTreeObserver() {
        return observer_tree_t( new FitSuiteObserverWriteTree() );
    }
};

#endif // FITSUITEHELPER_H
