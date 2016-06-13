// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FittingWorker.cpp
//! @brief     Implements class FittingWorker
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FittingWorker.h"
#include "FitSuite.h"
#include <QDateTime>
#include <QDebug>

void FittingWorker::startFit()
{
    int duration(0);
    QDateTime beginTime = QDateTime::currentDateTime();

    m_fitsuite->resetInterrupt();
    emit started();
    try {
        m_fitsuite->runFit();
        duration = durationSince(beginTime);

    } catch(const std::exception& ex) {
        duration = durationSince(beginTime);
        emit error(QString::fromLatin1(ex.what()));
    }
    emit finished(duration);
}

void FittingWorker::interruptFitting()
{
    if (m_fitsuite)
        m_fitsuite->interruptFitting();
}

int FittingWorker::durationSince(const QDateTime &since)
{
    QDateTime endTime = QDateTime::currentDateTime();
    return int(since.msecsTo(endTime));
}

