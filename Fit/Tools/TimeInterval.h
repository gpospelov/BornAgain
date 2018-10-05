// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Tools/TimeInterval.h
//! @brief     Defines TimeInterval class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H

#include "WinDllMacros.h"
#include <memory>

class TimeIntervalImp;

class BA_CORE_API_ TimeInterval
{
public:
    TimeInterval();
    ~TimeInterval();

    void start();
    void stop();

    //! returns run time in sec.msec
    double runTime() const;

private:
    std::unique_ptr<TimeIntervalImp> m_imp;
};

#endif // TIMEINTERVAL_H
