//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/FitWidgets/FitWorker.h
//! @brief     Implements class FitWorker
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITWORKER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITWORKER_H

#include <QObject>
#include <memory>

class FitObjectiveBuilder;

class FitWorker : public QObject {
    Q_OBJECT

public:
    FitWorker(std::shared_ptr<FitObjectiveBuilder> suite) { m_fit_objective = suite; }

public slots:

    void startFit();

    void interruptFitting();

signals:

    void started();

    void finished(int duration);

    void error(const QString& message);

private:
    int durationSince(const class QDateTime& since);
    std::shared_ptr<FitObjectiveBuilder> m_fit_objective;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITWORKER_H
