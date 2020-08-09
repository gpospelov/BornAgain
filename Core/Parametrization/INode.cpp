// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/INode.cpp
//! @brief     Implements class INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Parametrization/INode.h"
#include "Core/Basics/Assert.h"
#include "Core/Parametrization/IterationStrategy.h"
#include "Core/Parametrization/NodeIterator.h"
#include "Core/Parametrization/NodeUtils.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include <algorithm>
#include <exception>

INode::INode(const INode* parent, const std::vector<const char*>& PName,
             const std::vector<const char*>& PUnit, const std::vector<double>& PMin,
             const std::vector<double>& PMax, const std::vector<double>& PDefault,
             const std::vector<double>& P)
    : m_parent(parent), m_NP(PName.size())
{
    ASSERT(PUnit.size() == m_NP);
    ASSERT(PMin.size() <= m_NP);
    ASSERT(PMax.size() <= m_NP);
    ASSERT(PDefault.size() <= m_NP);
    if (P.size() > m_NP)
        throw std::runtime_error("Too many parameter values supplied to node constructor");
    if (P.size() < m_NP && PDefault.size() < m_NP)
        throw std::runtime_error("Not enough parameter values supplied to node constructor");
    m_P.resize(m_NP);

    for (size_t i = 0; i < m_NP; ++i) {
        m_P[i] = i < P.size() ? P[i] : PDefault[i];

        auto& reg = registerParameter(PName[i], &m_P[i]);
        reg.setUnit(PUnit[i]);
        const double pmi = i < PMin.size() ? PMin[i] : -INF;
        const double pma = i < PMax.size() ? PMax[i] : +INF;
        if (pmi == -INF) {
            ASSERT(pma == +INF);
            // nothing to do
        } else if (pma == +INF) {
            ASSERT(pmi == 0);
            reg.setNonnegative();
        } else {
            reg.setLimited(pmi, pma);
        }
    }
}

std::string INode::treeToString() const
{
    return NodeUtils::nodeToString(*this);
}

void INode::registerChild(INode* node)
{
    ASSERT(node);
    node->setParent(this);
}

std::vector<const INode*> INode::getChildren() const
{
    return {};
}

void INode::setParent(const INode* newParent)
{
    m_parent = newParent;
}

const INode* INode::parent() const
{
    return m_parent;
}

INode* INode::parent()
{
    return const_cast<INode*>(m_parent);
}

int INode::copyNumber(const INode* node) const
{
    if (node->parent() != this)
        return -1;

    int result(-1), count(0);
    for (auto child : getChildren()) {

        if (child == nullptr)
            throw std::runtime_error("INode::copyNumber() -> Error. Nullptr as child.");

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

ParameterPool* INode::createParameterTree() const
{
    std::unique_ptr<ParameterPool> result(new ParameterPool);

    NodeIterator<PreorderStrategy> it(this);
    it.first();
    while (!it.isDone()) {
        const INode* child = it.getCurrent();
        const std::string path = NodeUtils::nodePath(*child, this->parent()) + "/";
        child->parameterPool()->copyToExternalPool(path, result.get());
        it.next();
    }

    return result.release();
}
