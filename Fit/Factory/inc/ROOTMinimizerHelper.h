#ifndef ROOTMINIMIZERHELPER_H
#define ROOTMINIMIZERHELPER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ROOTMinimizerHelper.h
//! @brief  Definition of ROOTMinimizerHelper class
//! @author Scientific Computing Group at FRM II
//! @date   23.01.2013

#include "ROOTMinimizer.h"
#include "ROOTGSLSimAnMinimizer.h"


//- -------------------------------------------------------------------
//! @class ROOTMinimizerHelper
//! @brief Handles options and printing for ROOTMinimizer
//- -------------------------------------------------------------------
// TODO: replace ROOTMinimizersHelper completely with kind of PoolParameter/IConfigurable functionality
class ROOTMinimizerHelper
{
 public:
    ROOTMinimizerHelper() { }

    //! translate text with options into appropriate calls of minimizer's set method
    static void setOptions(ROOT::Math::Minimizer *minimizer, const std::string &options);

    //! print results of minimization
    static void printResults(ROOT::Math::Minimizer *minimizer, const std::string &minimizer_name, const std::string &algo_type);


 private:
    //! process single command
    static bool processCommand(ROOT::Math::Minimizer *minimizer, const std::string &command);

    //! process single command common for all minimizers
    static bool processCommandAll(ROOT::Math::Minimizer *minimizer, const std::string &command);

    //! process single command specific for GSL simulated annealing minimizer
    static bool processCommandGSLSimAn(ROOT::Patch::GSLSimAnMinimizer *, const std::string &command);

    //! print minimizer options
    static void printOptions(ROOT::Math::Minimizer *minimizer);

    //! print minimizer status
    static void printStatus(ROOT::Math::Minimizer *minimizer);

    //! print variables
    static void printVariables(ROOT::Math::Minimizer *minimizer);

};


#endif // ROOTMINIMIZERHELPER_H
