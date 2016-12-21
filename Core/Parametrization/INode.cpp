// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/INode.cpp
//! @brief     Implements class INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "INode.h"
#include "StringUsageMap.h"
#include "Exceptions.h"
#include "NodeUtils.h"
#include "SampleTreeIterator.h"
#include "ISampleIteratorStrategy.h"
#include "ParameterPool.h"
#include <algorithm>

INode::INode() : m_parent(nullptr)
{
}

std::string INode::to_str() const
{
    return NodeUtils::nodeToString(*this);
}

void INode::registerChild(INode *node)
{
    if(!node)
        throw Exceptions::NullPointerException("INode::registerChild -> Error. Null pointer.");
    node->setParent(this);
}

std::vector<const INode *> INode::getChildren() const
{
    return {};
}

std::string INode::addParametersToExternalPool(
    const std::string& path, ParameterPool* external_pool, int copy_number) const
{
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // We need a mechanism to handle cases with multiple children with the same name.
    // First run through all direct children and save their names
    StringUsageMap strUsageMap;
    for(auto child : getChildren())
        strUsageMap.add(new_path + child->getName()); // saving child names

    // Now run through the direct children again and assign a copy number for
    // all children with the same name
    StringUsageMap strUsageMap2;
    for(auto child : getChildren()) {
        std::string child_name = new_path + child->getName();
        strUsageMap2.add(child_name);
        // Copy number starts from 0:
        int ncopy = strUsageMap2[child_name] - 1;

        // If the child is the only one with that name, we do not want any copy number:
        if (strUsageMap[child_name] == 1)
            ncopy = -1;

        child->addParametersToExternalPool(new_path, external_pool, ncopy);
    }
    return new_path;
}

void INode::setParent(const INode* parent)
{
    m_parent = parent;
}

const INode* INode::parent() const
{
    return m_parent;
}

int INode::copyNumber(const INode* node) const
{
    if(node->parent() != this)
        return -1;

    int result(-1), count(0);
    for (auto child : getChildren()) {
        if (child == node)
            result = count;

        if (child->getName() == node->getName())
            ++count;
    }

    return count > 1 ? result : -1;
}

std::string INode::displayName() const
{
    std::string result = getName();
    if (m_parent) {
        int index = m_parent->copyNumber(this);
        if (index >= 0)
            result = result + std::to_string(index);
    }
    return result;
}

ParameterPool* INode::createParameterTree()
{
    auto P_new_pool = new ParameterPool(getName(), std::bind(&IParameterized::onChange, this) );
    addParametersToExternalPool("/", P_new_pool);
    return P_new_pool;
//    return createParameterTreeNew();
}

ParameterPool* INode::createParameterTreeNew()
{
    std::unique_ptr<ParameterPool> result(
                new ParameterPool(getName(), std::bind(&IParameterized::onChange, this) ));

    SampleTreeIterator<SampleIteratorPreorderStrategy> it(this);
    it.first();
    while (!it.isDone()) {
        const INode *child = it.getCurrent();
        const std::string path = NodeUtils::nodePath(*child, this->parent()) + "/";
        child->getParameterPool()->copyToExternalPool(path, result.get());
        it.next();
    }

    return result.release();
}
