//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/interfaces/celldecoratorinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_INTERFACES_CELLDECORATORINTERFACE_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_INTERFACES_CELLDECORATORINTERFACE_H

#include "mvvm/viewmodel_export.h"
#include <string>

class QModelIndex;
class QStyleOptionViewItem;

namespace ModelView {

//! Interface class to generate cell decorations (i.e. text) in Qt trees and tables.

class MVVM_VIEWMODEL_EXPORT CellDecoratorInterface {
public:
    virtual ~CellDecoratorInterface() = default;

    virtual bool hasCustomDecoration(const QModelIndex& index) const = 0;
    virtual void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_INTERFACES_CELLDECORATORINTERFACE_H
