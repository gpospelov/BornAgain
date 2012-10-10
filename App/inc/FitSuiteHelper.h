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
#include <string>


//- -------------------------------------------------------------------
//! @class FitSuiteObserverDraw
//! @brief Draw fit progress at the end of each FitSuite's iteration
//- -------------------------------------------------------------------
class FitSuiteObserverDraw : public IObserver
{
public:
    FitSuiteObserverDraw(std::string canvas_name) : m_ncall(0), m_canvas_name(canvas_name) {}
    void update(IObservable *subject);
private:
    int m_ncall; //! number of call of given observer
    std::string m_canvas_name; //! canvas name were to draw
};


//- -------------------------------------------------------------------
//! @class FitSuiteObserverWrite
//! @brief Save results of each fit iteration to the disk in the form of ROOT tree
//! If tree exist, data will be appended to it
//- -------------------------------------------------------------------
class FitSuiteObserverWriteTree : public IObserver
{
public:
    FitSuiteObserverWriteTree(std::string file_name) : m_ncall(0), m_file_name(file_name) {}
    void update(IObservable *subject);
private:
    int m_ncall;
    std::string m_file_name; //! canvas name were to draw
};




#endif // FITSUITEHELPER_H
