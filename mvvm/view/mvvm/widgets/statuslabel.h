//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/statuslabel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_STATUSLABEL_H
#define BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_STATUSLABEL_H

#include "mvvm/view_export.h"
#include <QFrame>

class QPaintEvent;

namespace ModelView {

//! Shows a single line of text on a white background.
//! Opposite to QLabel, doesn't trigger layout resize, being happy with place it has. If text string
//! is too long for current size, it will be clipped.

class MVVM_VIEW_EXPORT StatusLabel : public QFrame {
    Q_OBJECT

public:
    explicit StatusLabel(QWidget* parent = nullptr);

    void setText(const QString& text);
    void setFont(const QFont& font);
    void setPointSize(int pointSize);
    void setAlignment(Qt::Alignment);

protected:
    void paintEvent(QPaintEvent* event);

private:
    QString m_text;
    Qt::Alignment m_alignment;
    QFont m_font;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_STATUSLABEL_H
