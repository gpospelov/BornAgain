#include "MessageService.h"
#include <boost/assign/list_of.hpp>
#include "Exceptions.h"
//#include <sys/time.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdio>

std::vector<std::string> MSG::Logger::m_level_names =
        boost::assign::list_of("VERBOSE")("DEBUG")("INFO")("WARNING")("ERROR")("FATAL");

MSG::MessageLevel MSG::Logger::m_logLevel = MSG::ERROR;

namespace MSG
{

void SetLevel(MessageLevel level) 
{ 
	Logger::SetLevel(level); 
}

void SetLevel(const std::string& levelname) 
{ 
	Logger::SetLevel(levelname); 
}


Logger::Logger(MessageLevel level) 
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

const std::string& Logger::ToString(MessageLevel level) 
{
	return m_level_names[level];
}

void Logger::SetLevel(MessageLevel level) 
{
	m_logLevel = level; 
}

MessageLevel Logger::GetLevel() 
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




