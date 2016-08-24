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

class MultiLayer;

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

    void init(const MultiLayer* sample, int combinations);
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

#endif // PROGRESSHANDLER_H
