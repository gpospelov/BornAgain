// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/ProgressHandler.h
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
#include <memory>

class Simulation;

//! Provides the functionality to calculate the progress of running simulation and report it to GUI.
//!
//! Thread safe to be used from Computation.
//!
//! @ingroup algorithms_internal

class BA_CORE_API_ ProgressHandler : public INoncopyable
{
public:
    typedef std::function<bool(int)> Callback_t;

    ProgressHandler();

    void init(Simulation* simulation, int param_combinations = 1);
    void reset();

    void setCallback(ProgressHandler::Callback_t callback) { m_callback = callback; }
    void setNmaxItems(long max) { m_nitems_max = max; }

    bool update(int items_done);

private:
    ProgressHandler::Callback_t m_callback;
    long m_nitems;
    long m_nitems_max;
    int m_percentage_done;
};

// Shared pointer is needed because multiple Computation threads will contain a
// local clone of Simulation, which contains the original ProgressHandler
typedef std::shared_ptr<class ProgressHandler> ProgressHandler_t;

#endif // PROGRESSHANDLER_H
