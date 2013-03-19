// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ISample.h
//! @brief     Defines class ISample.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef ISAMPLE_H
#define ISAMPLE_H

#include "IParameterized.h"

class ICompositeSample;
class DWBASimulation;

//! Interface for objects related to scattering

class ISample : public IParameterized, public ICloneable
{
public:
    ISample() { }
    virtual ~ISample() { }

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
