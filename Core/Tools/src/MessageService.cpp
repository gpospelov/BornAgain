#include "MessageService.h"
#include "Macros.h"
GCC_DIAG_OFF(unused-local-typedefs);
#include <boost/assign/list_of.hpp>
GCC_DIAG_ON(unused-local-typedefs);
#include "Exceptions.h"
#include <sys/time.h>
#include <cstdio>

std::vector<std::string> MSG::Logger::m_level_names =
        boost::assign::list_of("VERBOSE")("DEBUG")("INFO")("WARNING")("ERROR")("FATAL");

MSG::MessageLevel MSG::Logger::m_logLevel = MSG::ERROR;

namespace MSG
{

std::string Logger::NowTime()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    char buffer[100];
    tm r;
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&tv.tv_sec, &r));
    char result[100];
    sprintf(result, "%s.%06ld", buffer, (long)tv.tv_usec);
    return result;
}

void Logger::SetLevel(const std::string& levelname)
{
    int index(0);
    for(std::vector<std::string >::iterator it = m_level_names.begin(); it!=m_level_names.end(); ++it) {
        if( (*it) == levelname ) {
            SetLevel(MessageLevel(index));
            return;
        }
        ++index;
    }
    throw LogicErrorException("Logger::SetLevel() -> Error! There is no message level '"+levelname+"'");
}

}




