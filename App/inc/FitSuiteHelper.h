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
#include "ChiSquaredModule.h"
#include <string>
#include <vector>

//- -------------------------------------------------------------------
//! @class FitSuiteObserverPrint
//! @brief Print fit progress at the end of each FitSuite's iteration
//- -------------------------------------------------------------------
class FitSuiteObserverPrint : public IObserver
{
public:
    FitSuiteObserverPrint() { }
    void update(IObservable *subject);
};


//- -------------------------------------------------------------------
//! @class FitSuiteObserverDraw
//! @brief Draw fit progress at the end of each FitSuite's iteration
//- -------------------------------------------------------------------
class FitSuiteObserverDraw : public IObserver
{
public:
    FitSuiteObserverDraw( const std::string &canvas_name = std::string("FitSuiteObserverDraw_c1") ) : m_canvas_name(canvas_name) , m_draw_every_nth(10) {}
    void update(IObservable *subject);

    //! return output data which contains chi2 values from ChisSquaredModule of FitSuite
    OutputData<double > *getDifferenceMap(const ChiSquaredModule *chi_module);
private:
    std::string m_canvas_name; //! canvas name were to draw
    int m_draw_every_nth;
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
