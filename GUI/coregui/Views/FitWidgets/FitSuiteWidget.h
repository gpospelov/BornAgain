// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSuiteWidget.h
//! @brief     Defines class FitSuiteWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEWIDGET_H
#define FITSUITEWIDGET_H

#include "FitProgressInfo.h"
#include "WinDllMacros.h"
#include <QWidget>

class QTabWidget;
class RunFitControlWidget;
class JobItem;
class FitParameterWidget;
class MinimizerSettingsWidget;
class FitResultsWidget;
class ParameterTuningWidget;
class FitSuiteManager;
class JobMessagePanel;

//! The FitSuiteWidget contains all fit settings for given JobItem (fit parameters,
//! minimizer settings). Controlled by FitActivityPanel.

class BA_CORE_API_ FitSuiteWidget : public QWidget
{
    Q_OBJECT

public:
    FitSuiteWidget(QWidget* parent = nullptr);

    void setItem(JobItem* jobItem);
    void setModelTuningWidget(ParameterTuningWidget* tuningWidget);
    void setJobMessagePanel(JobMessagePanel* jobMessagePanel);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

private slots:
    void onFittingError(const QString& text);

private:
    void connectSignals();

    QTabWidget* m_tabWidget;
    RunFitControlWidget* m_controlWidget;
    FitParameterWidget* m_fitParametersWidget;
    MinimizerSettingsWidget* m_minimizerSettingsWidget;
    FitResultsWidget* m_fitResultsWidget;
    FitSuiteManager* m_fitSuiteManager;
};

#endif // FITSUITEWIDGET_H
