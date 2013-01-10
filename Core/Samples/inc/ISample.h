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

#include "IParameterized.h"
#include "ICloneable.h"

class ICompositeSample;
class DWBASimulation;

//- -------------------------------------------------------------------
//! @class ISample
//! @brief Definition of ISample interface for objects related to scattering
//- -------------------------------------------------------------------
class ISample : public IParameterized, public ICloneable
{
public:
    ISample() { }
    virtual ~ISample() { }
//    ISample(const ISample &other);
//    ISample &operator=(const ISample &other);

    //! return pointer to "this", if it is composite sample (to overload)
    virtual ICompositeSample *getCompositeSample() { return 0; }
    virtual const ICompositeSample *getCompositeSample() const { return 0; }

    //! clone sample (to overload)
    virtual ISample *clone() const;

    //! check if this sample (or one of its subsamples) contains elements requiring DWBA corrections and return an ISimulation to calculate this
    virtual DWBASimulation *createDWBASimulation() const { return 0; }

    //! stream output
    friend std::ostream &operator<<(std::ostream &ostr, const ISample &m) { m.print(ostr); return ostr; }

    //! walk through composite sample and print content
    virtual void print_structure();

    //! add parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const;

protected:
    //! print in the output stream
    virtual void print(std::ostream &ostr) const { ostr << getName() << " " << this << " " << m_parameters; }
};

#endif // ISAMPLE_H
