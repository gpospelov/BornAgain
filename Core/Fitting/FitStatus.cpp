// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitStatus.cpp
//! @brief     Implements class FitStatus.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitStatus.h"
#include "FitPrintService.h"

FitStatus::FitStatus(const FitObjective* fit_objective)
    : m_iteration_count(0)
    , m_fit_status(IDLE)
    , m_fit_objective(fit_objective)
{

}

FitStatus::~FitStatus() = default;

unsigned FitStatus::iterationCount() const
{
    return m_iteration_count;
}

void FitStatus::setInterrupted()
{
    m_fit_status = INTERRUPTED;
}

bool FitStatus::isInterrupted() const
{
    return m_fit_status == INTERRUPTED;
}

bool FitStatus::isCompleted() const
{
    return m_fit_status == COMPLETED;
}

void FitStatus::update()
{
    m_fit_status = RUNNING;
    m_observers.notify(*m_fit_objective);
    m_iteration_count++;
}

void FitStatus::initPrint(int every_nth)
{
    m_print_service.reset(new FitPrintService);

    FitObserver<FitObjective>::observer_t callback = [&](const FitObjective& objective) {
        m_print_service->print(objective);
    };

    addObserver(every_nth, callback);
}

void FitStatus::addObserver(int every_nth, fit_observer_t observer)
{
    m_observers.addObserver(every_nth, observer);
}

void FitStatus::finalize()
{
    m_fit_status = COMPLETED;
    m_observers.notify_all(*m_fit_objective);
}
