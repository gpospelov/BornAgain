// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/ParameterPool.h
//! @brief     Defines class ParameterPool.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef PARAMETERPOOL_H
#define PARAMETERPOOL_H

#include "ICloneable.h"
#include "RealParameterWrapper.h"
#include <map>
#include <vector>

//! Holds a map of pointers to parameters (which must have different names).

class ParameterPool : public ICloneable
{
public:
    //! definition of parameter type and parameter container
    typedef RealParameterWrapper parameter_t;
    typedef std::map<std::string, parameter_t > parametermap_t;

    ParameterPool() : m_map() {}
    virtual ~ParameterPool() {}

    //! simple clone
    ParameterPool *clone() const;

    //! clone with adding preffix to every parameter key
    ParameterPool *cloneWithPrefix(const std::string &prefix) const;

    //! copy parameters of given pool to the external pool while adding prefix to local parameter keys
    void copyToExternalPool(const std::string &prefix, ParameterPool *external_pool) const;

    //! clear and delete parameter map
    void clear();

    //! return size of parameter container
    size_t size() const { return m_map.size(); }

    //! main method to register data address in the pool
    void registerParameter(const std::string &name, double *parpointer);

    //! add parameter to the pool
    bool addParameter(const std::string &name, parameter_t par);

    //! return parameter with given name
    parameter_t getParameter(const std::string &name) const;

    //! return vector of parameters which fit pattern
    std::vector<parameter_t > getMatchedParameters(const std::string &wildcards) const;

    //! set parameter value, return true in the case of success
    bool setParameterValue(const std::string &name, double value);

    //! set parameter value, return number of changed parameters
    int setMatchedParametersValue(const std::string &wildcards, double value);

    //! link first parameter to second parameter times a scale factor and return number of changed parameters
    //! note that the parameters to be linked should match:
    //! prefix/to_change --> prefix/source
    int fixRatioBetweenParameters(const std::string &to_change, const std::string &source, double ratio);

    //! print parameter pool
    friend std::ostream &operator<<(std::ostream &ostr, const ParameterPool &obj) { obj.print(ostr); return ostr; }

protected:
//    //! disabling assignment operator, hiding copy constructor
//    ParameterPool(const ParameterPool &other);
//    ParameterPool &operator=(const ParameterPool &);

    //! print parameter pool content
    virtual void print(std::ostream &ostr) const;

    parametermap_t m_map; //! map of parameters
};

#endif // PARAMETERPOOL_H
