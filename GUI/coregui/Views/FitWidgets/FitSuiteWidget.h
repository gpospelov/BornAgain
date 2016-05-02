// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitSuiteWidget.h
//! @brief     Declares class FitSuiteWidget
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

#include "WinDllMacros.h"
#include <QWidget>

class QTabWidget;
class JobModel;
class JobItem;
class FitParametersWidget;
class ModelTuningWidget;

//! The FitSuiteWidget contains all fit settings for given JobItem (fit parameters,
//! minimizer settings). Controlled by FitActivityPanel

class BA_CORE_API_ FitSuiteWidget : public QWidget
{
    Q_OBJECT
public:
    FitSuiteWidget(JobModel *jobModel, QWidget *parent = 0);

    void setItem(JobItem *jobItem);
    void setModelTuningWidget(ModelTuningWidget *tuningWidget);

private:
    QTabWidget *m_tabWidget;
    FitParametersWidget *m_fitParametersWidget;
    JobModel *m_jobModel;
    JobItem *m_currentItem;
};

#endif
