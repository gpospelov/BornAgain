// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ProgressHandler.h
//! @brief     Defines class ProgressHandler.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PROGRESSHANDLER_H
#define PROGRESSHANDLER_H

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

class Simulation;

//! @class ProgressHandler
//! @ingroup algorithms_internal
//! @brief Provides the functionality to calculate the progress of running simulation
//! and report it to GUI.
//!
//! Thread safe to be used from DWBASimulation
class ProgressHandler
{
public:
    typedef boost::function<bool (int)> Callback_t;

    ProgressHandler();

    void setCallback(ProgressHandler::Callback_t callback) { m_callback = callback; }

    bool update(int n);

    void setNmaxItems(long max) { m_nitems_max = max; }

    long getProgress() const { return m_current_progress; }
    long getNitems() const { return m_nitems; }

    void init(Simulation *simulation, int param_combinations = 1);

    void reset();
private:
    ProgressHandler(const ProgressHandler& );
    ProgressHandler& operator=(const ProgressHandler& );

    ProgressHandler::Callback_t m_callback;
    long m_nitems;
    long m_nitems_max;
    long m_current_progress;
};

typedef boost::shared_ptr<class ProgressHandler > ProgressHandler_t;


#endif
