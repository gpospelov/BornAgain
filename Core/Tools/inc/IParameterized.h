// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Tools/IParameterized.h 
//! @brief     Defines class IParameterized.
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
    IParameterized();
    IParameterized(const std::string &name);
    IParameterized(const IParameterized &other);
    IParameterized &operator=(const IParameterized &other);
    virtual ~IParameterized() {}

    //! return pointer to the parameter pool
    ParameterPool *getParameterPool() { return &m_parameters; }

    //! create new parameter pool which contains all local parameter and  parameters of children
    virtual ParameterPool *createParameterTree() const;

    //! add parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const;

    virtual void printParameters() const;

    virtual bool areParametersChanged() { return m_status.isChanged(); }

    virtual void setParametersAreChanged() { m_status.setIsChanged(true); }

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool (to overload)
    virtual void init_parameters();

    ParameterPool m_parameters; //! parameter pool
    IChangeable m_status;
};

#endif /* IPARAMETERIZED_H_ */
