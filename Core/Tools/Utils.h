// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/Utils.h
//! @brief     Declares various stuff in namespace Utils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef UTILS_H
#define UTILS_H

#include "WinDllMacros.h"
#include <map>
#include <string>
#include <vector>

namespace Utils {

//! @class String
//! @ingroup tools_internal
//! @brief Collection of utilities for std::string.

class BA_CORE_API_ String
{
public:
    //! assuming that string consist of doubles return new string
    //! where doubles are rounded according to the precision
    static std::string round_doubles(const std::string& str, int precision);

    //! Split string into vector of string using delimeter.
    static std::vector<std::string> split(const std::string& text, const std::string& delimeter);

    //! replace all occurences of items from string text with delimeter
    static void replaceItemsFromString(std::string& text, const std::vector<std::string>& items,
                                       const std::string& replacement=std::string(""));

    //! return string representing scientific double with given precision
    static std::string getScientificDoubleString(double value, size_t precision = 4);

    //! Returns string obtain by joining vector elements
    static std::string join(const std::vector<std::string>& joinable, const std::string& joint);

    //! Returns flattened filename, i.e. all directory separator ('/' or '\') are replaced by '_'.
    static std::string flatFilename(const std::string& filename);
};


//! @class StringUsageMap
//! @ingroup tools_internal
//! @brief Control how often a string is used.

class BA_CORE_API_ StringUsageMap
{
public:
    typedef std::map<std::string, int> nstringmap_t;
    typedef nstringmap_t::iterator iterator_t;

    StringUsageMap(){}
    ~StringUsageMap(){}

    //! Adds string to the map to count number of times it was used
    void add(std::string name)
    {
        m_current_string = name;
        iterator_t it = m_nstringmap.find(name);
        if(it != m_nstringmap.end() ) {
            // such string already exists, incremeting usage counter
            (*it).second++;
        } else {
            // such string doesnt exist, insert it with counter=1
            m_nstringmap.insert(nstringmap_t::value_type(name,1));
        }
    }

    //! access to the map of strings
    iterator_t begin() { return m_nstringmap.begin(); }
    iterator_t end() { return m_nstringmap.end(); }
    int& operator[](std::string name) { return m_nstringmap[name]; }

    //! Returns current string
    std::string get_current() const { return m_current_string; }

private:
    std::string m_current_string;
    nstringmap_t m_nstringmap;
};


class BA_CORE_API_ System
{
public:
    static int getThreadHardwareConcurrency();
    static std::string getCurrentDateAndTime();
};

//! enables exception throw in the case of NaN, Inf
BA_CORE_API_ void EnableFloatingPointExceptions();
}

#endif // UTILS_H
