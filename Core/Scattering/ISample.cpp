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

void ISample::registerChild(ISample* sample)
{
    if(!sample)
        throw Exceptions::NullPointerException(
            "ISample::registerChild -> Error. Null pointer.");
    m_samples.push_back(sample);
}

//! remove registered child from the container

void ISample::deregisterChild(ISample* sample)
{
    auto it = std::find(m_samples.begin(), m_samples.end(), sample);
    if (it != m_samples.end())
        m_samples.erase(it);
}

std::vector<const ISample*> ISample::getChildren() const
{
    std::vector<const ISample*> result;
    for (size_t i=0; i<m_samples.size(); ++i)
        result.push_back(m_samples[i]);
    return result;
}

std::string ISample::addParametersToExternalPool(
    const std::string& path, ParameterPool* external_pool, int copy_number) const
{
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // We need a mechanism to handle cases with multiple children with the same name.
    // First run through all direct children and save their names
    StringUsageMap strUsageMap;
    for (size_t i = 0; i < m_samples.size(); ++i)
        strUsageMap.add(new_path + m_samples[i]->getName()); // saving child names

    // Now run through the direct children again and assign a copy number for
    // all children with the same name
    StringUsageMap strUsageMap2;
    for (size_t i = 0; i < m_samples.size(); ++i) {
        std::string child_name = new_path + m_samples[i]->getName();
        strUsageMap2.add(child_name);
        // Copy number starts from 0:
        int ncopy = strUsageMap2[child_name] - 1;

        // If the child is the only one with that name, we do not want any copy number:
        if (strUsageMap[child_name] == 1)
            ncopy = -1;

        m_samples[i]->addParametersToExternalPool(new_path, external_pool, ncopy);
    }
    return new_path;
}
