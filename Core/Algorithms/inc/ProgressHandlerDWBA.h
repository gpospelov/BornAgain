// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ProgressHandlerDWBA.h
//! @brief     Defines class ProgressHandlerDWBA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PROGRESSHANDLERDWBA_H
#define PROGRESSHANDLERDWBA_H

#include "ProgressHandler.h"

//! @class DWBAProgressHandler
//! @ingroup algorithms_internal
//! @brief Holds number of items processed by DWBASimulation and informs Simulation
//! every n'th processed item.
class ProgressHandlerDWBA
{
public:
    ProgressHandlerDWBA();
    void setCallback(ProgressHandler::Callback_t callback) { m_callback = callback; }
    ProgressHandler::Callback_t getCallback() const { return m_callback; }
    bool update();
    bool finished();
private:
    ProgressHandler::Callback_t m_callback;
    long m_nitems;
    long m_nitems_total;
    long m_report_every_nth;
};

#endif
