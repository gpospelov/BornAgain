#ifndef MESSAGESVC_H
#define MESSAGESVC_H

#include "WinDllMacros.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>


//! Sets of logging utilities
namespace MSG
{

enum MessageLevel { VERBOSE, DEBUG, INFO, WARNING, ERROR, FATAL };


class BA_CORE_API_ Logger
{
public:
    Logger(MessageLevel level);

    template <typename T>
    Logger&  operator<<(T const&  value)
    {
        m_buffer << value;
        return *this;
    }

    ~Logger();

    std::string NowTime();
    const std::string& ToString(MessageLevel level);
    static void SetLevel(MessageLevel level);
    static void SetLevel(const std::string& levelname);
    static MessageLevel GetLevel();

private:
    static MessageLevel m_logLevel;
    static std::vector<std::string > m_level_names;
    std::ostringstream m_buffer;
};

//inline void SetLevel(MessageLevel level) { Logger::SetLevel(level); }
//inline void SetLevel(const std::string& levelname) { Logger::SetLevel(levelname); }

void SetLevel(MessageLevel level);
void SetLevel(const std::string& levelname);

}

#define msglog(level) \
if (level < MSG::Logger::GetLevel()) ; \
else MSG::Logger(level)



#endif // MESSAGESVC_H


