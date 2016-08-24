// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProgressHandler.cpp
//! @brief     Implements class ProgressHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ProgressHandler.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "MultiLayer.h"
#include <mutex>

ProgressHandler::ProgressHandler()
    : m_callback(nullptr)
    , m_completed_nticks(0)
    , m_expected_nticks(0)
    , m_percentage_done(0)
{}

//! Collects number of ticks processed by different Computation's.
//! Calculates general progress and inform GUI if progress has changed.
//! Return flag is obtained from GUI and transferred to Computation to ask
//! them to stop calculations.
bool ProgressHandler::update(size_t ticks_done)
{
    static std::mutex single_mutex;
    std::unique_lock<std::mutex> single_lock( single_mutex );

    // this flag is to inform Simulation that GUI wants it to be terminated
    bool continue_calculations(true);

    m_completed_nticks += ticks_done;

    m_percentage_done = int(100.*m_completed_nticks/m_expected_nticks);
    //std::cout << "ProgressHandler::update done" << ticks_done << " of " << m_expected_nticks
    //         << " => progress:" << progress << std::endl;
    if(m_callback)
        continue_calculations = m_callback(m_percentage_done); // report to gui

    return continue_calculations;
}
