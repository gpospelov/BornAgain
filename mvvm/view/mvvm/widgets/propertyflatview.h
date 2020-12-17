//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/propertyflatview.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_PROPERTYFLATVIEW_H
#define BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_PROPERTYFLATVIEW_H

#include "mvvm/view_export.h"
#include <QWidget>
#include <memory>

namespace ModelView {

class SessionItem;

//! Widget holding grid layout with editors and intended for displaying all properties of given
//! SessionItem.

class MVVM_VIEW_EXPORT PropertyFlatView : public QWidget {
    Q_OBJECT

public:
    PropertyFlatView(QWidget* parent = nullptr);
    ~PropertyFlatView();

    void setItem(SessionItem* item);

private:
    struct PropertyFlatViewImpl;
    std::unique_ptr<PropertyFlatViewImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_PROPERTYFLATVIEW_H
