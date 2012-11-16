#ifndef PARAMETERPOOL_H
#define PARAMETERPOOL_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ParameterPool.h
//! @brief  Definition of Layer class
//! @author Scientific Computing Group at FRM II
//! @date   18.06.2012

#include "Exceptions.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>


//- -------------------------------------------------------------------
//! @class ParameterPool
//! @brief Definition of ParameterPool to hold map of pointers to parameters
//! Names of parameters should be the different, otherwise exception is thrown
//- -------------------------------------------------------------------
class ParameterPool
{
public:
    class RealPar {
    public:
        explicit RealPar(double *par) : m_data(par) {}
        void setValue(double value) { checkNull(); *m_data = value; }
        double getValue() const { checkNull(); return *m_data; }
        bool isNull() { return (m_data ? false : true); }
        void checkNull() const { if(!m_data) throw NullPointerException("ParameterPool::RealPar::getValue() -> Attempt to access uninitialised pointer."); }
        friend std::ostream &operator<<(std::ostream &ostr, const RealPar &p) { ostr << p.m_data; return ostr; }
    private:
        double *m_data;
    };

    //! definition of parameter type and parameter container
    typedef std::map<std::string, RealPar > parametermap_t;

    ParameterPool();
    virtual ~ParameterPool();

    //! simple clone
    ParameterPool *clone();

    //! clone with adding preffix to every parameter key
    ParameterPool *cloneWithPrefix(const std::string &prefix);

    //! copy parameters of given pool to the external pool while adding prefix to local parameter keys
    void copyToExternalPool(const std::string &prefix, ParameterPool *external_pool) const;

    //! clear and delete parameter map
    void clear();

    //! return size of parameter container
    size_t size() const { return m_map.size(); }

    //! main method to register data address in the pool
    bool registerParameter(const std::string &name, double *parpointer);

    //! add parameter to the pool
    bool addParameter(const std::string &name, RealPar par);

//    //! access to parameter container
//    iterator_t begin() { return m_map.begin(); }
//    iterator_t end() { return m_map.end(); }

//    //! const access to parameter container
//    const_iterator_t begin() const { return m_map.begin(); }
//    const_iterator_t end() const { return m_map.end(); }

    //! return parameter with given name
    RealPar getParameter(const std::string &name) const;

    //! return vector of parameters which fit pattern
    std::vector<RealPar > getMatchedParameters(const std::string &wildcards) const;

    //! set parameter value, return true in the case of success
    bool setParameterValue(const std::string &name, double value);

    //! set parameter value, return number of changed parameters
    int setMatchedParametersValue(const std::string &wildcards, double value);

    //! print parameter pool
    friend std::ostream &operator<<(std::ostream &ostr, const ParameterPool &obj)
    {
        obj.print(ostr); return ostr;
    }

protected:
    //! disabled copy constructors and assignment operator
    ParameterPool(const ParameterPool &);
    ParameterPool &operator=(const ParameterPool &);

    //! print parameter pool content
    virtual void print(std::ostream &ostr) const;

    parametermap_t m_map; //! map of parameters
};

#endif // PARAMETERPOOL_H
