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
#include "SamplePrintVisitor.h"

ISample* ISample::cloneInvertB() const
{
    throw Exceptions::NotImplementedException(
        "ISample::cloneInvertB() -> Error! Method is not implemented");
}

DWBASimulation* ISample::createDWBASimulation() const
{
    return nullptr;
}

std::string ISample::to_str(int indent)
{
    SamplePrintVisitor visitor;
    VisitSampleTreePreorder(*this, visitor);
    return visitor.to_str();
}

std::set<const IMaterial*> ISample::containedMaterials() const
{
    std::set<const IMaterial*> result;
    if( const IMaterial* material = getMaterial() )
        result.insert( material );
    if( const IMaterial* material = getAmbientMaterial() )
        result.insert( material );
    for( const ISample* child: getChildren() )
        for( const IMaterial* material: child->containedMaterials() )
            result.insert( material );
    return result;
}

bool ISample::containsMagneticMaterial() const
{
    for( const IMaterial* material: containedMaterials() )
        if ( material->isMagneticMaterial() )
            return true;
    return false;
}

std::vector<const ISample*> ISample::getChildren() const
{
    return std::vector<const ISample*> {};
}
