// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/ISample.cpp
//! @brief     Implements class ISample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ISample.h"
#include "Exceptions.h"
#include "ParameterPool.h"
#include "Exceptions.h"
#include <algorithm>
#include <sstream>

ISample* ISample::cloneInvertB() const
{
    throw Exceptions::NotImplementedException(
        "ISample::cloneInvertB() -> Error! Method is not implemented");
}

std::vector<const HomogeneousMaterial*> ISample::containedMaterials() const
{
    std::vector<const HomogeneousMaterial*> result;
    if( const HomogeneousMaterial* p_material = material() )
        result.push_back( p_material );
    if( const HomogeneousMaterial* p_material = ambientMaterial() )
        result.push_back( p_material );
    for(auto child: getChildren() ) {
        if(const ISample* sample = dynamic_cast<const ISample *>(child)) {
            for( const HomogeneousMaterial* p_material: sample->containedMaterials() )
                result.push_back( p_material );
        }
    }
    return result;
}
