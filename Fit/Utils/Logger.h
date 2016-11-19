// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Utils/Logger.h
//! @brief     Defines MSG namespace and Logger class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LOGGER_H
#define LOGGER_H

#include "WinDllMacros.h"
#include <iomanip>
#include <sstream>
#include <vector>

//! Logging utility.

namespace MSG
{

enum EMessageLevel { VERBOSE, DEBUG2, DEBUG, INFO, WARNING, ERROR, FATAL };

//! @class Logger
//! @ingroup tools_internal
//! @brief Provides message service

class BA_CORE_API_ Logger
{
public:
    Logger(EMessageLevel level);

    template <typename T>
    Logger&  operator<<(T const&  value)
    {
        m_buffer << value;
        return *this;
    }

    ~Logger();

    std::string NowTime();
    const std::string& ToString(EMessageLevel level);
    static void SetLevel(EMessageLevel level);
    static void SetLevel(const std::string& levelname);
    static EMessageLevel GetLevel();

private:
    static EMessageLevel m_logLevel;
    static std::vector<std::string > m_level_names;
    std::ostringstream m_buffer;
};

//inline void SetLevel(MessageLevel level) { Logger::SetLevel(level); }
//inline void SetLevel(const std::string& levelname) { Logger::SetLevel(levelname); }

BA_CORE_API_ void SetLevel(EMessageLevel level);
BA_CORE_API_ void SetLevel(const std::string& levelname);

} // namespace MSG

#define msglog(level) \
if (level < MSG::Logger::GetLevel()) ; \
else MSG::Logger(level)

#endif // LOGGER_H
