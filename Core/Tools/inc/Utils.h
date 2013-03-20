// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/Utils.h
//! @brief     Various stuff in namespace Utils.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef UTILS_H
#define UTILS_H

#include "Types.h"
//#include <string>
//#include <vector>
//#include <map>
//#include <iostream>
//#include <sstream>
//#include "Exceptions.h"
#include <boost/unordered_map.hpp>

namespace Utils {

//- -------------------------------------------------------------------
//! @class String
//! @brief Collection of utilities for std::string
//- -------------------------------------------------------------------
class String
{
public:
    //! parse double values from string to vector of double
    static vdouble1d_t parse_doubles(const std::string &str);

    //! assuming that string consist of doubles return new string where doubles are rounded according to the precision
    static std::string round_doubles(const std::string &str, int precision);

    //! return true if text matches pattern with wildcards '*' and '?'
    static bool MatchPattern(const std::string &text, std::string wildcardPattern);

    //! split string into vector of string using delimeter
    static std::vector<std::string> Split(const std::string &text, const std::string &delimeter);
};


//- -------------------------------------------------------------------
//! @class StringUsageMap
//! @brief Definition of StringUsageMap to control how often string is used
//- -------------------------------------------------------------------
class StringUsageMap
{
public:
    typedef std::map<std::string, int> nstringmap_t;
    typedef nstringmap_t::iterator iterator_t;

    StringUsageMap(){}
    ~StringUsageMap(){}

    //! add string to the map to count number of times it was used
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
    int &operator[](std::string name) { return m_nstringmap[name]; }

    //! get current string
    std::string get_current() const { return m_current_string; }

private:
    std::string m_current_string;
    nstringmap_t m_nstringmap;
};


//- -------------------------------------------------------------------
//! @class FileSystem
//! @brief different utilities to deal with file system
//- -------------------------------------------------------------------
class FileSystem
{
public:
    //! return path to the current (working) directory
    static std::string GetWorkingPath();

    //! return path to BornAgain home directory
    static std::string GetHomePath();

    //! set relative path, which is the path from working directory to executable module. The value is known only from argv[0] and should be set from outside
    static void SetRelativePath(const std::string &path) { m_relative_path = path; }

    //! return file extension
    static std::string GetFileExtension(const std::string &name);

    //! return true if name contains *.gz extension
    static bool isGZipped(const std::string &name);

    //! return file extension after stripping '.gz' if any
    static std::string GetFileMainExtension(const std::string &name);
private:
    static std::string m_relative_path; //!< it's value of argv[0], i.e. the path from working directory to executable module
};


//- -------------------------------------------------------------------
//! @brief adjust length of the string
//- -------------------------------------------------------------------
inline std::string AdjustStringLength(std::string name, int length)
{
    std::string newstring = name;
    newstring.resize(length,' ');
    return newstring;
}


/* ************************************************************************* */
// unordered map of values
/* ************************************************************************* */
template<class Key, class Object >
class UnorderedMap
{
public:
    typedef boost::unordered_map<Key, Object > container_t;
    typedef typename container_t::iterator iterator;
    typedef typename container_t::const_iterator const_iterator;

    UnorderedMap() {}
    virtual ~UnorderedMap(){}

    //UnorderedMap *clone() { return new UnorderedMap(m_value_map); }

    const_iterator begin() { return m_value_map.begin(); }
    const_iterator end() { return m_value_map.end(); }
    const Object &find(const Key &key) const
    {
        const_iterator pos = m_value_map.find(key);
        if(pos != m_value_map.end() ) {
            return (*pos).second;
        } else {
            throw RuntimeErrorException("UnorderedMap::find() -> Error! Can't find the object");
        }
    }

    size_t size() { return m_value_map.size(); }
    Object & operator[] (const Key &key) { return m_value_map[key]; }

private:
    UnorderedMap &operator=(const UnorderedMap &);

    container_t m_value_map;
};

}

#endif // UTILS_H
