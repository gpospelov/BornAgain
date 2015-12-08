// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ISample.cpp
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
#include "SampleMaterialVisitor.h"
#include "ICompositeSample.h"
#include "Utils.h"
#include "SamplePrintVisitor.h"

ICompositeSample *ISample::getCompositeSample()
{
    return nullptr;
}

const ICompositeSample *ISample::getCompositeSample() const
{
    return nullptr;
}

ISample* ISample::cloneInvertB() const
{
    throw NotImplementedException(
        "ISample::cloneInvertB() -> Error! Method is not implemented");
}

DWBASimulation *ISample::createDWBASimulation() const
{
    return nullptr;
}

std::string ISample::addParametersToExternalPool(
        std::string path, ParameterPool *external_pool, int copy_number) const
{
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // go through direct children of this sample and copy their parameters recursively
    const ICompositeSample *p_sample = getCompositeSample();
    if( p_sample ) {
        // Here we need some default mechanism to handle cases with multiple children with
        // the same name.
        // First run through all direct children and save their names
        Utils::StringUsageMap strUsageMap;
        for(size_t i=0; i<p_sample->size(); ++i) {
            strUsageMap.add( new_path + (*p_sample)[i]->getName() ); // saving child names
        }
        // Now run through the direct children again and assign a copy number for
        // all children with the same name
        Utils::StringUsageMap strUsageMap2;
        for(size_t i=0; i<p_sample->size(); ++i) {
            std::string child_name = new_path + (*p_sample)[i]->getName();
            strUsageMap2.add(child_name);
            // Copy number starts from 0:
            int ncopy = strUsageMap2[child_name]-1;

            // If the child is the only one with that name, we do not want any copy number:
            if(strUsageMap[child_name] == 1) ncopy = -1;

            (*p_sample)[i]->addParametersToExternalPool(new_path, external_pool, ncopy);
        }
    }
    return new_path;
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
