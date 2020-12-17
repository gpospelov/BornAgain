// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_LABELDATAROWSTRATEGY_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_LABELDATAROWSTRATEGY_H

#include "mvvm/interfaces/rowstrategyinterface.h"

class QStandardItem;

namespace ModelView {

class SessionItem;

//! Constructs row of QStandardItem's for given SessionItem.
//! Row consists of two columns, ViewLabelItem for SessionItem's display role and
//! ViewDataItem for Session's item data role.

class MVVM_VIEWMODEL_EXPORT LabelDataRowStrategy : public RowStrategyInterface {
public:
    QStringList horizontalHeaderLabels() const override;

    std::vector<std::unique_ptr<ViewItem>> constructRow(SessionItem*) override;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_LABELDATAROWSTRATEGY_H
