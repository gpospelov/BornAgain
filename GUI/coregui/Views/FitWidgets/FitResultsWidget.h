// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitResultsWidget.h
//! @brief     Defines class FitResultsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITRESULTSWIDGET_H
#define FITRESULTSWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

//! The FitResultsWidget contains fitting summary. Part of FitSuiteWidget.

class BA_CORE_API_ FitResultsWidget : public QWidget
{
    Q_OBJECT

public:
    FitResultsWidget(QWidget* parent = 0);
};

#endif // FITRESULTSWIDGET_H
