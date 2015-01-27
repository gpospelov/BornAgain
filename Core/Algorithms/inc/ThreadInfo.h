// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ThreadInfo.h
//! @brief     Defines struct ThreadInfo.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
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
    //! Get the start index to use for this batch and thread when the total
    //! size of the data is _total_size_
    int getBeginIndex(int total_size);

    //! Get the end index to use for this batch and thread when the total
    //! size of the data is _total_size_
    int getEndIndex(int total_size);

private:
    //! Impose consistency of members
    void imposeConsistency();
};

inline ThreadInfo::ThreadInfo()
: n_threads(0)
, current_thread(0)
, n_batches(1)
, current_batch(0)
{
}

inline int ThreadInfo::getBeginIndex(int total_size)
{
    imposeConsistency();
    int size_per_batch = total_size/n_batches;
    if (total_size%n_batches) ++size_per_batch;
    int size_of_this_batch =
            current_batch==n_batches-1
            ? total_size - (n_batches-1)*size_per_batch
            : size_per_batch;
    if (size_of_this_batch<=0) return total_size;
    int size_per_thread = size_of_this_batch/n_threads;
    if (size_of_this_batch%n_threads) ++size_per_thread;
    if (current_thread*size_per_thread>=size_of_this_batch) return total_size;
    return current_batch*size_per_batch + current_thread*size_per_thread;
}

inline int ThreadInfo::getEndIndex(int total_size)
{
    imposeConsistency();
    int size_per_batch = total_size/n_batches;
    if (total_size%n_batches) ++size_per_batch;
    int size_of_this_batch =
            current_batch==n_batches-1
            ? total_size - (n_batches-1)*size_per_batch
            : size_per_batch;
    if (size_of_this_batch<=0) return total_size;
    int size_per_thread = size_of_this_batch/n_threads;
    if (size_of_this_batch%n_threads) ++size_per_thread;
    if (current_thread*size_per_thread>=size_of_this_batch) return total_size;
    int end_of_thread_in_batch =
            current_thread==n_threads-1
            ? size_of_this_batch
            : (current_thread+1)*size_per_thread;
    if (end_of_thread_in_batch>size_of_this_batch) {
        end_of_thread_in_batch = size_of_this_batch;
    }
    return current_batch*size_per_batch + end_of_thread_in_batch;
}

inline void ThreadInfo::imposeConsistency()
{
    if (n_batches<2) {
        n_batches = 1;
        current_batch = 0;
    }
    if (n_threads<2) {
        n_threads = 1;
        current_thread = 0;
    }
    if (current_batch>=n_batches) {
        throw ClassInitializationException("Batch number must be smaller than "
                "number of batches.");
    }
    if (current_thread>=n_threads) {
        throw ClassInitializationException("Thread number must be smaller than "
                "number of threads.");
    }
}

#endif /* THREADINFO_H_ */