// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/UpdateTimer.h
//! @brief     Defines class UpdateTimer
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef UPDATETIMER_H
#define UPDATETIMER_H

#include "WinDllMacros.h"
#include <QObject>

class QTimer;

//! The UpdateTimer class accumulates update requests during certain period of time, and at
//! the end of this period emits special signal.

//! Used in ColorMap plot to avoid often replot of CustomPlot.

class BA_CORE_API_ UpdateTimer : public QObject {
    Q_OBJECT
public:
    explicit UpdateTimer(int timerInterval, QObject* parent = 0);

    void reset();

    void setTimeInterval(int timerInterval);

signals:
    void timeToUpdate();

public slots:
    void scheduleUpdate();

private slots:
    void onTimerTimeout();

private:
    qint64 m_update_request_count; //!< Number of requests accumulated so far.
    int m_timer_interval; //!< Timer in msec.
    bool m_is_busy;
    QTimer* m_timer;
};

#endif // UPDATETIMER_H
