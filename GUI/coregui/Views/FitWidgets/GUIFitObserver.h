// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FittingWorker.h
//! @brief     Implements class FittingWorker
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GUIFITOBSERVER_H
#define GUIFITOBSERVER_H

#include "WinDllMacros.h"
#include "IFitObserver.h"
#include <QObject>
#include <atomic>

class FitSuite;
class IntensityDataItem;

class BA_CORE_API_ GUIFitObserver : public QObject, public IFitObserver
{
    Q_OBJECT

public:

    GUIFitObserver(QObject *parent = 0)
        : QObject(parent)
        , IFitObserver(1) {}

    void update(FitSuite *subject);

    void finishedPlotting();

public slots:

    void setInterval(int val);

signals:

    void updateStatus(const QString &);

    void updatePlots(IntensityDataItem*, IntensityDataItem*);

    void updateLog(const QString &);

private:
    std::atomic<bool> m_is_updating_plots;
    int m_update_interval;
};

#endif
