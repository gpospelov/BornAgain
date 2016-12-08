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
#include "StringUsageMap.h"
#include <algorithm>
#include <sstream>

ISample* ISample::cloneInvertB() const
{
    throw Exceptions::NotImplementedException(
        "ISample::cloneInvertB() -> Error! Method is not implemented");
}

std::vector<const IMaterial*> ISample::containedMaterials() const
{
    std::vector<const IMaterial*> result;
    if( const IMaterial* material = getMaterial() )
        result.push_back( material );
    if( const IMaterial* material = getAmbientMaterial() )
        result.push_back( material );
    for(auto child: getChildren() ) {
        if(const ISample *sample = dynamic_cast<const ISample *>(child)) {
            for( const IMaterial* material: sample->containedMaterials() )
                result.push_back( material );
        }
    }
    return result;
}
