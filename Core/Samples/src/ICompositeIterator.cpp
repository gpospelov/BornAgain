#include "ICompositeIterator.h"
#include "Exceptions.h"


void ICompositeIterator::first()
{
    m_memento_itor.reset();
    if (m_root->begin_shallow() == m_root->end_shallow()) {
        m_done = true;
        return;
    }
    m_done = false;
    m_memento_itor.push_state( MementoState(m_root->begin_shallow(), m_root->end_shallow()) );
}


void ICompositeIterator::next()
{
    ISample *smp = (*m_memento_itor.get_current_itor());
    if( !smp ) {
        throw NullPointerException("ICompositeIterator::next() -> Error! Null object in the tree of objects");
    }
    if ( smp->getCompositeSample() ) {
        ICompositeSample* comp = dynamic_cast<ICompositeSample* > (*m_memento_itor.get_current_itor() );
        if(comp->begin_shallow() != comp->end_shallow() ) {
            m_memento_itor.push_state( MementoState(comp->begin_shallow(), comp->end_shallow()) );
            return;
        }
    }

    m_memento_itor.next();

    while ( !m_memento_itor.empty() && m_memento_itor.get_state().is_end() )
    {
        m_memento_itor.pop_state();
        if ( !m_memento_itor.empty() ) m_memento_itor.next();
    }

    if (m_memento_itor.empty()) m_done = true;

}
