// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/Utils.cpp
//! @brief     Implements various stuff in namespace Utils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Utils.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <thread>
#include <stdexcept>

#ifdef DEBUG_FPE
#ifdef Q_OS_MAC
#endif
#endif

int Utils::System::getThreadHardwareConcurrency()
{
    return std::thread::hardware_concurrency();
}

std::string Utils::System::getCurrentDateAndTime()
{
    using boost::posix_time::ptime;
    using boost::posix_time::second_clock;
    using boost::gregorian::day_clock;

    ptime todayUtc(day_clock::universal_day(), second_clock::universal_time().time_of_day());
    return to_simple_string(todayUtc);
}

//! enables exception throw in the case of NaN, Inf
void Utils::EnableFloatingPointExceptions()
{
#ifdef DEBUG_FPE
#ifndef _WIN32
    std::cout << "Utils::EnableFloatingPointExceptions() -> "
        "Enabling floating point exception debugging\n";
    feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW);
//    feenableexcept(-1);
#endif // _WIN32
#else
    std::cout << "Utils::EnableFloatingPointExceptions() -> "
        "Can't enable floating point exceptions. Available in debug mode only.\n";
#endif
}

std::pair<size_t, size_t> Utils::getShape(const std::vector<std::vector<double>>& data)
{
    size_t nrows = data.size();
    size_t ncols(0);
    if(nrows) ncols = data[0].size();
    for(size_t row=0; row<nrows; row++)
        if(data[row].size() != ncols)
            throw std::runtime_error("Utils::getShape() -> Error. "
                                     "Number of elements is different from row to row.");
    return std::make_pair(nrows, ncols);
}
