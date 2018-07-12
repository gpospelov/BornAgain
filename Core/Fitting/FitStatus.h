// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitStatus.h
//! @brief     Defines class FitStatus.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITSTATUS_H
#define FITSTATUS_H

#include "WinDllMacros.h"
#include "FitObserver.h"
#include <vector>
#include <functional>

class FitObjective;

//! Contains status of the fitting (running, interupted etc) and all intermediate
//! information which has to be collected during the fit.
//! Owned by FitObjective.

class BA_CORE_API_ FitStatus
{
public:
    using fit_observer_t = std::function<void(const FitObjective&)>;

    FitStatus(const FitObjective* fit_objective);

    unsigned iterationCount() const;

    void setInterrupted();
    bool isInterrupted() const;

    void update();

    void initPrint(int every_nth);

    void addObserver(int every_nth, fit_observer_t);

private:
    enum EFitStatus { IDLE, RUNNING, COMPLETED, FAILED, INTERRUPTED };
    unsigned m_iteration_count;
    EFitStatus m_fit_status;
    FitObserver<FitObjective> m_observers;
    const FitObjective* m_fit_objective;
};

#endif // FITSTATUS_H
