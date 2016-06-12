// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/MinimizerSettingsWidget.h
//! @brief     Declares class MinimizerSettingsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERSETTINGSWIDGET_H
#define MINIMIZERSETTINGSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

//! The MinimizerSettingsWidget contains editor for all minnimizer settings and related fit
//! options. Part of FitSuiteWidget.

class BA_CORE_API_ MinimizerSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    MinimizerSettingsWidget(QWidget *parent = 0);

    QSize minimumSizeHint() const;

};

#endif
