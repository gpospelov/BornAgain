//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/importdataview/dataviewmodel.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/importdataview/dataviewmodel.h"
#include "gui2/model/experimentaldatamodel.h"
#include "gui2/model/item_constants.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/viewmodel/viewmodelutils.h"
#include "mvvm/widgets/widgetutils.h"
#include <QByteArray>
#include <QDataStream>
#include <QMimeData>

using namespace ModelView;

namespace {
const std::string ExperimentalDataMimeType = "darefl/ExperimentalDataMime";

} // namespace

namespace gui2 {

DataViewModel::DataViewModel(ExperimentalDataModel* model, QObject* parent)
    : ModelView::TopItemsViewModel(model, parent)
{
}

//! Return the Qt flags for given index. We allow GraphItem drag, they can be dropped on CanvasItem.

Qt::ItemFlags DataViewModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags result = ViewModel::flags(index);

    if (auto item = sessionItemFromIndex(index); item) {
        if (item->modelType() == ModelView::Constants::GraphItemType)
            result |= Qt::ItemIsDragEnabled;
        else if (item->modelType() == Constants::CanvasItemType)
            result |= Qt::ItemIsDropEnabled;
    }

    return result;
}

//! Generate the mime data for all selected items.

QMimeData* DataViewModel::mimeData(const QModelIndexList& index_list) const
{
    auto result = new QMimeData;

    // Get the list of the identifiers
    QStringList identifiers;
    for (auto item : Utils::UniqueItemsFromIndex(index_list))
        identifiers.append(QString::fromStdString(item->identifier()));

    result->setData(QString::fromStdString(ExperimentalDataMimeType),
                    Utils::serialize(identifiers));

    return result;
}

//! Supported drag actions.

Qt::DropActions DataViewModel::supportedDragActions() const
{
    return Qt::TargetMoveAction;
}

//! Supported drop actions.

Qt::DropActions DataViewModel::supportedDropActions() const
{
    return Qt::TargetMoveAction;
}

//! Returns true if we can drop item here.

bool DataViewModel::canDropMimeData(const QMimeData* data, Qt::DropAction, int, int,
                                    const QModelIndex& parent) const
{
    if (data->hasFormat(QString::fromStdString(ExperimentalDataMimeType)))
        if (auto target = sessionItemFromIndex(parent); target)
            return target->modelType() == Constants::CanvasItemType;

    return false;
}

bool DataViewModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                 const QModelIndex& parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    auto target = sessionItemFromIndex(parent);

    int requested_row = parent.isValid() ? parent.row() : row;

    // retrieving list of item identifiers and accessing items
    auto identifiers =
        Utils::deserialize(data->data(QString::fromStdString(ExperimentalDataMimeType)));
    for (auto id : identifiers) {
        auto item = sessionModel()->findItem(id.toStdString());

        int row = std::clamp(requested_row, 0, item->parent()->itemCount(item->tag()) - 1);
        sessionModel()->moveItem(item, target, {"", row});
    }

    return true;
}

} // namespace gui2
