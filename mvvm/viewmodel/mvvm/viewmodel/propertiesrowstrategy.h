//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/viewmodel/propertiesrowstrategy.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_PROPERTIESROWSTRATEGY_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_PROPERTIESROWSTRATEGY_H

#include "mvvm/interfaces/rowstrategyinterface.h"

class QStandardItem;

namespace ModelView {

class SessionItem;

//! Constructs row of QStandardItem's for given SessionItem.
//! Row consists of columns with all PropertyItem's of given SessionItem.

class MVVM_VIEWMODEL_EXPORT PropertiesRowStrategy : public RowStrategyInterface {
public:
    PropertiesRowStrategy(std::vector<std::string> labels = {});

    QStringList horizontalHeaderLabels() const override;

    std::vector<std::unique_ptr<ViewItem>> constructRow(SessionItem* item) override;

private:
    void update_column_labels(std::vector<ModelView::SessionItem*> items);
    std::vector<std::string> current_column_labels;
    std::vector<std::string> user_defined_column_labels;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_PROPERTIESROWSTRATEGY_H
