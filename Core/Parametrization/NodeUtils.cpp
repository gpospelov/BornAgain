// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/NodeUtils.cpp
//! @brief     Implements collection of utility functions for INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "NodeUtils.h"
#include "NodeIterator.h"
#include "IterationStrategy.h"
#include "RealParameter.h"
#include "ParameterPool.h"
#include "INode.h"
#include "Exceptions.h"
#include <functional>
#include <algorithm>
#include <iterator>
#include <sstream>

namespace {

    // Returns string filled with '.'
    std::string s_indent(int depth) {
        const int multiplier = 4;
        return std::string(multiplier*depth, '.');
    }

    // Returns single line string representing pool parameters of given node.
    std::string poolToString(const INode &node) {
        std::ostringstream result;

        const std::vector<RealParameter*> pars = node.parameterPool()->parameters();
        if (pars.empty())
            return {};

        result << " (";
        size_t index(0);
        for (auto par : pars) {
            result << "'" << par->getName() << "':" << par->getValue();
            ++index;
            if (index!=pars.size())
                result << " ";
        }
        result << ")";

        return result.str();
    }

    // Returns a string representing given node.
    std::string nodeString(const INode& node, int depth) {
        std::ostringstream result;
        result << s_indent(depth) << node.displayName() << poolToString(node) << "\n";
        return result.str();
    }
}

std::string NodeUtils::nodeToString(const INode& node)
{
    std::ostringstream result;

    NodeIterator<PreorderStrategy> it(&node);
    it.first();
    while (!it.isDone()) {
        const INode *child = it.getCurrent();
        result << nodeString(*child, it.depth()-1);
        it.next();
    }

    return result.str();
}

std::string NodeUtils::nodePath(const INode& node, const INode* root)
{
    std::vector<std::string> pathElements;
    const INode* current = &node;
    while (current && current != root) {
        pathElements.push_back(current->displayName());
        pathElements.push_back("/");
        current = current->parent();
    }

    if (root != nullptr && current != root) {
        throw Exceptions::RuntimeErrorException("NodeUtils::nodePath() -> Error. Node doesn't "
                                                "belong to root's branch");
    }

    std::reverse(pathElements.begin(), pathElements.end());
    std::ostringstream result;
    std::copy(pathElements.begin(), pathElements.end(), std::ostream_iterator<std::string>(result));
    return result.str();
}
