// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParametersWidget.h
//! @brief     Declares class FitParametersWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERSWIDGET_H
#define FITPARAMETERSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QTreeView;

//! The FitParametersWidget class contains a tree view to set fit parameters (fix/release,
//! starting value, min/max bounds). It occupies buttom right corner of JobView.

class BA_CORE_API_ FitParametersWidget : public QWidget
{
    Q_OBJECT
public:
    FitParametersWidget(QWidget *parent = 0);

private:
    QTreeView *m_treeView;
};

#endif
