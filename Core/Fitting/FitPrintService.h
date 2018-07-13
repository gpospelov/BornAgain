// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitPrintService.h
//! @brief     Defines class FitPrintService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITPRINTSERVICE_H
#define FITPRINTSERVICE_H

#include "WinDllMacros.h"
#include "TimeInterval.h"

class FitObjective;

//! Prints fit statistics to standard output during minimizer iterations.

class BA_CORE_API_ FitPrintService
{
public:
    FitPrintService();

    void print(const FitObjective& objective);

private:
    void printFitResults();

    TimeInterval m_run_time;
    TimeInterval m_last_call_time;
};

#endif
