//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/adjustingscrollarea.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/widgets/adjustingscrollarea.h"
#include <QEvent>
#include <QScrollBar>

using namespace ModelView;

AdjustingScrollArea::AdjustingScrollArea(QWidget* parent) : QScrollArea(parent) {
    setObjectName("AdjustingScrollArea");
    setContentsMargins(0, 0, 0, 0);
    setWidgetResizable(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setStyleSheet("QScrollArea#AdjustingScrollArea {border: 0px; background-color:transparent;}");
}

void AdjustingScrollArea::setWidget(QWidget* w) {
    QScrollArea::setWidget(w);
    w->installEventFilter(this);
}

QSize AdjustingScrollArea::sizeHint() const {
    auto horizontal = horizontalScrollBar();
    QSize result(viewport()->width(), widget()->height() + horizontal->height() * 2);
    return result;
}

bool AdjustingScrollArea::eventFilter(QObject* obj, QEvent* ev) {
    if (obj == widget() && ev->type() != QEvent::Resize) {
        widget()->setMaximumWidth(viewport()->width());
        setMaximumHeight(height() - viewport()->height() + widget()->height());
    }

    return QScrollArea::eventFilter(obj, ev);
}
