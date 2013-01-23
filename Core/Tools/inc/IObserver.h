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
#include <boost/shared_ptr.hpp>

class IObservable;

//- -------------------------------------------------------------------
//! @class IObserver
//! @brief IObserver interface from Observer pattern to define one-to-many
//! dependency between objects
//- -------------------------------------------------------------------
class IObserver {
public:
//    IObserver() : m_observed_subject(0) {}
    virtual ~IObserver() {}

    //! method which is used by observable subject to notify change in status
    virtual void update (IObservable *subject) = 0;

//    //! set pointer to observed subject
//    virtual void setObservedSubject(IObservable *subject);
//private:
//    IObservable *m_observed_subject;
};


//- -------------------------------------------------------------------
//! @class IObservable
//! @brief IObserverable interface from Observer pattern to define one-to-many
//! dependency between objects
//- -------------------------------------------------------------------
class IObservable {
public:
    typedef boost::shared_ptr<IObserver > observer_t;
    typedef std::list<observer_t > observerlist_t;

    virtual ~IObservable(){}

    //! attach observer to the list of observers
    virtual void attachObserver(observer_t obj);

    //! notify observers about change in status
    virtual void notifyObservers();

private:
    observerlist_t m_observers;
};


#endif // IOBSERVER_H
