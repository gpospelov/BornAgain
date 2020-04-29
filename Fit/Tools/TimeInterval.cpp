// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Tools/TimeInterval.cpp
//! @brief     Implements TimeInterval class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "TimeInterval.h"
#include <chrono>

using clock_used = std::chrono::high_resolution_clock;
using duration_unit = std::chrono::milliseconds;

class TimeIntervalImp
{
public:
    std::chrono::time_point<clock_used> m_start_time;
    std::chrono::time_point<clock_used> m_end_time;
    bool m_is_running;
    TimeIntervalImp() : m_is_running(false) {}
};

TimeInterval::TimeInterval() : m_imp(new TimeIntervalImp) {}

TimeInterval::~TimeInterval() = default;

void TimeInterval::start()
{
    m_imp->m_is_running = true;
    m_imp->m_start_time = clock_used::now();
}

void TimeInterval::stop()
{
    m_imp->m_is_running = false;
    m_imp->m_end_time = clock_used::now();
}

double TimeInterval::runTime() const
{
    duration_unit diff =
        m_imp->m_is_running
            ? std::chrono::duration_cast<duration_unit>(clock_used::now() - m_imp->m_start_time)
            : std::chrono::duration_cast<duration_unit>(m_imp->m_end_time - m_imp->m_start_time);

    return diff.count() / 1000.;
}
