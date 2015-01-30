// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IParameterized.h
//! @brief     Defines standard mix-in class IParameterized.
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
#include "IChangeable.h"
#include "ParameterPool.h"

//! @class IParameterized
//! @ingroup tools_internal
//! @brief Manage a "local" parameter pool, and a tree of children's pools.

class BA_CORE_API_ IParameterized : public INamed
{
public:
    IParameterized()
        : m_parameters(), m_status() {}
    IParameterized(const std::string& name)
        : INamed(name), m_parameters(), m_status() {}
    IParameterized(const IParameterized& other)
        : INamed(other), m_parameters(), m_status() {}
    IParameterized& operator=(const IParameterized& other);
    virtual ~IParameterized() {}

    //! Returns pointer to the parameter pool.
    const ParameterPool* getParameterPool() const { return& m_parameters; }

    //! Creates new parameter pool, with all local parameters
    //! and parameters of children
    virtual ParameterPool* createParameterTree() const;

    //! Adds parameters from local pool to external pool and
    //! call recursion over direct children.
    virtual std::string addParametersToExternalPool(
        std::string path,
        ParameterPool* external_pool,
        int copy_number=-1) const;

    virtual void printParameters() const;

    virtual bool areParametersChanged() { return m_status.isChanged(); }

    virtual void setParametersAreChanged() { m_status.setIsChanged(true); }

    //! main method to register data address in the pool
    virtual void registerParameter(const std::string &name, double *parpointer)
    { m_parameters.registerParameter(name, parpointer); }

    //! set parameter value, return true in the case of success
    virtual bool setParameterValue(const std::string &name, double value);

    //! clear parameter pool
    virtual void clearParameterPool() { m_parameters.clear(); }

    friend std::ostream& operator<<(std::ostream& ostr, const IParameterized& m)
    { m.print(ostr); return ostr; }

protected:
    virtual void print(std::ostream& ostr) const;
    //! registers class parameters in the parameter pool
    virtual void init_parameters();

    ParameterPool m_parameters; //!< parameter pool
    IChangeable m_status;
};

#endif /* IPARAMETERIZED_H_ */


