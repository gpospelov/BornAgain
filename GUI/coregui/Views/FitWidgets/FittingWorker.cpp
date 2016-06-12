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

void FittingWorker::startFit()
{
    m_fitsuite->resetInterrupt();
    emit started();
    try {
        m_fitsuite->runFit();
    } catch(const std::exception& ex) {
        emit error(QString::fromLatin1(ex.what()));
    }
    emit finished();
}

void FittingWorker::interruptFitting()
{
    if (m_fitsuite) {
        m_fitsuite->interruptFitting();
    }
}

