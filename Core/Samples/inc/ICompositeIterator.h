#ifndef ICOMPOSITEITERATOR_H
#define ICOMPOSITEITERATOR_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ICompositeIterator.h
//! @brief  Definition of ICompositeIterator class and surroundings
//! @author Scientific Computing Group at FRM II
//! @date   18.06.2012

#include "ISample.h"
#include "ICompositeSample.h"
#include <iostream>
#include <stack>
#include <list>


//- -------------------------------------------------------------------
//! @class MementoState
//! @brief Definition of MementoState to hold state of IComositeSample iterator
//- -------------------------------------------------------------------
class MementoState
{
public:
   typedef ICompositeSample::iterator_t iterator_t;

    MementoState(iterator_t itor, iterator_t end_itor) : m_itor( itor ), m_end_itor( end_itor ) { }

    MementoState &operator=(const MementoState &other)
    {
        if(this != &other) {
            m_itor = other.m_itor;
            m_end_itor = other.m_end_itor;
        }
        return *this;
    }

    virtual ~MementoState(){}

    iterator_t &get_itor() { return m_itor; }
    bool is_end() const { return m_itor == m_end_itor; }
    void next() { m_itor++; }

    friend std::ostream &operator<<(std::ostream &o, MementoState const &m)
    {
      return  (o << "memento state " << &m.m_itor << " " << &m.m_end_itor);
    }

protected:
    iterator_t m_itor;
    iterator_t m_end_itor;
private:
    MementoState();
};


//- -------------------------------------------------------------------
//! @class MementoIterator
//! @brief Definition of MementoIterator to hold state of IComositeSample iterator
//- -------------------------------------------------------------------
class MementoIterator
{
public:
    MementoIterator() {}
    virtual ~MementoIterator() {}

    void push_state(const MementoState &state) { m_state_stack.push(state); }
    void pop_state() { m_state_stack.pop(); }
    MementoState &get_state() { return m_state_stack.top(); }
    bool empty() const { return m_state_stack.empty(); }
    void reset() { while(!m_state_stack.empty()) m_state_stack.pop(); }
    MementoState::iterator_t& get_current_itor() { return m_state_stack.top().get_itor(); }
    void next() { m_state_stack.top().next(); }
    size_t size() { return m_state_stack.size(); }
protected:
    std::stack<MementoState > m_state_stack;
};


//- -------------------------------------------------------------------
//! @class ICompositeIterator
//! @brief Definition of ICompositeIterator to walk through ISample tree
//! of objects inside ICompositeSample object.
//!
//! Example
//!    ICompositeIterator it = sample->createIterator();
//!    it.first();
//!    while( !it.is_done() ) {
//!        ISample *child = it.get_current();
//!        it.next();
//!     }
//- -------------------------------------------------------------------
class ICompositeIterator
{
public:
    ICompositeIterator(ICompositeSample *root) : m_root(root) { }
    virtual ~ICompositeIterator() { }

    void first();
    void next();
    ISample* get_current() { return *(m_memento_itor.get_current_itor()); }
    bool is_done() { return m_done; }
    size_t get_level() { return m_memento_itor.size(); }
protected:
    MementoIterator m_memento_itor;
    ICompositeSample* m_root;
    bool m_done;
};



#endif // ICOMPOSITEITERATOR_H
