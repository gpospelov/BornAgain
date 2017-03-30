// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/INodeVisitor.cpp
//! @brief     Implements class INodeVisitor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ISampleIteratorStrategy.h"
#include "NodeIterator.h"

void VisitSampleTreePreorder(const INode& node, INodeVisitor& visitor)
{
    NodeIterator<SampleIteratorPreorderStrategy> it(&node);
    it.first();
    while (!it.isDone()) {
        visitor.setDepth(it.depth());
        const INode *child = it.getCurrent();
        child->accept(&visitor);
        it.next();
    }
}

void VisitSampleTreePostorder(const INode& node, INodeVisitor& visitor)
{
    NodeIterator<SampleIteratorPostorderStrategy> it(&node);
    it.first();
    while (!it.isDone()) {
        visitor.setDepth(it.depth());
        const INode *child = it.getCurrent();
        child->accept(&visitor);
        it.next();
    }
}
