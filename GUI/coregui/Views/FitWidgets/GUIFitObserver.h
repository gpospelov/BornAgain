// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/GUIFitObserver.h
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

#include "IFitObserver.h"
#include <QObject>
#include <atomic>

template <class T> class OutputData;
class FitSuite;
class IntensityDataItem;

//! The GUIFitObserver class is a intermediate between FitSuite and the GUI.
//! It is called at the end of each iterations and sends (messages, data) to the rest of the GUI.

class BA_CORE_API_ GUIFitObserver : public QObject, public IFitObserver
{
    Q_OBJECT

public:

    GUIFitObserver(QObject *parent = 0);

    void update(FitSuite *subject);

    void finishedPlotting();

    const OutputData<double> *getSimulationData() const;
    const OutputData<double> *getChiSquaredData() const;

public slots:

    void setInterval(int val);

signals:

    void updateStatus(const QString &);

    void updatePlots();

    void updateLog(const QString &);

    void startFitting(OutputData<double>*);

    void updateParameters(const QStringList &, QVector<double>);

private:
    bool canUpdatePlots(FitSuite *fitSuite);
    bool canUpdateStatus(FitSuite *fitSuite);

    std::atomic<bool> m_block_update_plots;
    int m_update_interval;
    std::unique_ptr<OutputData<double> > m_simData;
    std::unique_ptr<OutputData<double> > m_chiData;
};

#endif
