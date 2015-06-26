// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/SampleTreeIterator.h
//! @brief     Defines and classes IteratorState, IteratorMemento and SampleTreeIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISAMPLETREEITERATOR_H
#define ISAMPLETREEITERATOR_H

#include "ISample.h"
#include "ICompositeSample.h"
#include <iostream>
#include <stack>
#include <list>
#include <boost/scoped_ptr.hpp>

class ISampleIteratorStrategy;

//! @class IteratorState
//! @ingroup samples_internal
//! @brief Holds state of iterator at single level for SampleTreeIterator

class IteratorState
{
public:
    typedef typename std::list<const ISample*>::const_iterator const_iterator_t;

    IteratorState(const ISample* single_element);
    IteratorState(std::vector<const ISample*> samples);

    virtual ~IteratorState() {}

    const ISample* getCurrent() const { return m_samples[m_position]; }
    bool isEnd() const { return m_position>=m_samples.size(); }
    void next() { ++m_position; }

    friend std::ostream& operator<<(std::ostream& output_stream, IteratorState const& iterator_state)
    {
        return  output_stream << "memento state " << iterator_state.m_position << " "
                              << iterator_state.m_samples.size();
    }

private:
    std::vector<const ISample*> m_samples;
    size_t m_position;

    IteratorState();
};

//! @class IteratorMemento
//! @ingroup samples_internal
//! @brief Holds all iterator states encountered for SampleTreeIterator

class IteratorMemento
{
public:
    IteratorMemento() {}
    virtual ~IteratorMemento() {}

    void push_state(const IteratorState& state) { m_state_stack.push(state); }
    void pop_state() { m_state_stack.pop(); }
    IteratorState& get_state() { return m_state_stack.top(); }
    bool empty() const { return m_state_stack.empty(); }
    void reset() { while(!m_state_stack.empty()) m_state_stack.pop(); }
    const ISample* getCurrent() { return m_state_stack.top().getCurrent(); }
    void next() { m_state_stack.top().next(); }
    size_t size() const { return m_state_stack.size(); }
protected:
    std::stack<IteratorState > m_state_stack;
};


//! @class SampleTreeIterator
//! @ingroup samples_internal
//! @brief Iterator through ISample tree of objects inside ISample object.
//!
//! Usage example:
//!    SampleTreeIterator it(&sample);
//!    it.first();
//!    while( !it.is_done() ) {
//!        ISample *p_sample = it.get_current();
//!        it.next();
//!     }

class BA_CORE_API_ SampleTreeIterator
{
public:
    SampleTreeIterator(const ISample *root);
    SampleTreeIterator& operator=(const SampleTreeIterator &other);
    virtual ~SampleTreeIterator();

    void first();
    void next();
    const ISample* getCurrent();
    bool isDone() const;
    size_t getLevel() const;
protected:
    boost::scoped_ptr<ISampleIteratorStrategy> mP_strategy;
    IteratorMemento m_memento_itor;
    const ISample* mp_root;
};

#endif // ISAMPLETREEITERATOR_H


