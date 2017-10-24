// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonController.h
//! @brief     Defines class FitComparisonController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITCOMPARISONCONTROLLER_H
#define FITCOMPARISONCONTROLLER_H

#include "WinDllMacros.h"
#include <QObject>

//! Provides syncronization between certain properties of fit related IntensityDataItems.
//! Part of FitComparisonWidget.

class BA_CORE_API_ FitComparisonController : public QObject
{
    Q_OBJECT
public:
    explicit FitComparisonController(QObject* parent = nullptr);

private:

};

#endif  // FITCOMPARISONCONTROLLER_H
