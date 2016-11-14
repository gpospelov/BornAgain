// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/WarningSignWidget.h
//! @brief     Defines class WarningSignWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef WARNINGSIGNWIDGET_H
#define WARNINGSIGNWIDGET_H

#include "WinDllMacros.h"
#include <QPixmap>
#include <QString>
#include <QWidget>

//! The WarningSignWidget is an transparent widget with warning sign pixmap intended to be
//! overlayed onto other widget at some arbitrary position.
class WarningSignWidget : public QWidget
{
public:
    WarningSignWidget(QWidget *parent = 0);

    void setPosition(int x, int y);

    void setWarningMessage(const QString &message) {m_warning_message = message;}

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QPixmap m_pixmap;
    QString m_warning_message;
};

#endif // WARNINGSIGNWIDGET_H
