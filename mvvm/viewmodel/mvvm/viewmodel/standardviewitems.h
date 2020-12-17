//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/viewmodel/standardviewitems.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_STANDARDVIEWITEMS_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_STANDARDVIEWITEMS_H

#include "mvvm/viewmodel/viewitem.h"

namespace ModelView {

class SessionItem;

//! Represents root item.

class MVVM_VIEWMODEL_EXPORT RootViewItem : public ViewItem {
public:
    explicit RootViewItem(SessionItem* item);
};

//! Represents empty cell of tree or table.

class MVVM_VIEWMODEL_EXPORT ViewEmptyItem : public ViewItem {
public:
    ViewEmptyItem();
    QVariant data(int role) const override;
};

//! Represents display name of SessionItem in any cell of Qt's trees and tables.

class MVVM_VIEWMODEL_EXPORT ViewLabelItem : public ViewItem {
public:
    explicit ViewLabelItem(SessionItem* item);

    QVariant data(int role) const override;
};

//! Represents data role of SessionItem in any cell of Qt's trees and tables.

class MVVM_VIEWMODEL_EXPORT ViewDataItem : public ViewItem {
public:
    explicit ViewDataItem(SessionItem* item);

    Qt::ItemFlags flags() const override;

    QVariant data(int role) const override;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_STANDARDVIEWITEMS_H
