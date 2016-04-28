// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/ObsoleteMinimizerSettingsWidget.h
//! @brief     Declares class ObsoleteMinimizerSettingsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETEMINIMIZERSETTTINGSWIDGET_H
#define OBSOLETEMINIMIZERSETTTINGSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class ObsoleteFitModel;

class BA_CORE_API_ ObsoleteMinimizerSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    ObsoleteMinimizerSettingsWidget(ObsoleteFitModel *fitModel, QWidget *parent = 0);
};




#endif
