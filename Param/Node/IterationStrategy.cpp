// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Node/IterationStrategy.cpp
//! @brief     Implements class IterationStrategy and children.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Param/Node/IterationStrategy.h"
#include "Base/Utils/Assert.h"
#include "Param/Node/NodeIterator.h"

PreorderStrategy::PreorderStrategy() = default;

PreorderStrategy* PreorderStrategy::clone() const
{
    return new PreorderStrategy();
}

IteratorMemento PreorderStrategy::first(const INode* p_root)
{
    IteratorMemento iterator_stack;
    iterator_stack.push_state(IteratorState(p_root));
    return iterator_stack;
}

void PreorderStrategy::next(IteratorMemento& iterator_stack) const
{
    const INode* node = iterator_stack.getCurrent();
    ASSERT(node);
    std::vector<const INode*> children = node->getChildren();
    if (children.size() > 0) {
        iterator_stack.push_state(IteratorState(children));
        return;
    }
    iterator_stack.next();
    while (!iterator_stack.empty() && iterator_stack.get_state().isEnd()) {
        iterator_stack.pop_state();
        if (!iterator_stack.empty())
            iterator_stack.next();
    }
}

bool PreorderStrategy::isDone(IteratorMemento& iterator_stack) const
{
    return iterator_stack.empty();
}
