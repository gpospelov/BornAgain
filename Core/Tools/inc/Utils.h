#ifndef UTILS_H
#define UTILS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Utils.h
//! @brief  Definition of several helper classes
//! @author Scientific Computing Group at FRM II
//! @date   19.06.2012

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>


namespace Utils {


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
    std::string get_current() { return m_current_string; }

private:
    std::string m_current_string;
    nstringmap_t m_nstringmap;
};



//- -------------------------------------------------------------------
//! @class StringMatchText
//! @brief Definition of StringMatchText class to perform simple '*' and '?'
//! wilcard matching
//- -------------------------------------------------------------------
class StringMatchText
{
public:
    static bool WildcardPattern(const std::string &text, std::string wildcardPattern);
};


////- -------------------------------------------------------------------
////! @class StringSampleHelper
////! @brief Definition of StringSampleHelper to build the string representing
////! path in ISample parameter tree
////!
////! See example in ICompositeSample::getParameterTree()
////- -------------------------------------------------------------------
//class StringSampleHelper
//{
//public:
//    typedef std::vector<StringUsageMap > nstringmap_t;
//    typedef nstringmap_t::iterator iterator_t;

//    StringSampleHelper(){}
//    ~StringSampleHelper(){}

//    void add(std::string name, int dirlevel) {

//        while(dirlevel > (int)m_stringstack.size()-1) {
//            m_stringstack.push_back(StringUsageMap());
//        }

//        while(dirlevel < (int)m_stringstack.size()-1) {
//            m_stringstack.pop_back();
//        }

//        m_stringstack[dirlevel].add(name);
//    }

//    //! return current path in parameter tree, like /multilayer/interface3/roughness/sigma
//    std::string get_path()
//    {
//        std::string result;
//        for(size_t i_level=0; i_level<m_stringstack.size(); i_level++) {
//            std::string currentLevelName = m_stringstack[i_level].get_current();
//            StringUsageMap &strUsageMap = m_stringstack[i_level];
//            // if such name has been already used on that level, built the level name using index number
//            std::ostringstream os;
//            int nOfUsage = strUsageMap[currentLevelName];
//            result += std::string("/") + currentLevelName;
//            if(nOfUsage != 1) {
//                os<<nOfUsage;
//                result += os.str();
//            }
//        }
//        return result;
//    }

//    iterator_t begin() { return m_stringstack.begin(); }
//    iterator_t end() { return m_stringstack.end(); }
//    size_t size() const { return m_stringstack.size(); }
//    StringUsageMap &operator[](size_t i) { return m_stringstack[i]; }
//    StringUsageMap const &operator[](size_t i) const { return m_stringstack[i]; }

//protected:
//    std::vector<StringUsageMap > m_stringstack;
//};


}


#endif // UTILS_H


