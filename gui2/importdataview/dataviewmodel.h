//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/importdataview/dataviewmodel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_IMPORTDATAVIEW_DATAVIEWMODEL_H
#define BORNAGAIN_GUI2_IMPORTDATAVIEW_DATAVIEWMODEL_H

#include "darefl_export.h"
#include "mvvm/viewmodel/topitemsviewmodel.h"

namespace ModelView {
class SessionModel;
}

namespace gui2 {

class ExperimentalDataModel;

//! View model for ExperimentalDataModel with drag-and-drop support.

class DAREFLCORE_EXPORT DataViewModel : public ModelView::TopItemsViewModel {
    Q_OBJECT

public:
    DataViewModel(ExperimentalDataModel* model, QObject* parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QMimeData* mimeData(const QModelIndexList& index_list) const override;
    Qt::DropActions supportedDragActions() const override;
    Qt::DropActions supportedDropActions() const override;
    bool canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                         const QModelIndex& parent) const override;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                      const QModelIndex& parent) override;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_IMPORTDATAVIEW_DATAVIEWMODEL_H
