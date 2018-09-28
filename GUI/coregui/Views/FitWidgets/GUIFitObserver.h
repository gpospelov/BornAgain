// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/GUIFitObserver.h
//! @brief     Implements class GUIFitObserver
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GUIFITOBSERVER_H
#define GUIFITOBSERVER_H

#include "IFitObserver.h"
#include "FitProgressInfo.h"
#include <QObject>
#include <condition_variable>
#include <mutex>

template <class T> class OutputData;
class FitSuite;
class IntensityDataItem;

//! The GUIFitObserver class is a intermediate between FitSuite and the GUI.
//! It is called at the end of each iterations and sends (messages, data) to the rest of the GUI.

class BA_CORE_API_ GUIFitObserver : public QObject, public IFitObserver
{
    Q_OBJECT

public:
    GUIFitObserver(QObject* parent = nullptr);
    ~GUIFitObserver();

    void update(FitSuite* subject);

    void finishedPlotting();

    FitProgressInfo progressInfo();

public slots:
    void setInterval(int val);

signals:
    void updateReady();

private:
    bool is_suitable_iteration(FitSuite* fitSuite);
    bool is_obligatory_iteration(FitSuite* fitSuite);
    std::string reportToString(FitSuite* fitSuite);

    bool m_block_update_plots;
    std::mutex m_update_plot_mutex;
    std::condition_variable m_on_finish_notifier;
    int m_update_interval;
    FitProgressInfo m_iteration_info;
};

#endif // GUIFITOBSERVER_H
