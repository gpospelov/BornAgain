//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/viewmodel/defaultcelldecorator.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_DEFAULTCELLDECORATOR_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_DEFAULTCELLDECORATOR_H

#include "mvvm/interfaces/celldecoratorinterface.h"
#include <optional>

namespace ModelView {

//! Generates default cell decorations for Qt trees and tables.

class MVVM_VIEWMODEL_EXPORT DefaultCellDecorator : public CellDecoratorInterface {
public:
    bool hasCustomDecoration(const QModelIndex& index) const override;
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) override;

protected:
    virtual std::optional<std::string> cellText(const QModelIndex& index) const;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_DEFAULTCELLDECORATOR_H
