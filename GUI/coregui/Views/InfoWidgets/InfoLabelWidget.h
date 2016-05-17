// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/InfoLabelWidget.h
//! @brief     Declares class InfoLabelWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INFOLABELWIDGET_H
#define INFOLABELWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QString>
#include <QRect>

//! The InfoLabelWidget is a semi-transparent overlay label to palce on top of other
//! widgets outside of any layout context.

class InfoLabelWidget : public QWidget
{
public:
    InfoLabelWidget(QWidget *parent = 0);

    void setPosition(int x, int y);

    void setWarningMessage(const QString &text) {m_text = text;}

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString m_text;
    QRect m_bounding_rect;
};

#endif
