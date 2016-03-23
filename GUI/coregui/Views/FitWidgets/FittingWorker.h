// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FittingWorker.h
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

#ifndef FITTINGWORKER_H
#define FITTINGWORKER_H

#include "WinDllMacros.h"
#include <QObject>
#include <memory>

class FitSuite;

class BA_CORE_API_ FittingWorker : public QObject
{
    Q_OBJECT

public:

    FittingWorker(std::shared_ptr<FitSuite> suite) {m_fitsuite = suite;}

public slots:

    void startFit();

    void interruptFitting();

signals:

    void started();

    void finished();

    void error(const QString &message);

private:

    std::shared_ptr<FitSuite> m_fitsuite;

};

#endif
