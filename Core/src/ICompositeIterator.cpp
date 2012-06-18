#include "ICompositeIterator.h"


void ICompositeIterator::first()
{
    //std::cout << "1.1" << std::endl;
    m_memento_itor.reset();
    if (m_root->begin_shallow() == m_root->end_shallow()) {
        m_done = true;
        return;
    }
    //std::cout << "1.2" << std::endl;
    m_done = false;
    m_memento_itor.push_state( MementoState(m_root->begin_shallow(), m_root->end_shallow()) );
    //std::cout << "1.3" << std::endl;
}


void ICompositeIterator::next()
{
    //std::cout << "---------------" << std::endl;
    //std::cout << "2.1 ICompositeIterator::next() " << std::endl;
    ISample *smp = (*m_memento_itor.get_current_itor());
    //std::cout << "2.1 ICompositeIterator::next() smp:" << smp << " id:" << smp->id << " " << smp->get_text() << std::endl;
    if ( smp->getCompositeSample()  )
//    if ( (*m_itor_memento.get_current_itor())->getCompositeSample() )
    {
        //std::cout << "2.2 ICompositeIterator::next() " << std::endl;
        ICompositeSample* comp = dynamic_cast<ICompositeSample* > (*m_memento_itor.get_current_itor() );
        if(comp->begin_shallow() != comp->end_shallow() ) {
        //std::cout << "2.3 comp:" << comp << std::endl;
            m_memento_itor.push_state( MementoState(comp->begin_shallow(), comp->end_shallow()) );
            //std::cout << "2.4" << std::endl;
            return;
        }
    }

    //std::cout << "2.5" << std::endl;
    // moving to the next item "in the plane"
    m_memento_itor.next();

    //std::cout << "2.6" << std::endl;
    // if new iterator is pointing to the end, then we go one level up
    while ( !m_memento_itor.empty() && m_memento_itor.get_state().is_end() )
    {
        //std::cout << "2.7" << std::endl;
        m_memento_itor.pop_state();
        //std::cout << "2.8" << std::endl;
        if ( !m_memento_itor.empty() ) m_memento_itor.next();
        //std::cout << "2.9" << std::endl;
    }

    //std::cout << "2.10" << std::endl;
    if (m_memento_itor.empty()) m_done = true;

    //std::cout << "2.11" << std::endl;

}
