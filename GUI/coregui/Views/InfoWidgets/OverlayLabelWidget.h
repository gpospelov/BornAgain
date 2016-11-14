// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/OverlayLabelWidget.h
//! @brief     Defines class OverlayLabelWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OVERLAYLABELWIDGET_H
#define OVERLAYLABELWIDGET_H

#include "WinDllMacros.h"
#include <QRect>
#include <QString>
#include <QWidget>

//! The OverlayLabelWidget is a semi-transparent overlay label to place on top of other
//! widgets outside of any layout context.

class BA_CORE_API_ OverlayLabelWidget : public QWidget
{
    Q_OBJECT
public:
    OverlayLabelWidget(QWidget *parent = 0);

    void setRectangle(const QRect &rect);
    void setPosition(int x, int y);

    void setText(const QString &text) {m_text = text;}

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString m_text;
    QRect m_bounding_rect;
};

#endif // OVERLAYLABELWIDGET_H
