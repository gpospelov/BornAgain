// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Utils/TimeInterval.cpp
//! @brief     Implements TimeInterval class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TimeInterval.h"
#include <boost/date_time/posix_time/posix_time.hpp>

class TimeIntervalImp
{
public:
    boost::posix_time::ptime m_start_time;
    boost::posix_time::ptime m_end_time;
    bool m_is_running;
    TimeIntervalImp() : m_is_running(false){}
};

TimeInterval::TimeInterval()
    : m_imp(new TimeIntervalImp)
{

}

TimeInterval::~TimeInterval()
{

}

void TimeInterval::start()
{
    m_imp->m_is_running = true;
    m_imp->m_start_time = boost::posix_time::microsec_clock::local_time();
}

void TimeInterval::stop()
{
    m_imp->m_is_running = false;
    m_imp->m_end_time = boost::posix_time::microsec_clock::local_time();
}

double TimeInterval::runTime() const
{
    boost::posix_time::time_duration diff ;
    if(m_imp->m_is_running) {
        diff = boost::posix_time::microsec_clock::local_time() - m_imp->m_start_time;
    } else {
        diff = m_imp->m_end_time - m_imp->m_start_time;
    }
    return diff.total_milliseconds()/1000.;
}
