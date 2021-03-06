//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/adjustingscrollarea.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_ADJUSTINGSCROLLAREA_H
#define BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_ADJUSTINGSCROLLAREA_H

#include "mvvm/view_export.h"
#include <QScrollArea>

namespace ModelView {

//! Modification of standard scroll area, which makes widget with dynamic layout occupy the whole
//! available space.

class MVVM_VIEW_EXPORT AdjustingScrollArea : public QScrollArea {
    Q_OBJECT

public:
    AdjustingScrollArea(QWidget* parent = 0);
    void setWidget(QWidget* w);

    QSize sizeHint() const;

private:
    bool eventFilter(QObject* obj, QEvent* ev);
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_ADJUSTINGSCROLLAREA_H
