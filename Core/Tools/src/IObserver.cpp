#include "IObserver.h"


//void IObserver::setObservedSubject(IObservable *subject)
//{
//    m_observed_subject = subject;
//}


void IObservable::attachObserver(observer_t obj)
{
//    obj->setObservedSubject(this);
    m_observers.push_back(obj);
}


void IObservable::notifyObservers()
{
    for(observerlist_t::iterator it = m_observers.begin(); it!=m_observers.end(); ++it) {
        (*it)->update(this);
    }
}


//void IObservable::detachObserver(IObserver *obj)
//{
//    m_observers.remove(obj);
//}

