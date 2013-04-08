// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IObserver.h
//! @brief     Defines classes IObserver and IObservable (Observer pattern).
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IOBSERVER_H
#define IOBSERVER_H

#include "Exceptions.h"
#include <list>
#include <boost/shared_ptr.hpp>

class IObservable;

//! Observer interface from Observer pattern, for 1:n object dependencies.

class IObserver {
 public:
//    IObserver() : m_observed_subject(0) {}
    virtual ~IObserver() {}

    //! method which is used by observable subject to notify change in status
    virtual void update (IObservable *subject) = 0;

//    //! Sets pointer to observed subject
//    virtual void setObservedSubject(IObservable *subject);
//private:
//    IObservable *m_observed_subject;
};

//! Observable interface from Observer pattern, for 1:n object dependencies.

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


