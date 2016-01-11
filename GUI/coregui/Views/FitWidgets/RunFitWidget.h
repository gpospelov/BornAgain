// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitWidget.h
//! @brief     Defines class RunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RUNFITWIDGET_H
#define RUNFITWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>


class BA_CORE_API_ RunFitWidget : public QWidget
{
    Q_OBJECT
public:
    RunFitWidget(QWidget *parent = 0);

private slots:
    void onRunFit();

private:
    void run_test_fit();
    void run_test_fit_long();
};

#endif
