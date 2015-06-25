// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ICompositeIteratorStrategy.h
//! @brief     Defines and implements strategies for the class ICompositeIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISAMPLEITERATORSTRATEGY_H
#define ISAMPLEITERATORSTRATEGY_H

#include "ISample.h"
#include <list>


class IteratorMemento;

class BA_CORE_API_ ISampleIteratorStrategy
{
public:
    virtual ~ISampleIteratorStrategy() {}

    virtual ISampleIteratorStrategy *clone() const=0;

    virtual IteratorMemento first(const ISample *p_root)=0;
    virtual void next(IteratorMemento &iterator_stack) const=0;
    virtual bool isDone(IteratorMemento &iterator_stack) const=0;
};

class BA_CORE_API_ CompositeIteratorPreorderStrategy : public ISampleIteratorStrategy
{
public:
    CompositeIteratorPreorderStrategy();

    virtual CompositeIteratorPreorderStrategy *clone() const;

    virtual ~CompositeIteratorPreorderStrategy();
    virtual IteratorMemento first(const ISample *p_root);
    virtual void next(IteratorMemento &iterator_stack) const;
    virtual bool isDone(IteratorMemento &iterator_stack) const;
};

#endif // ISAMPLEITERATORSTRATEGY_H


