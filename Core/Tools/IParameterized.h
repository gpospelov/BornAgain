// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/IParameterized.h
//! @brief     Declares class IParameterized.
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

class AttLimits;

//! @class IParameterized
//! @ingroup tools_internal
//! @brief Manage a local parameter pool, and a tree of child pools.

class BA_CORE_API_ IParameterized : public INamed
{
public:
    IParameterized() : m_parameters(this) {}
    IParameterized(const std::string &name) : INamed(name), m_parameters(this) {}
    IParameterized(const IParameterized &other) : INamed(other), m_parameters(this) {}
    IParameterized& operator=(const IParameterized &other);

    virtual ~IParameterized() {}

    //! Returns pointer to the parameter pool.
    const ParameterPool* getParameterPool() const;

    //! Creates new parameter pool, with all local parameters and those of its children.
    ParameterPool* createParameterTree();

    void printParameters(); // const;

    //! Register parameter address in the parameter pool
    void registerParameter(const std::string &name, double *parpointer,
                           const AttLimits &limits = AttLimits::limitless());

    //! Sets the value of the parameter with the given name.
    void setParameterValue(const std::string &name, double value);

    //! Clears the parameter pool.
    void clearParameterPool();

    friend std::ostream& operator<<(std::ostream& ostr, const IParameterized& m);

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

protected:
    //! Action to be taken in inherited class when a parameter has changed.
    virtual void onChange() { std::cerr << "DEBUG: IPar'ed::onChange\n"; }

    //! Prints a representation of this IParameterized object to the given output stream.
    //! default implementation prints "IParameterized:" and the parameter pool
    virtual void print(std::ostream& ostr) const;

    //! Registers class parameters in the parameter pool
    //! Needs to be implemented by subclasses.
    virtual void init_parameters();

    ParameterPool m_parameters; //!< parameter pool
    friend ParameterPool;
};

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

inline const ParameterPool* IParameterized::getParameterPool() const
{
    return &m_parameters;
}

inline void IParameterized::registerParameter(const std::string &name, double *parpointer,
                                              const AttLimits &limits)
{
    m_parameters.registerParameter(name, parpointer, limits);
}

inline void IParameterized::clearParameterPool()
{
    m_parameters.clear();
}

inline std::ostream& operator<<(std::ostream &ostr, const IParameterized &m)
{
    m.print(ostr);
    return ostr;
}

#endif /* IPARAMETERIZED_H_ */
