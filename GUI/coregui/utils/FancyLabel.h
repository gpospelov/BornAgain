//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/utils/FancyLabel.h
//! @brief     Defines class FancyLabel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_UTILS_FANCYLABEL_H
#define BORNAGAIN_GUI_COREGUI_UTILS_FANCYLABEL_H

#include <QLabel>

//! The FancyLabel class is a QLabel-like class with trivial animation when text slowly
//! appears on the screen from left to right, pretending to be typed.

class FancyLabel : public QLabel {
    Q_OBJECT

public:
    FancyLabel(const QString& text, QWidget* parent = nullptr);
    FancyLabel(QWidget* parent = nullptr);

    void setTextAnimated(const QString& animated_text);

private slots:
    void onTimeout();

private:
    void init_fancy_label();

    QString m_text;
    QTimer* m_timer{nullptr};
    int m_total_effect_duration{0};
    int m_current_index{0};
};

#endif // BORNAGAIN_GUI_COREGUI_UTILS_FANCYLABEL_H
