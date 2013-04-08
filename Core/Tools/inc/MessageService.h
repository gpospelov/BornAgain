#ifndef MESSAGESVC_H
#define MESSAGESVC_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
//#include <boost/thread.hpp>


//! Sets of logging utilities
namespace MSG
{

enum MessageLevel { VERBOSE, DEBUG, INFO, WARNING, ERROR, FATAL };


class Logger
{
 public:
    Logger(MessageLevel level) {
        //m_buffer << boost::this_thread::get_id();
        m_buffer << "- " << NowTime();
        m_buffer << " " << std::setw(8) << std::left << ToString(level) << ": ";
    }

    template <typename T>
    Logger&  operator<<(T const&  value)
    {
        m_buffer << value;
        return *this;
    }

    ~Logger()
    {
        m_buffer << std::endl;
        std::cout << m_buffer.str();
    }

    std::string NowTime();
    const std::string& ToString(MessageLevel level) {return m_level_names[level];}

    static void SetLevel(MessageLevel level) {m_logLevel = level; }
    static void SetLevel(const std::string& levelname);
    static MessageLevel GetLevel() {return m_logLevel; }

 private:
    static MessageLevel m_logLevel;
    static std::vector<std::string > m_level_names;
    std::ostringstream m_buffer;
};

inline void SetLevel(MessageLevel level) { Logger::SetLevel(level); }
inline void SetLevel(const std::string& levelname) { Logger::SetLevel(levelname); }

}

#define msglog(level) \
if (level < MSG::Logger::GetLevel()) ; \
else MSG::Logger(level)



#endif // MESSAGESVC_H


