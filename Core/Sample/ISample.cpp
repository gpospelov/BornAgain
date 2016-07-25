// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Sample/ISample.cpp
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
#include "IMaterial.h"

ISample* ISample::cloneInvertB() const
{
    throw Exceptions::NotImplementedException(
        "ISample::cloneInvertB() -> Error! Method is not implemented");
}

DWBASimulation* ISample::createDWBASimulation() const
{
    return nullptr;
}

std::string ISample::to_str(int indent) const
{
    std::stringstream ss;
    ss << std::string(4*indent, '.') << " " << getName() << " " << *getParameterPool() << "\n";
    for( const ISample* child: getChildren() )
        ss << child->to_str(indent+1);
    return ss.str();
}

std::vector<const IMaterial*> ISample::containedMaterials() const
{
    std::vector<const IMaterial*> result;
    if( const IMaterial* material = getMaterial() )
        result.push_back( material );
    if( const IMaterial* material = getAmbientMaterial() )
        result.push_back( material );
    for( const ISample* child: getChildren() )
        for( const IMaterial* material: child->containedMaterials() )
            result.push_back( material );
    return result;
}

bool ISample::containsMagneticMaterial() const
{
    if( const IMaterial* material = getMaterial() )
        if( material->isMagneticMaterial() )
            return true;
    if( const IMaterial* material = getAmbientMaterial() )
        if( material->isMagneticMaterial() )
            return true;
    for( const ISample* child: getChildren() )
        if( child->containsMagneticMaterial() )
            return true;
    return false;
}

std::vector<const ISample*> ISample::getChildren() const
{
    return std::vector<const ISample*> {};
}
