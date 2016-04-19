// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/ThreadInfo.h
//! @brief     Declares struct ThreadInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef THREADINFO_H_
#define THREADINFO_H_

#include "Exceptions.h"


//! @class ThreadInfo
//! @ingroup simulation
//! @brief Information to run simulation with dedicated number of threads

struct BA_CORE_API_ ThreadInfo
{
    ThreadInfo();
    int n_threads;
    int current_thread;
    int n_batches;
    int current_batch;
};

inline ThreadInfo::ThreadInfo()
: n_threads(0)
, current_thread(0)
, n_batches(1)
, current_batch(0)
{
}

#endif /* THREADINFO_H_ */
