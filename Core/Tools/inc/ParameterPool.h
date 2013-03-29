// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/ParameterPool.h
//! @brief     Defines class ParameterPool.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
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

    //! Constructs an empty parameter pool.
    ParameterPool() : m_map() {}

    virtual ~ParameterPool() {}

    //! Returns a literal clone.
    ParameterPool *clone() const
    {
        ParameterPool *new_pool = new ParameterPool();
        new_pool->m_map = m_map;
        return new_pool;
    }

    //! Returns a clone with _prefix_ added to every parameter key.
    ParameterPool *cloneWithPrefix(const std::string& prefix) const;

    //! Copies parameters to _external_pool_, adding _prefix_ to every key.
    void copyToExternalPool(
        const std::string& prefix, ParameterPool *external_pool) const;

    //! Deletes parameter map.
    void clear() { m_map.clear(); }

    //! Returns size of parameter container.
    size_t size() const { return m_map.size(); }

    //! Registers a parameter with key _name_ and pointer-to-value _parpointer_.
    void registerParameter(const std::string& name, double *parpointer);

    //! Adds parameter to the pool
    bool addParameter(const std::string& name, parameter_t par);

    //! Returns parameter named _name_.
    parameter_t getParameter(const std::string& name) const;

    //! Returns vector of parameters which fit pattern
    std::vector<parameter_t > getMatchedParameters(
        const std::string& wildcards) const;

    //! Sets parameter value, return true in the case of success
    bool setParameterValue(const std::string& name, double value);

    //! Sets parameter value, return number of changed parameters
    int setMatchedParametersValue(const std::string& wildcards, double value);

    //! link first parameter to second parameter times a scale factor and return number of changed parameters

    //! note that the parameters to be linked should match:
    //! prefix/to_change --> prefix/source
    int fixRatioBetweenParameters(const std::string& to_change, const std::string& source, double ratio);

    friend std::ostream& operator<<(std::ostream& ostr,
                                    const ParameterPool& obj)
    { obj.print(ostr); return ostr; }

 protected:
    //! Prints parameter pool contents.
    virtual void print(std::ostream& ostr) const;

    //! Map of parameters.
    parametermap_t m_map;
};

#endif // PARAMETERPOOL_H
