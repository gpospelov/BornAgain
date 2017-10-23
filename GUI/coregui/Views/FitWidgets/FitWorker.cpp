// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitWorker.cpp
//! @brief     Implements class FitWorker
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitWorker.h"
#include "FitSuite.h"
#include <QDateTime>

void FitWorker::startFit()
{
    int duration(0);
    QDateTime beginTime = QDateTime::currentDateTime();

    m_fitsuite->resetInterrupt();
    emit started();
    try {
        m_fitsuite->runFit();
        duration = durationSince(beginTime);

    } catch (const std::exception& ex) {
        duration = durationSince(beginTime);
        emit error(QString::fromLatin1(ex.what()));
    }
    emit finished(duration);
}

void FitWorker::interruptFitting()
{
    if (m_fitsuite)
        m_fitsuite->interruptFitting();
}

int FitWorker::durationSince(const QDateTime& since)
{
    QDateTime endTime = QDateTime::currentDateTime();
    return int(since.msecsTo(endTime));
}
