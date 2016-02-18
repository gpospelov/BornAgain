// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParameterWidget.h
//! @brief     Defines class FitParameterWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERSETTTINGSWIDGET_H
#define MINIMIZERSETTTINGSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class FitModel;

class BA_CORE_API_ MinimizerSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    MinimizerSettingsWidget(FitModel *fitModel, QWidget *parent = 0);
};




#endif
