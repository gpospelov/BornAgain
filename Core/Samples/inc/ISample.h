// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ISample.h
//! @brief     Defines interface class ISample.
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
#include "ICloneable.h"
#include "ISampleVisitor.h"

class ICompositeSample;
class DWBASimulation;

//! Interface for objects related to scattering

class ISample : public IParameterized, public ICloneable
{
 public:
    ISample() { setName("ISample"); }
    virtual ~ISample() {}

    //! Returns pointer to "this", if it is composite sample (to overload).
    virtual const ICompositeSample *getCompositeSample() const { return 0; }

    virtual ISample *clone() const;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *p_visitor)=0;

    //! Returns an ISimulation if DWBA is required.
    virtual DWBASimulation *createDWBASimulation() const { return 0; }

    //! Adds params from local to external pool, recurses over direct children.
    virtual std::string addParametersToExternalPool(
        std::string path,
        ParameterPool *external_pool,
        int copy_number=-1) const;

    void print_structure();

    friend std::ostream& operator<<(std::ostream& ostr, const ISample& m)
    { m.print(ostr); return ostr; }

 protected:
    virtual void print(std::ostream& ostr) const;
};

#endif // ISAMPLE_H


