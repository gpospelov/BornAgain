// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/UpdateTimer.cpp
//! @brief     Implements class UpdateTimer
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "UpdateTimer.h"
#include <QTimer>
#include <QDebug>

namespace {
const int default_timer_interval_in_msec = 2;
}

UpdateTimer::UpdateTimer(int accumulateDuring, QObject *parent)
    : QObject(parent)
    , m_accumulate_updates_during(accumulateDuring)
    , m_update_request_count(0)
    , m_timer_interval(default_timer_interval_in_msec)
    , m_remaining_time_to_update(0)
    , m_timer(new QTimer(this))
{

    m_timer->setInterval(m_timer_interval);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));

}

//! Sets time period in msec, during which updates will be accumulated.

void UpdateTimer::setAccumulateDuring(int accumulateDuring)
{
    m_accumulate_updates_during = accumulateDuring;
}

//! Sets timer interval in msec to check if it is time to propagate update requests back.

void UpdateTimer::setTimerInterval(int timerInterval)
{
    m_timer_interval = timerInterval;
}

//! Schedule subsequent update.

#include <iostream>
void UpdateTimer::scheduleUpdate()
{
    ++m_update_request_count;
    qDebug() << "TTT scheduleUpdate() m_update_request_count"
             << m_update_request_count
             << "m_remaining_time_to_update" << m_remaining_time_to_update;

    std::cout << "TTT scheduleUpdate() m_update_request_count"
             << m_update_request_count
             << "m_remaining_time_to_update" << m_remaining_time_to_update
             << "XXX" << m_timer_interval << std::endl;

    if(!m_timer->isActive()) {
        m_timer->start(m_timer_interval);
        m_remaining_time_to_update = m_accumulate_updates_during;
        qDebug() << "   TTT scheduleUpdate() -- starting --- m_remaining_time_to_update" << m_remaining_time_to_update;
    }
}


void UpdateTimer::onTimerTimeout()
{
    m_remaining_time_to_update -= m_timer_interval;
    qDebug() << "   TTT onTimerTimeout() m_remaining_time_to_update" << m_remaining_time_to_update;

    if(m_remaining_time_to_update <= 0) {
        m_timer->stop();
        qDebug() << "   TTT onTimerTimeout()  -- stopping -- m_remaining_time_to_update" << m_remaining_time_to_update;
        processUpdates();
    }

}

void UpdateTimer::processUpdates()
{
    Q_ASSERT(!m_timer->isActive());

    qDebug() << "   TTT processUpdates() m_update_request_count" << m_update_request_count;
    std::cout << "   TTT processUpdates() m_update_request_count" << m_update_request_count << std::endl;

    if(m_update_request_count > 0) {
        qDebug() << "   TTT processUpdates() --- emiting";
        emit timeToUpdate();
    }

    m_update_request_count = 0;
}
