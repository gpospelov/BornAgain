// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Samples/ISample.cpp
//! @brief     Implements class ISample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleMaterialVisitor.h"
#include "SamplePrintVisitor.h"

ISample* ISample::cloneInvertB() const
{
    throw Exceptions::NotImplementedException(
        "ISample::cloneInvertB() -> Error! Method is not implemented");
}

DWBASimulation *ISample::createDWBASimulation() const
{
    return nullptr;
}

void ISample::printSampleTree()
{
    SamplePrintVisitor visitor;
    VisitSampleTreePreorder(*this, visitor);
}

bool ISample::containsMagneticMaterial() const
{
    SampleMaterialVisitor material_vis;
    VisitSampleTreePreorder(*this, material_vis);
    return material_vis.containsMagneticMaterial();
}

std::vector<const ISample *> ISample::getChildren() const
{
    return std::vector<const ISample*>{};
}
