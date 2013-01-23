#ifndef ROOTMINIMIZEROPTIONS_H
#define ROOTMINIMIZEROPTIONS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ROOTMinimizerOptions.h
//! @brief  Definition of ROOTMinimizerOptions class
//! @author Scientific Computing Group at FRM II
//! @date   23.01.2013

#include "ROOTMinimizer.h"
#include "ROOTGSLSimAnMinimizer.h"


//- -------------------------------------------------------------------
//! @class ROOTMinimizerOptionsHelper
//! @brief Handles string representation of ROOTMinimizer options
//- -------------------------------------------------------------------
// TODO: replace ROOTMinimizerOptionsHelper completely with kind of PoolParameter/IConfigurable functionality
class ROOTMinimizerOptionsHelper
{
public:
    ROOTMinimizerOptionsHelper() { }
    //! translate text with options into appropriate calls of minimizer's set method
    static void setOptions(ROOT::Math::Minimizer *minimizer, const std::string &options);

private:
    //! process single command
    static bool processCommand(ROOT::Math::Minimizer *minimizer, const std::string &command);

    //! process single command common for all minimizers
    static bool processCommandAll(ROOT::Math::Minimizer *minimizer, const std::string &command);

    //! process single command specific for GSL simulated annealing minimizer
    static bool processCommandGSLSimAn(ROOT::Patch::GSLSimAnMinimizer *, const std::string &command);

};


#endif // ROOTMINIMIZEROPTIONS_H
