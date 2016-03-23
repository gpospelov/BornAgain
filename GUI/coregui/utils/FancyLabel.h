// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/FancyLabel.h
//! @brief     Defines class FancyLabel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FANCYLABEL_H
#define FANCYLABEL_H

#include "WinDllMacros.h"
#include <QLabel>
#include <QTimer>

//! The FancyLabel class is QLabel-like class with trivail animation, when text slowly
//! appears on the screen from left to right pretending to be typed
class BA_CORE_API_ FancyLabel : public QLabel
{
    Q_OBJECT
public:
    FancyLabel(const QString &text, QWidget *parent = 0);
    FancyLabel(QWidget *parent = 0);

    void setTextAnimated(const QString &animated_text);

private slots:
    void timeout();

private:
    void init_fancy_label();

    QString m_text;
    QTimer *m_timer;
    int m_total_effect_duration;
    int m_current_index;
};

#endif
