// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IParameterized.h
//! @brief     Defines class IParameterized.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef IPARAMETERIZED_H_
#define IPARAMETERIZED_H_

#include "INamed.h"
#include "IChangeable.h"
#include "ParameterPool.h"

class IParameterized : public INamed
{
  public:
    IParameterized()
        : m_parameters(), m_status() {}
    IParameterized(const std::string &name) 
        : INamed(name), m_parameters(), m_status() {}
    IParameterized(const IParameterized &other)
        : INamed(other), m_parameters(), m_status() {}
    IParameterized &operator=(const IParameterized &other);
    virtual ~IParameterized() {}

    //! Return pointer to the parameter pool.
    ParameterPool *getParameterPool() { return &m_parameters; }

    //! Create new parameter pool, with all local parameter and parameters of children
    virtual ParameterPool *createParameterTree() const;

    //! Add parameters from local pool to external pool and call recursion over direct children.
    virtual std::string addParametersToExternalPool(
        std::string path,
        ParameterPool *external_pool,
        int copy_number=-1) const;

    virtual void printParameters() const;

    virtual bool areParametersChanged() { return m_status.isChanged(); }

    virtual void setParametersAreChanged() { m_status.setIsChanged(true); }

protected:
    //! Throw non-implemented exception (needed for Python).
    virtual void init_parameters();

    ParameterPool m_parameters; //!< parameter pool
    IChangeable m_status;
};

#endif /* IPARAMETERIZED_H_ */
