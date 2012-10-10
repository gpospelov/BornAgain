#include "IObserver.h"



/* ************************************************************************* */
// Observer
/* ************************************************************************* */
IObserver::~IObserver()
{
    if(m_observed_subject) m_observed_subject->detachObserver(this);
}


void IObserver::setObservedSubject(IObservable *subject)
{
    m_observed_subject = subject;
}



/* ************************************************************************* */
// Observable
/* ************************************************************************* */
void IObservable::attachObserver(IObserver *obj)
{
    obj->setObservedSubject(this);
    m_observers.push_back(obj);
}


void IObservable::detachObserver(IObserver *obj)
{
    m_observers.remove(obj);
}


void IObservable::notifyObservers()
{
    for(observers_t::iterator it = m_observers.begin(); it!=m_observers.end(); ++it) {
        (*it)->update(this);
    }
}

