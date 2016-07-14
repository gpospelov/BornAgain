// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/FitSuitePrintObserver.h
//! @brief     Declares class FitSuitePrintObserver.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEPRINTOBSERVER_H
#define FITSUITEPRINTOBSERVER_H

#include "IFitObserver.h"
#include <boost/date_time/posix_time/posix_time.hpp>

//! @class FitSuitePrintObserver
//! @ingroup fitting_internal
//! @brief Prints fit progress at the end of each FitSuite's iteration

class BA_CORE_API_ FitSuitePrintObserver : public IFitObserver
{
public:
    FitSuitePrintObserver(int print_every_nth = 1);
    virtual ~FitSuitePrintObserver() {}

    void update(FitSuite *fit_suite);

protected:
    void printIterationHeader();
    void printWallTime();
    void printParameters();
    void printFitResults();

    FitSuite *m_fit_suite;
    boost::posix_time::ptime m_start_time;
    boost::posix_time::ptime m_last_call_time;
};

#endif // FITSUITEPRINTOBSERVER_H


