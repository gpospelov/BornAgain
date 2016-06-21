// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/SessionItemWidget.h
//! @brief     Declares class ItemComboWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SESSIONITEMWIDGET_H
#define SESSIONITEMWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

//! The SessionItemWidget class is a base for all widgets representing the content of SessionItem.

class BA_CORE_API_ SessionItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SessionItemWidget(QWidget *parent = 0);

    virtual void setItem(class SessionItem *item) = 0;
    virtual QList<QAction *> actionList();

};

#endif

