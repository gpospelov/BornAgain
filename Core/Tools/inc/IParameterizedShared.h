// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IParameterizedShared.h
//! @brief     Defines class IParameterizedShared.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IPARAMETERIZEDSHARED_H_
#define IPARAMETERIZEDSHARED_H_

#include "INamedShared.h"
#include "ParameterPool.h"
#include "IParameterized.h"

class AttLimits;

//! @class IParameterized
//! @ingroup tools_internal
//! @brief Manage a local parameter pool, and a tree of child pools.

class BA_CORE_API_ IParameterizedShared : public INamedShared
{
public:
    IParameterizedShared() : m_parameters() {}
    IParameterizedShared(const std::string &name) : INamedShared(name), m_parameters() {}
    IParameterizedShared(const IParameterizedShared &other) : INamedShared(other), m_parameters() {}
    IParameterizedShared &operator=(const IParameterizedShared &other);

    virtual ~IParameterizedShared() {}

    //! Returns pointer to the parameter pool.
    const ParameterPool* getParameterPool() const;

    //! Creates new parameter pool, with all local parameters and those of its children.
    ParameterPool* createParameterTree() const;

    void printParameters() const;

    //! Register parameter address in the parameter pool
    void registerParameter(const std::string &name, double *parpointer,
                           const AttLimits &limits = AttLimits::limitless());

    //! Sets the value of the parameter with the given name; returns true in the case of success.
    bool setParameterValue(const std::string &name, double value);

    //! Clears the parameter pool.
    void clearParameterPool();

    friend std::ostream& operator<<(std::ostream& ostr, const IParameterizedShared& m);

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

protected:
    //! Prints a representation of this IParameterizedShared object to the given output stream.
    //! default implementation prints "IParameterizedShared:" and the parameter pool
    virtual void print(std::ostream& ostr) const;

    //! Registers class parameters in the parameter pool
    //! Needs to be implemented by subclasses.
    virtual void init_parameters();

    ParameterPool m_parameters; //!< parameter pool
};

//! @class ParameterPattern
//! @ingroup tools_internal
//! @brief Helper class for constructing parameter patterns.


inline const ParameterPool *IParameterizedShared::getParameterPool() const
{
    return& m_parameters;
}

inline void IParameterizedShared::registerParameter(const std::string &name, double *parpointer,
                                              const AttLimits &limits)
{
    m_parameters.registerParameter(name, parpointer, limits);
}

inline void IParameterizedShared::clearParameterPool()
{
    m_parameters.clear();
}

inline std::ostream& operator<<(std::ostream &ostr, const IParameterizedShared &m)
{
    m.print(ostr);
    return ostr;
}

#endif /* IPARAMETERIZED_H_ */


