// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ThreadedComputation.h
//! @brief     Defines class ThreadedComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef THREADEDCOMPUTATION_H
#define THREADEDCOMPUTATION_H

#include "INoncopyable.h"

class ProgressHandler;

//! Base class for threaded computation; keeps count of progress.

class ThreadedComputation: public INoncopyable
{
public:
    ThreadedComputation() : m_count(0) {}
protected:
    void stepProgress(ProgressHandler* progress);
private:
    const int bundle = 100;
    int m_count;
};

#endif // THREADEDCOMPUTATION_H
