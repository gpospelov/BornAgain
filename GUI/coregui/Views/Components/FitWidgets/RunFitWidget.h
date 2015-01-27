// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/FitWidgets/RunFitWidget.h
//! @brief     Defines class RunFitWidget
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RUNFITWIDGET_H
#define RUNFITWIDGET_H

#include <QWidget>


class BA_CORE_API_ RunFitWidget : public QWidget
{
    Q_OBJECT

public:
    RunFitWidget(QWidget *parent = 0);
};

#endif
