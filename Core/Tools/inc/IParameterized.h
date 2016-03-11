// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IParameterized.h
//! @brief     Defines class IParameterized.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IPARAMETERIZED_H_
#define IPARAMETERIZED_H_

#include "INamed.h"
#include "ParameterPool.h"
#include "ICloneable.h"
#include "IShareable.h"

class AttLimits;

//! @class IParameterized
//! @ingroup tools_internal
//! @brief Manage a local parameter pool, and a tree of child pools.
template <typename T>
class BA_CORE_API_ IParameterizedTemplate : public INamedTemplate<T>
{
public:
    IParameterizedTemplate() : m_parameters() {}
    IParameterizedTemplate(const std::string &name) : INamedTemplate<T>(name), m_parameters() {}
    IParameterizedTemplate(const IParameterizedTemplate &other) : INamedTemplate<T>(other), m_parameters() {}
    IParameterizedTemplate &operator=(const IParameterizedTemplate &other);

    virtual ~IParameterizedTemplate() {}

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

    template <typename S>
        friend std::ostream& operator<<(std::ostream& ostr, const IParameterizedTemplate<S>& m);

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

protected:
    //! Prints a representation of this IParameterizedTemplate object to the given output stream.
    //! default implementation prints "IParameterizedTemplate:" and the parameter pool
    virtual void print(std::ostream& ostr) const;

    //! Registers class parameters in the parameter pool
    //! Needs to be implemented by subclasses.
    virtual void init_parameters();

    ParameterPool m_parameters; //!< parameter pool
};

typedef IParameterizedTemplate<ICloneable> IParameterized;
typedef IParameterizedTemplate<IShareable> IParameterizedShared;

//! @class ParameterPattern
//! @ingroup tools_internal
//! @brief Helper class for constructing parameter patterns.

class BA_CORE_API_ ParameterPattern
{
public:
    ParameterPattern();
    ParameterPattern(std::string root_object);

    ParameterPattern& beginsWith(std::string start_type);
    ParameterPattern& add(std::string object_type);

    std::string toStdString() const;
private:
    std::string m_pattern;
};

template <typename T>
inline const ParameterPool *IParameterizedTemplate<T>::getParameterPool() const
{
    return& m_parameters;
}

template <typename T>
inline void IParameterizedTemplate<T>::registerParameter(const std::string &name, double *parpointer,
                                              const AttLimits &limits)
{
    m_parameters.registerParameter(name, parpointer, limits);
}

template <typename T>
inline void IParameterizedTemplate<T>::clearParameterPool()
{
    m_parameters.clear();
}

template <typename T>
inline std::ostream& operator<<(std::ostream &ostr, const IParameterizedTemplate<T> &m)
{
    m.print(ostr);
    return ostr;
}

#endif /* IPARAMETERIZED_H_ */


