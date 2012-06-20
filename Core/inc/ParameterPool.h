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


//- -------------------------------------------------------------------
//! @class ParameterPool
//! @brief Definition of ParameterPool to hold map of pointers to parameters
//! Names of parameters should be the different, otherwise exception is thrown
//- -------------------------------------------------------------------
class ParameterPool
{
public:
    //! definition of parameter type and parameter container
    typedef double * parameter_t;
    typedef std::map<std::string, parameter_t > parametermap_t;
    typedef parametermap_t::iterator iterator_t;

    ParameterPool();
    virtual ~ParameterPool();

    //! simple clone
    ParameterPool *clone();

    //! clone with adding preffix to every parameter key
    ParameterPool *cloneWithPrefix(std::string prefix);

    //! copy parameters of given pool to the external pool while adding prefix to local parameter keys
    void copyToExternalPool(std::string prefix, ParameterPool *external_pool);

    //! clear and delete parameter map
    void clear();

    //! return size of parameter container
    size_t size() const { return m_map ? m_map->size() : 0; }

    //! main method to register parameter in the container
    bool registerParameter(std::string name, parameter_t par);

    //! access to parameter container
    iterator_t begin() { return (m_map ? m_map->begin() : throw NullPointerException("ParameterPool::begin() -> Error! Non existing parameter map.")); }
    iterator_t end() { return (m_map ? m_map->end() : throw NullPointerException("ParameterPool::end() -> Error! Non existing parameter map.")); }

    //! print parameter pool
    friend std::ostream &operator<<(std::ostream &ostr, const ParameterPool &obj)
    {
        obj.print(ostr); return ostr;
    }

    //! print content of parameter pool on the screen
    void print();

protected:
    //! hiding copy constructors and assignment operators to allow only conscious cloning
    ParameterPool(const ParameterPool &other);
    ParameterPool &operator=(const ParameterPool &other);

    //! print parameter pool content
    virtual void print(std::ostream &ostr) const;

    parametermap_t *m_map; //! map of parameters
};

#endif // PARAMETERPOOL_H
