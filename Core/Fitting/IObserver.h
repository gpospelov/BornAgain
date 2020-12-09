//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/IObserver.h
//! @brief     Defines and implements classes IObserver and IObservable (Observer pattern).
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_CORE_FITTING_IOBSERVER_H
#define BORNAGAIN_CORE_FITTING_IOBSERVER_H

#include <list>
#include <memory>

class IObservable;

//! Observer interface from %Observer pattern.
//! @ingroup tools_internal

class IObserver {
public:
    virtual ~IObserver() = default;

    //! method which is used by observable subject to notify change in status
    virtual void notify(IObservable* subject) = 0;
};

//! Observable interface from %Observer pattern.
//! Shared pointer is used when passing these objects from Python to C++.
//! @ingroup tools_internal

class IObservable {
public:
    virtual ~IObservable() = default;

    //! attach observer to the list of observers
    virtual void attachObserver(std::shared_ptr<IObserver> obj) {
        m_observers.push_back(obj);
    }

    //! notify observers about change in status
    virtual void notifyObservers() {
        for (auto it : m_observers)
            it->notify(this);
    }

private:
    std::list<std::shared_ptr<IObserver>> m_observers;
};

#endif // BORNAGAIN_CORE_FITTING_IOBSERVER_H
