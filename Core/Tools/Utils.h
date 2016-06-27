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
#include "Exceptions.h"
#include <boost/unordered_map.hpp>
#include <vector>
#include <map>
#include <list>

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

    //! Returns true if text matches pattern with wildcards '*' and '?'.
    static bool MatchPattern(const std::string& text, std::string wildcardPattern);

    //! Split string into vector of string using delimeter.
    static std::vector<std::string> Split(const std::string& text, const std::string& delimeter);

    //! replace all occurences of items from string text with delimeter
    static void replaceItemsFromString(std::string& text, const std::vector<std::string>& items,
                                       const std::string& replacement=std::string(""));

    //! return string representing scientific double with given precision
    static std::string getScientificDoubleString(double value, size_t precision = 4);
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


inline std::string AdjustStringLength(std::string name, int length)
{
    std::string newstring = name;
    newstring.resize(length,' ');
    return newstring;
}


//! @class OrderedMap
//! @ingroup tools_internal
//! @brief Ordered map which saves the order of insertion

template<class Key, class Object>
class OrderedMap
{
public:
    typedef std::pair<Key, Object> entry_t;
    typedef std::list<entry_t> list_t;
    typedef typename list_t::iterator iterator;
    typedef typename list_t::const_iterator const_iterator;
    typedef boost::unordered_map<Key, iterator> map_t;

    OrderedMap() {}
    virtual ~OrderedMap(){}

    void clear() {
        m_map.clear();
        m_list.clear();
    }

    const_iterator begin() const { return m_list.begin(); }
    const_iterator end() const { return m_list.end(); }
    iterator begin() { return m_list.begin(); }
    iterator end() { return m_list.end(); }

    size_t size() {
        assert(m_list.size() == m_map.size());
        return m_list.size();
    }

    // if such key exists, pair will be deleted, and new pair appended to the end
    void insert(const Key& key, const Object& object) {
        erase(key);
        iterator it = m_list.insert(m_list.end(), std::make_pair(key, object));
        m_map[key] = it;
    }

    const iterator find(const Key& key) const {
        if(m_map.find(key) == m_map.end())
            return m_list.end();
        return m_map[key];
    }

    iterator find(const Key& key) {
        if(m_map.find(key) == m_map.end())
            return m_list.end();
        return m_map[key];
    }

    size_t erase(const Key& key) {
        size_t result(0);
        if(m_map.find(key) == m_map.end())
            return result;
        iterator it = m_map[key];
        m_list.erase(it);
        m_map.erase(key);
        return 1;
    }

    const Object& value(const Key& key) {
        typename map_t::const_iterator mit = m_map.find(key);
        if(mit == m_map.end())
            throw RuntimeErrorException("OrderedMap::value() -> No such key");
        const_iterator it = mit->second;
        return (*it).second;
    }

    const Object& operator[](const Key& key) { return value(key); }

private:
    map_t m_map;
    list_t m_list;
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
