// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProgressHandler.h
//! @brief     Defines class ProgressHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PROGRESSHANDLER_H
#define PROGRESSHANDLER_H

#include "INoncopyable.h"
#include "WinDllMacros.h"
#include <functional>

class MultiLayer;

//! Maintains information about progress of a computation.
//! Owner is the computation, which periodically calls the thread-safe function incrementDone(..).
//! An application (GUI or script) may subscribe(..) to be informed about progress.
//! It is then periodically called back by inform(..).
//! The return value of inform(..) can be used to request termination of the computation.
//!
//! @ingroup algorithms_internal

class BA_CORE_API_ ProgressHandler
{
public:
    typedef std::function<bool(size_t)> Callback_t;

    ProgressHandler() : m_inform(nullptr), m_expected_nticks(0), m_completed_nticks(0) {}
    ProgressHandler(const ProgressHandler& other)
        : m_inform(nullptr) // not clear whether we want to copy subscriptions
        , m_expected_nticks(other.m_expected_nticks)
        , m_completed_nticks(other.m_completed_nticks) {}
    void subscribe(ProgressHandler::Callback_t callback);
    void reset() { m_completed_nticks = 0; }
    void setExpectedNTicks(size_t n) { m_expected_nticks = n; }
    bool incrementDone(size_t ticks_done);

    int  percentage_done() const { return 100.*m_completed_nticks/m_expected_nticks; }

private:
    Callback_t m_inform;
    size_t m_expected_nticks;
    size_t m_completed_nticks;
    bool defaultMonitorExec(int);
};

#endif // PROGRESSHANDLER_H
