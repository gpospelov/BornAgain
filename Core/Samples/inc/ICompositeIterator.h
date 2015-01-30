// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ICompositeIterator.h
//! @brief     Defines and implements classes MementoState, MementoIterator;
//!              defines class ICompositeIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOMPOSITEITERATOR_H
#define ICOMPOSITEITERATOR_H

#include "ISample.h"
#include "ICompositeSample.h"
#include <iostream>
#include <stack>
#include <list>

//! @class MementoState
//! @ingroup samples_internal
//! @brief Holds state of iterator (Memento pattern) for ICompositeIterator

class BA_CORE_API_ MementoState
{
public:
    typedef std::list<ISample*>::const_iterator const_iterator_t;

    MementoState(const_iterator_t itor, const_iterator_t end_itor)
        : m_itor( itor ), m_end_itor( end_itor ) {}

    MementoState& operator=(const MementoState& other)
    {
        if(this !=& other) {
            m_itor = other.m_itor;
            m_end_itor = other.m_end_itor;
        }
        return *this;
    }

    virtual ~MementoState() {}

    const_iterator_t& get_itor() { return m_itor; }
    bool is_end() const { return m_itor == m_end_itor; }
    void next() { m_itor++; }

    friend std::ostream& operator<<(std::ostream& o, MementoState const& m)
    { return  (o << "memento state " <<& m.m_itor << " " <<& m.m_end_itor); }

protected:
    const_iterator_t m_itor;
    const_iterator_t m_end_itor;

private:
    MementoState();
};

//! @class MementoIterator
//! @ingroup samples_internal
//! @brief The iterator from Memento pattern, part of ICompositeSample iterator

class BA_CORE_API_ MementoIterator
{
public:
    MementoIterator() {}
    virtual ~MementoIterator() {}

    void push_state(const MementoState& state) { m_state_stack.push(state); }
    void pop_state() { m_state_stack.pop(); }
    MementoState& get_state() { return m_state_stack.top(); }
    bool empty() const { return m_state_stack.empty(); }
    void reset() { while(!m_state_stack.empty()) m_state_stack.pop(); }
    MementoState::const_iterator_t& get_current_itor()
    { return m_state_stack.top().get_itor(); }
    void next() { m_state_stack.top().next(); }
    size_t size() { return m_state_stack.size(); }
protected:
    std::stack<MementoState > m_state_stack;
};


//! @class ICompositeIterator
//! @ingroup samples_internal
//! @brief Iterator through ISample tree of objects inside ICompositeSample object.
//!
//! Usage example:
//!    ICompositeIterator it = sample->createIterator();
//!    it.first();
//!    while( !it.is_done() ) {
//!        ISample *child = it.get_current();
//!        it.next();
//!     }

class BA_CORE_API_ ICompositeIterator
{
public:
    ICompositeIterator(const ICompositeSample *root) : m_root(root), m_done(false) {}
    virtual ~ICompositeIterator() {}

    void first();
    void next();
    ISample* get_current() { return *(m_memento_itor.get_current_itor()); }
    bool is_done() { return m_done; }
    size_t get_level() { return m_memento_itor.size(); }
protected:
    MementoIterator m_memento_itor;
    const ICompositeSample* m_root;
    bool m_done;
};

#endif // ICOMPOSITEITERATOR_H


