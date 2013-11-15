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

class BA_CORE_API_ ISample : public ICloneable, public IParameterized
{
public:
    ISample() { setName("ISample"); }
    virtual ~ISample() {}

    //! Returns pointer to "this", if it is composite sample (to overload).
    virtual const ICompositeSample *getCompositeSample() const { return 0; }

    virtual ISample *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual ISample *cloneInvertB() const;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *p_visitor) const = 0;

    //! Returns an ISimulation if DWBA is required.
    virtual DWBASimulation *createDWBASimulation() const { return 0; }

    //! Adds params from local to external pool, recurses over direct children.
    virtual std::string addParametersToExternalPool(
        std::string path,
        ParameterPool *external_pool,
        int copy_number=-1) const;

    virtual void printSampleTree();

    friend std::ostream& operator<<(std::ostream& ostr, const ISample& m)
    { m.print(ostr); return ostr; }

    bool containsMagneticMaterial() const;

protected:
    virtual void print(std::ostream& ostr) const;
};

#endif // ISAMPLE_H


