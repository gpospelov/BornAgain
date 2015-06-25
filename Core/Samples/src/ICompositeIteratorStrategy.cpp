// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ICompositeIteratorStrategy.cpp
//! @brief     Implements class ICompositeIteratorStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ICompositeIteratorStrategy.h"
#include "ICompositeIterator.h"


CompositeIteratorPreorderStrategy::CompositeIteratorPreorderStrategy()
{
}

CompositeIteratorPreorderStrategy *CompositeIteratorPreorderStrategy::clone() const
{
    return new CompositeIteratorPreorderStrategy();
}

CompositeIteratorPreorderStrategy::~CompositeIteratorPreorderStrategy()
{
}

IteratorMemento CompositeIteratorPreorderStrategy::first(const ISample *p_root)
{
    IteratorMemento iterator_stack;
    iterator_stack.push_state( IteratorState(p_root) );
    return iterator_stack;
}

void CompositeIteratorPreorderStrategy::next(IteratorMemento &iterator_stack) const
{
    const ISample *p_sample = iterator_stack.getCurrent();
    if( !p_sample ) {
        throw NullPointerException("CompositeIteratorPreorderStrategy::next(): "
                                   "Error! Null object in the tree of objects");
    }
    if ( p_sample->getCompositeSample() ) {
        const ICompositeSample* p_composite = dynamic_cast<const ICompositeSample*>(p_sample);
        if(p_composite->size()>0 ) {
            iterator_stack.push_state( IteratorState(p_composite->getChildren()) );
            return;
        }
    }

    iterator_stack.next();

    while ( !iterator_stack.empty() && iterator_stack.get_state().isEnd() )
    {
        iterator_stack.pop_state();
        if ( !iterator_stack.empty() ) iterator_stack.next();
    }
}

bool CompositeIteratorPreorderStrategy::isDone(IteratorMemento &iterator_stack) const
{
    return iterator_stack.empty();
}
