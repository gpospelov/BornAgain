// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/ISampleVisitor.cpp
//! @brief     Implements class ISampleVisitor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ISampleIteratorStrategy.h"
#include "Exceptions.h"
#include "SampleTreeIterator.h"

void VisitSampleTreePreorder(const ISample& sample, ISampleVisitor& visitor)
{
    SampleTreeIterator<SampleIteratorPreorderStrategy> it(&sample);
    it.first();
    while (!it.isDone()) {
        visitor.setDepth(it.depth());
        const INode *child = it.getCurrent();
        child->accept(&visitor);
        it.next();
    }
}

void VisitSampleTreePostorder(const ISample& sample, ISampleVisitor& visitor)
{
    SampleTreeIterator<SampleIteratorPostorderStrategy> it(&sample);
    it.first();
    while (!it.isDone()) {
        visitor.setDepth(it.depth());
        const INode *child = it.getCurrent();
        child->accept(&visitor);
        it.next();
    }
}
