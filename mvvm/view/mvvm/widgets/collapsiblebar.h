//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/collapsiblebar.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_COLLAPSIBLEBAR_H
#define BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_COLLAPSIBLEBAR_H

#include "mvvm/view_export.h"
#include <QFrame>

class QLabel;
class QString;

namespace ModelView {

//! Horizontal collapsible bar, part of CollapsibleListWidget.
//! Intended for placement into the QSplitter, makes client widget visible/invisible on clicks.

class MVVM_VIEW_EXPORT CollapsibleBar : public QFrame {
    Q_OBJECT

public:
    CollapsibleBar(QWidget* parent = nullptr);

    void setWidget(QWidget* widget, const QString& title);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    bool eventFilter(QObject* obj, QEvent* event) override;
    void updatePixmap();

    QWidget* m_controlledWidget{nullptr};
    QLabel* m_pixmapLabel{nullptr};
    QLabel* m_titleLabel{nullptr};
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_COLLAPSIBLEBAR_H
