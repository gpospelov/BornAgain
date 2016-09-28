// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ThreadedComputation.cpp
//! @brief     Implements class ThreadedComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ProgressHandler.h"
#include "ThreadedComputation.h"

//! Increments progress count; updates upstream progress handler; returns true unless cancelled.
bool ThreadedComputation::stepProgress(ProgressHandler* progress)
{
    ++m_count;
    if( m_count==bundle ) {
        if( !progress->incrementDone(bundle) )
            return false;
        m_count = 0;
    }
    return true;
}
