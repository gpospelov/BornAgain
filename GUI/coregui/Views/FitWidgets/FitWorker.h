// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitWorker.h
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

#ifndef FITWORKER_H
#define FITWORKER_H

#include "WinDllMacros.h"
#include <QObject>
#include <memory>

class FitSuite;

class BA_CORE_API_ FitWorker : public QObject
{
    Q_OBJECT

public:
    FitWorker(std::shared_ptr<FitSuite> suite) { m_fitsuite = suite; }

public slots:

    void startFit();

    void interruptFitting();

signals:

    void started();

    void finished(int duration);

    void error(const QString& message);

private:
    int durationSince(const class QDateTime& since);
    std::shared_ptr<FitSuite> m_fitsuite;
};

#endif // FITWORKER_H
