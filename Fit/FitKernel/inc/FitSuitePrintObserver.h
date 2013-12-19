// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitSuitePrintObserver.h
//! @brief     Defines class FitSuitePrintObserver.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEPRINTOBSERVER_H
#define FITSUITEPRINTOBSERVER_H

#include "IObserver.h"
#include <boost/date_time/posix_time/posix_time.hpp>


//! @class FitSuitePrintObserver
//! @ingroup fitting_internal
//! @brief Prints fit progress at the end of each FitSuite's iteration

class BA_CORE_API_ FitSuitePrintObserver : public IObserver
{
public:
    FitSuitePrintObserver(int print_every_nth = 1);
    virtual ~FitSuitePrintObserver(){}

    void update(IObservable *subject);

private:
    int m_print_every_nth;
    boost::posix_time::ptime m_start_time;
    boost::posix_time::ptime m_last_call_time;
};

#endif // FITSUITEPRINTOBSERVER_H

