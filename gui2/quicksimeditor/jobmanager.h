// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_JOBMANAGER_H
#define DAREFL_QUICKSIMEDITOR_JOBMANAGER_H

#include "darefl_export.h"
#include "gui2/quicksimeditor/quicksim_types.h"
#include "mvvm/utils/threadsafestack.h"
#include <QObject>

namespace gui2 {

//! Handles all thread activity for running job simulation in the background.

class DAREFLCORE_EXPORT JobManager : public QObject {
    Q_OBJECT

public:
    JobManager(QObject* parent = nullptr);
    ~JobManager() override;

    SimulationResult simulationResult();

signals:
    void progressChanged(int value);
    void simulationCompleted();

public slots:
    void requestSimulation(const multislice_t& multislice, const std::vector<double>& qvalues,
                           double intensity);
    void onInterruptRequest();

private:
    void wait_and_run();

    std::thread m_simThread;
    ModelView::threadsafe_stack<SimulationInput> m_requestedInputValues;
    ModelView::threadsafe_stack<SimulationResult> m_simulationResult;
    std::atomic<bool> m_isRunning;
    bool m_interruptRequest{false};
};

} // namespace gui2

#endif // DAREFL_QUICKSIMEDITOR_JOBMANAGER_H
