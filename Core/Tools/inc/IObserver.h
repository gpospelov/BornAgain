#ifndef IOBSERVER_H
#define IOBSERVER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IObserver.h
//! @brief  Definition of IObserver class
//! @author Scientific Computing Group at FRM II
//! @date   08.10.2012

#include "Exceptions.h"
#include <list>
class IObservable;

//- -------------------------------------------------------------------
//! @class IObserver
//! @brief IObserver interface from Observer pattern to define one-to-many
//! dependency between objects
//- -------------------------------------------------------------------
class IObserver {
public:
    virtual ~IObserver(){}
    //! method which is used by observable object to notify change in status
    virtual void update (IObservable *subject) = 0;
protected:
    IObserver(){}
};


//- -------------------------------------------------------------------
//! @class IObservable
//! @brief IObserverable interface from Observer pattern to define one-to-many
//! dependency between objects
//- -------------------------------------------------------------------
class IObservable {
public:
    typedef std::list<IObserver *> observers_t;
    virtual ~IObservable(){}

    //! attach observer to the list of observers
    virtual void attachObserver(IObserver *obj) { m_observers.push_back(obj); }

    //! detach observer from observers list
    virtual void detachObserver(IObserver *obj) { m_observers.remove(obj); }

    //! notify observers about change in status
    virtual void notifyObservers()
    {
        for(observers_t::iterator it = m_observers.begin(); it!=m_observers.end(); ++it) {
            (*it)->update(this);
        }
    }

protected:
    IObservable(){}
private:
    observers_t m_observers;
};


#endif // IOBSERVER_H
