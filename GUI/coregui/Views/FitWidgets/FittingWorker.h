// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FittingWorker.h
//! @brief     Implements class RunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITTINGWORKER_H
#define FITTINGWORKER_H

#include "WinDllMacros.h"
#include "IFitObserver.h"
#include <QObject>

class FitSuite;
class IObservable;

class BA_CORE_API_ FittingWorker : public QObject, public IFitObserver
{
    Q_OBJECT
public:
    FittingWorker() : IFitObserver(1) { me = IObservable::observer_t(this); }
    void update(FitSuite *subject);

public slots:
    void startFit();

    void interrupt();

signals:
    void statusUpdate(const QString &);

private:
    IObservable::observer_t me;
    boost::shared_ptr<FitSuite> m_fitsuite;

};

#endif
