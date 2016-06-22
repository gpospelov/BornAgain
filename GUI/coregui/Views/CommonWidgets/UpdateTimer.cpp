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

namespace {
const int default_timer_interval_in_msec = 10;
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

//! Sets the time interval in msec, during which updates will be accumulated.

void UpdateTimer::setAccumulateDuring(int accumulateDuring)
{
    m_accumulate_updates_during = accumulateDuring;
}

void UpdateTimer::onTimerTimeout()
{
    m_remaining_time_to_update -= m_timer_interval;

    if(m_remaining_time_to_update < 0) {
        m_timer->stop();
        processUpdates();
    }

}

void UpdateTimer::processUpdates()
{
    Q_ASSERT(!m_timer->isActive());

    if(m_update_request_count > 0) {
        emit timeToUpdate();
    }

    m_remaining_time_to_update = m_accumulate_updates_during;
    m_update_request_count = 0;
}
