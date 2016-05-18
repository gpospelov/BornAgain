// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/InfoLabelController.h
//! @brief     Declares class InfoLabelController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INFOLABELCONTROLLER_H
#define INFOLABELCONTROLLER_H

#include "WinDllMacros.h"
#include <QObject>
#include <QString>

class InfoLabelWidget;
class QAbstractScrollArea;

//! The InfoLabelController class controlls appearance of InfoLabelWidget (position, show/hide)
//! on top of some scroll area.

class BA_CORE_API_ InfoLabelController : public QObject
{
    Q_OBJECT
public:
    InfoLabelController(QObject *parent = 0);

    void setText(const QString &text);

    void setArea(QAbstractScrollArea *area);

    void setShown(bool shown);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void updateLabelGeometry();

    InfoLabelWidget *m_label;
    QAbstractScrollArea *m_area;
    QString m_text;
};

#endif
