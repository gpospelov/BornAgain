// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Sample/ISample.h
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

#include "ICloneable.h"
#include "IParameterized.h"
#include "ISampleVisitor.h"
#include <vector>

class IMaterial;
class ISampleVisitor;

//! Interface for sample components and properties related to scattering.
//! @ingroup samples_internal

//! Pure virtual base class of ICompositeSample, IFormFactor, IInterferenceFunction,
//! IRoughness, IRotation. So it is somewhat more abstract than the name "ISample" suggests.

class BA_CORE_API_ ISample : public ICloneable, public IParameterized
{
public:
    //! Returns a clone of this ISample object.
    virtual ISample* clone() const=0;

    //! Returns a clone with inverted magnetic fields.
    virtual ISample* cloneInvertB() const;

    //! Calls the ISampleVisitor's visit method.
    virtual void accept(ISampleVisitor* p_visitor) const=0;

    //! Returns textual representation of this and its descendants.
    virtual std::string to_str(int indent=0) const;

    //! Returns nullptr, unless overwritten to return a specific material.
    virtual const IMaterial* getMaterial() const { return nullptr; }

    //! Returns nullptr, unless overwritten to return a specific material.
    virtual const IMaterial* getAmbientMaterial() const { return nullptr; }

    //! Returns set of unique materials contained in this ISample.
    std::vector<const IMaterial*> containedMaterials() const;

    //! Indicates if this ISample object contains any material with magnetic properties.
    bool containsMagneticMaterial() const;

    //! Returns a vector of children.
    virtual std::vector<const ISample*> getChildren() const { return {}; }

    //! Returns number of children.
    virtual size_t size() const { return 0; }

    template<class T> std::vector<const T*> containedSubclass() const;
};

//! Returns vector of children of type T.
template<class T>
std::vector<const T*> ISample::containedSubclass() const
{
    std::vector<const T*> result;
    if( const T* t = dynamic_cast<const T*>(this) )
        result.push_back( t );
    for( const ISample* child: getChildren() )
        for( const T* t: child->containedSubclass<T>() )
            result.push_back( t );
    return result;
}

#endif // ISAMPLE_H
