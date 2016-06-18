// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/MessageService.cpp
//! @brief     Implement Logger class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Exceptions.h"
#include "MessageService.h"
#include <boost/date_time/posix_time/posix_time.hpp>

std::vector<std::string> MSG::Logger::m_level_names =
    {"VERBOSE", "DEBUG2", "DEBUG", "INFO", "WARNING", "ERROR", "FATAL"};

MSG::EMessageLevel MSG::Logger::m_logLevel = MSG::ERROR;

namespace MSG
{

void SetLevel(EMessageLevel level)
{
    Logger::SetLevel(level);
}

void SetLevel(const std::string& levelname)
{
    Logger::SetLevel(levelname);
}


Logger::Logger(EMessageLevel level)
{
    //m_buffer << boost::this_thread::get_id();
    m_buffer << "- " << NowTime();
    m_buffer << " " << std::setw(8) << std::left << ToString(level) << ": ";
}


Logger::~Logger()
{
    m_buffer << std::endl;
    std::cout << m_buffer.str();
}

const std::string& Logger::ToString(EMessageLevel level)
{
    return m_level_names[level];
}

void Logger::SetLevel(EMessageLevel level)
{
    m_logLevel = level;
}

EMessageLevel Logger::GetLevel()
{
    return m_logLevel;
}

std::string Logger::NowTime()
{
    //struct timeval tv;
    //gettimeofday(&tv, 0);
    //char buffer[100];
    //tm r;
    //strftime(buffer, sizeof(buffer), "%X", localtime_r(&tv.tv_sec, &r));
    //char result[100];
    //sprintf(result, "%s.%06ld", buffer, (long)tv.tv_usec);

    std::ostringstream msg;
    //const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    boost::posix_time::time_facet*const f=new boost::posix_time::time_facet("%H-%M-%S");
    msg.imbue(std::locale(msg.getloc(),f));
    return msg.str();
}

void Logger::SetLevel(const std::string& levelname)
{
    int index(0);
    for(auto it = m_level_names.begin(); it!=m_level_names.end(); ++it) {
        if( (*it) == levelname ) {
            SetLevel(EMessageLevel(index));
            return;
        }
        ++index;
    }
    throw Exceptions::LogicErrorException(
        "Logger::SetLevel() -> Error! There is no message level '"+levelname+"'");
}

}
