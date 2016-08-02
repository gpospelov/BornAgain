// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/IParameterized.h
//! @brief     Declares class IParameterized.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IPARAMETERIZED_H
#define IPARAMETERIZED_H

#include "INamed.h" // inheriting from

class AttLimits;
class ParameterPool;
class RealParameter;

//! @class IParameterized
//! @ingroup tools_internal
//! @brief Manage a local parameter pool, and a tree of child pools.

class BA_CORE_API_ IParameterized : public INamed
{
public:
    IParameterized(const std::string& name="");
    IParameterized(const IParameterized& other);
    virtual ~IParameterized();

    //! Previously, copied name, but not parameters. Unused. Deleted to prevent misunderstandings.
    IParameterized operator=(const IParameterized& other) = delete;

    //! Returns pointer to the parameter pool.
    ParameterPool* getParameterPool() const { return m_pool; }

    //! Creates new parameter pool, with all local parameters and those of its children.
    ParameterPool* createParameterTree();

    void printParameters();

    void registerParameter(const std::string& name, double* parpointer);
    void registerParameter(const std::string& name, double* parpointer, const AttLimits& limits);

    void setParameterValue(const std::string& name, double value);

    RealParameter* getParameter(const std::string& name) const;

    friend std::ostream& operator<<(std::ostream& ostr, const IParameterized& m) {
        m.print(ostr);
        return ostr; }

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(
        std::string path, ParameterPool* external_pool, int copy_number=-1) const;

protected:
    //! Action to be taken in inherited class when a parameter has changed.
    virtual void onChange() {}

    //! Prints a representation of this IParameterized object to the given output stream.
    //! default implementation prints "IParameterized:" and the parameter pool
    virtual void print(std::ostream& ostr) const;

private:
    ParameterPool* m_pool; //!< parameter pool (kind of pointer-to-implementation)
};

#endif // IPARAMETERIZED_H
