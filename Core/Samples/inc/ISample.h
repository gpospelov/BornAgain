#ifndef ISAMPLE_H
#define ISAMPLE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ISample.h
//! @brief  Definition of ISample class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "INamed.h"
#include "Exceptions.h"
#include "ParameterPool.h"


class ICompositeSample;

//- -------------------------------------------------------------------
//! @class ISample
//! @brief Definition of ISample which
//- -------------------------------------------------------------------
class ISample : public INamed
{
public:
    ISample();
    ISample(const ISample &other);
    ISample &operator=(const ISample &other);
    virtual ~ISample();

    //! return pointer to "this", if it is composite sample (to overload)
    virtual ICompositeSample *getCompositeSample() { return 0; }

    //! clone sample (to overload)
    virtual ISample *clone();

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool (to overload)
    virtual void init_parameters();

    //! (temporary for debugging) return sample Id
    long getId() const {return m_id; }

    //! return pointer to the parameter pool
    ParameterPool *getParameterPool() { return &m_parameters; }

    //! create new parameter pool which contains all local parameter and  parameters of children
    virtual ParameterPool *createParameterTree();

    //! same as above, demonstration of iterators instead of nested calls
    virtual ParameterPool *createParameterTreeTest();

    //! add parameters from local pool to external pool and call recursion over direct children
    virtual void addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1);

protected:
    long m_id; //! temporary debug variable to track id of instance
    static long m_id_last; //! temporary debug variable to track id of instance

    ParameterPool m_parameters; //! parameter pool
};

#endif // ISAMPLE_H
