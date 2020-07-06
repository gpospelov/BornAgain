// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ThreadInfo.h
//! @brief     Defines struct ThreadInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef THREADINFO_H
#define THREADINFO_H

#include "Wrap/WinDllMacros.h"

//! Information to run simulation with dedicated number of threads.
//! @ingroup simulation

struct BA_CORE_API_ ThreadInfo {
    ThreadInfo();
    unsigned n_threads;
    unsigned n_batches;
    unsigned current_batch;
};

inline ThreadInfo::ThreadInfo() : n_threads(0), n_batches(1), current_batch(0) {}

#endif // THREADINFO_H
