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

UpdateTimer::UpdateTimer(int timerInterval, QObject* parent)
    : QObject(parent)
    , m_update_request_count(0)
    , m_timer_interval(timerInterval)
    , m_is_busy(false)
    , m_timer(new QTimer(this))
{
    m_timer->setInterval(m_timer_interval);
    m_timer->setSingleShot(true);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));
}

void UpdateTimer::reset()
{
    m_update_request_count = 0;
    m_timer->stop();
    m_is_busy = false;
}

void UpdateTimer::scheduleUpdate()
{
    qDebug() << "UpdateTimer::scheduleUpdate() m_is_busy" << m_is_busy << m_update_request_count;
    if(m_is_busy)
        return;

    ++m_update_request_count;

    qDebug() << "UpdateTimer::scheduleUpdate()" << m_update_request_count;

    if(!m_timer->isActive()) {
        qDebug() << "       AccumulateTimer::scheduleUpdate() -> starting timer";
        m_timer->start(m_timer_interval);
    }
}


void UpdateTimer::onTimerTimeout()
{
    m_is_busy = true;
    qDebug() << "UpdateTimer::onTimerTimeout()" << m_update_request_count;

    if(m_update_request_count > 0) {
        m_update_request_count = 0;
        qDebug() << " emiting timeToUpdate()";
        emit timeToUpdate();
    }

    m_is_busy = false;
}



