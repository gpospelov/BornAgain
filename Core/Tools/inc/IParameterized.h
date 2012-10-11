#ifndef IPARAMETERIZED_H_
#define IPARAMETERIZED_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IParameterized.h
//! @brief  Definition of IParameterized interface
//! @author Scientific Computing Group at FRM II
//! @date   Oct 10, 2012

#include "INamed.h"
#include "ParameterPool.h"


class IParameterized : public INamed
{
public:
    IParameterized();
    IParameterized(const IParameterized &other);
    IParameterized &operator=(const IParameterized &other);
    virtual ~IParameterized() {};

    //! return pointer to the parameter pool
    ParameterPool *getParameterPool() { return &m_parameters; }

    //! create new parameter pool which contains all local parameter and  parameters of children
    virtual ParameterPool *createParameterTree() const;

    //! add parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const;

    void printParameters() const;
protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool (to overload)
    virtual void init_parameters();

    ParameterPool m_parameters; //! parameter pool

};

#endif /* IPARAMETERIZED_H_ */
