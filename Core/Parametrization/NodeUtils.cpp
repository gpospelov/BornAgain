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
#include "SampleTreeIterator.h"
#include "ISampleIteratorStrategy.h"
#include "RealParameter.h"
#include "ParameterPool.h"
#include "INode.h"
#include <functional>
#include <sstream>

namespace {

    // Returns string filled with '.'
    std::string s_indent(int depth) {
        const int multiplier = 4;
        return std::string(multiplier*depth, '.');
    }

    // Returns multiline string representing pool parameters of given node.
    std::string poolToMultiString(const INode &node, int depth) {
        std::ostringstream result;

        for(auto par : node.getParameterPool()->getParameters())
            result << s_indent(depth)
                   << "'" << par->getName() << "':" << par->getValue() << "\n";

        return result.str();
    }

    // Returns single line string representing pool parameters of given node.
    std::string poolToString(const INode &node) {
        std::ostringstream result;

        const std::vector<RealParameter*> pars = node.getParameterPool()->getParameters();
        if(pars.size())
            result << " (";

        size_t index(0);
        for(auto par : pars) {
            result << "'" << par->getName() << "':" << par->getValue();
            ++index;
            if(index!=pars.size())
                result << " ";
        }

        if(pars.size())
            result << ")";

        return result.str();
    }

    // Returns a string representing given node.
    std::string nodeString(const INode& node, int depth) {
        std::ostringstream result;
        //result << s_indent(depth) << node.getName() << "\n" << poolToMultiString(node, depth+1);
        result << s_indent(depth) << node.getName() << poolToString(node) << "\n";
        return result.str();
    }
}

std::string NodeUtils::nodeToString(const INode& node)
{
    std::ostringstream result;

    SampleTreeIterator<SampleIteratorPreorderStrategy> it(&node);
    it.first();
    while (!it.isDone()) {
        const INode *child = it.getCurrent();
        result << nodeString(*child, it.depth()-1);
        it.next();
    }

    return result.str();
}
