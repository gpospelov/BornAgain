// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/ROOTMinimizerHelper.h
//! @brief     Declares class ROOTMinimizerHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTMINIMIZERHELPER_H
#define ROOTMINIMIZERHELPER_H

#include "ROOTMinimizer.h"


//! @class ROOTMinimizerHelper
//! @ingroup fitting_internal
//! @brief Handles options and printing for ROOTMinimizer
//! Required by Fumili, Fumili2 and GSLMultiMin minimizers

class BA_CORE_API_ ROOTMinimizerHelper
{
 public:
    ROOTMinimizerHelper() { }

    //! translate text with options into appropriate calls of minimizer's
    //! set method
    static void setOptions(BA_ROOT::Math::Minimizer *minimizer,
            const std::string& options);

    //! Prints results of minimization
    static void printResults(const ROOTMinimizer *minimizer);

 private:
    //! process single command
//    static bool processCommand(ROOT::Math::Minimizer *minimizer,
//            const std::string& command);

//    //! process single command common for all minimizers
//    static bool processCommandAll(ROOT::Math::Minimizer *minimizer,
//            const std::string& command);

//    //! process single command specific for GSL simulated annealing minimizer
//    static bool processCommandGSLSimAn(ROOT::Patch::GSLSimAnMinimizer *minimizer,
//            const std::string& command);

    //! Prints minimizer options
    static void printOptions(const BA_ROOT::Math::Minimizer *minimizer);

    //! Prints minimizer status
    static void printStatus(const BA_ROOT::Math::Minimizer *minimizer);

    //! Prints variables
    static void printVariables(const BA_ROOT::Math::Minimizer *minimizer);

};


#endif // ROOTMINIMIZERHELPER_H
