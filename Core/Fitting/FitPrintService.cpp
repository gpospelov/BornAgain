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

#include "FitPrintService.h"
#include "FitObjective.h"
#include <iostream>
#include <iomanip>

FitPrintService::FitPrintService()
{

}

void FitPrintService::print(const FitObjective& objective)
{
    if (objective.iterationCount() == 0) {
        m_run_time.start();
        m_last_call_time.start();
    }

    std::cout << "FitPrintService::print() " << objective.iterationCount() << std::endl;

    if (objective.isCompleted())
        printFitResults();

}

void FitPrintService::printFitResults()
{
    std::cout << "This was the last iteration." << std::endl;
    m_run_time.stop();
    std::cout << "Total time spend: " << std::fixed << std::setprecision(2)
              << m_run_time.runTime() << " sec." <<std::endl;
    std::cout << std::endl;
}
