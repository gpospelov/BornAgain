// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ISample.h
//! @brief     Defines interface class ISample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISAMPLE_H
#define ISAMPLE_H

#include "IParameterized.h"
#include "ICloneable.h"
#include "ISampleVisitor.h"

class ICompositeSample;
class DWBASimulation;

//! @class ISample
//! @ingroup samples_internal
//! @brief Interface for objects related to scattering.

class BA_CORE_API_ ISample : public ICloneable, public IParameterized
{
public:
    //! Returns a clone of this ISample object.
    virtual ISample *clone() const=0;

    //! Returns a clone with inverted magnetic fields.
    virtual ISample *cloneInvertB() const;

    //! Calls the ISampleVisitor's visit method.
    virtual void accept(ISampleVisitor *p_visitor) const=0;

    //! Returns an ISimulation if DWBA is required.
    virtual DWBASimulation *createDWBASimulation() const;

    //! Outputs the tree of parameters generated from this ISample object and its descendants.
    virtual void printSampleTree();

    //! Indicates if this ISample object contains a material with magnetic properties.
    virtual bool containsMagneticMaterial() const;

    //! Returns a vector of children (const).
    //! Default implementation returns empty vector.
    virtual std::vector<const ISample*> getChildren() const;

    //! Returns number of children.
    //! Default implementation returns zero.
    virtual size_t size() const;
};

inline size_t ISample::size() const
{
    return 0;
}

#endif // ISAMPLE_H


