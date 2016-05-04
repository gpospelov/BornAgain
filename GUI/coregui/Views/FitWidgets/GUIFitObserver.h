// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/GUIFitObserver.h
//! @brief     Implements class GUIFitObserver
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GUIFITOBSERVER_H
#define GUIFITOBSERVER_H

#include "WinDllMacros.h"
#include "IFitObserver.h"
#include "OutputData.h"
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
        , IFitObserver(1)
        , m_block_update_plots(false)
        , m_update_interval(1)
    {}

    void update(FitSuite *subject);

    void finishedPlotting();

public slots:

    void setInterval(int val);

signals:

    void updateStatus(const QString &);

    void updatePlots(OutputData<double>*, OutputData<double>*);

    void updateLog(const QString &);

    void startFitting(OutputData<double>*);

    void updateParameters(const QStringList &, QVector<double>);

private:
    bool isToUpdatePlots(FitSuite *fitSuite);
    bool isToUpdateStatus(FitSuite *fitSuite);

    std::atomic<bool> m_block_update_plots;
    int m_update_interval;
};

#endif
