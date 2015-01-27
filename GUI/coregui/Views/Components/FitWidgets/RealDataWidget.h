// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/FitWidgets/RealDataWidget.h
//! @brief     Defines class RealDataWidget
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef REALDATAWIDGET_H
#define REALDATAWIDGET_H

#include <QWidget>


class BA_CORE_API_ RealDataWidget : public QWidget
{
    Q_OBJECT

public:
    RealDataWidget(QWidget *parent = 0);
};

#endif
