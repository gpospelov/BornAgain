//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/collapsiblelistwidget.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_COLLAPSIBLELISTWIDGET_H
#define BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_COLLAPSIBLELISTWIDGET_H

#include "mvvm/view_export.h"
#include <QWidget>

class QSplitter;
class QString;

namespace ModelView {

//! Vertical widget with column of panels displayed one under another.
//! Each panel contains user widget and can be collapsed/expanded. When expanded,
//! the place occupied by the panel can be changed by draging a splitter.

class MVVM_VIEW_EXPORT CollapsibleListWidget : public QWidget {
    Q_OBJECT

public:
    CollapsibleListWidget(QWidget* parent = nullptr);

    void addWidget(QWidget* widget, const QString& title, bool collapsed = false);

private:
    QSplitter* m_splitter{nullptr};
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_COLLAPSIBLELISTWIDGET_H
