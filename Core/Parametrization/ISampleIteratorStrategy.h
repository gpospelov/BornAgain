// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ISampleIteratorStrategy.h
//! @brief     Defines strategies for the class SampleTreeIterator.
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

class IteratorMemento;

class BA_CORE_API_ IterationStrategy
{
public:
    virtual ~IterationStrategy() {}

    virtual IterationStrategy* clone() const = 0;

    virtual IteratorMemento first(const INode* p_root) = 0;
    virtual void next(IteratorMemento& iterator_stack) const = 0;
    virtual bool isDone(IteratorMemento& iterator_stack) const = 0;
};

class BA_CORE_API_ PreorderStrategy : public IterationStrategy
{
public:
    PreorderStrategy();

    virtual PreorderStrategy* clone() const;

    virtual ~PreorderStrategy();
    virtual IteratorMemento first(const INode* p_root);
    virtual void next(IteratorMemento& iterator_stack) const;
    virtual bool isDone(IteratorMemento& iterator_stack) const;
};

class BA_CORE_API_ PostorderStrategy : public IterationStrategy
{
public:
    PostorderStrategy();

    virtual PostorderStrategy* clone() const;

    virtual ~PostorderStrategy();
    virtual IteratorMemento first(const INode* p_root);
    virtual void next(IteratorMemento& iterator_stack) const;
    virtual bool isDone(IteratorMemento& iterator_stack) const;
};

#endif // ISAMPLEITERATORSTRATEGY_H
