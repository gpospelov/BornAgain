// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/WarningSign.h
//! @brief     Defines class WarningSign
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef WARNINGSIGN_H
#define WARNINGSIGN_H

#include "WinDllMacros.h"
#include <QObject>

class WarningSignWidget;
class QWidget;

//! The WarningSign controls appearance of WarningSignWidget on top of parent widget.

class WarningSign : public QObject
{
public:
    WarningSign(QWidget* parent);

    void clear();

    void setWarningHeader(const QString& warningHeader);

    void setWarningMessage(const QString& warningMessage);

    void setArea(QWidget *area);

    bool isShown() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void updateLabelGeometry();
    QPoint positionForWarningSign() const;

    QString m_warning_header;
    QString m_warning_message;
    WarningSignWidget* m_warningWidget;
    QWidget *m_area;
    bool m_clear_just_had_happened;
};

#endif // WARNINGSIGN_H
