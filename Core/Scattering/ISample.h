// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/ISample.h
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
#include "INode.h"
#include <vector>

class HomogeneousMaterial;

//! Pure virtual base class for sample components and properties related to scattering.
//! @ingroup samples_internal

class BA_CORE_API_ ISample : public ICloneable, public INode
{
public:
    //! Returns a clone of this ISample object.
    ISample* clone() const override=0;

    //! Returns nullptr, unless overwritten to return a specific material.
    virtual const HomogeneousMaterial* material() const { return nullptr; }

    //! Returns nullptr, unless overwritten to return a specific material.
    virtual const HomogeneousMaterial* ambientMaterial() const { return nullptr; }

    //! Returns set of unique materials contained in this ISample.
    std::vector<const HomogeneousMaterial*> containedMaterials() const;

    template<class T> std::vector<const T*> containedSubclass() const;
};

//! Returns vector of children of type T.
template<class T>
std::vector<const T*> ISample::containedSubclass() const
{
    std::vector<const T*> result;
    if( const T* t = dynamic_cast<const T*>(this) )
        result.push_back( t );
    for(auto child: getChildren() ) {
        if(const ISample *sample = dynamic_cast<const ISample *>(child)) {
            for( const T* t: sample->containedSubclass<T>() )
                result.push_back( t );
        }
    }
    return result;
}

#endif // ISAMPLE_H
