// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataItemView.cpp
//! @brief     Implements class DataItemView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DataItemView.h"
#include "DataItem.h"
#include "GUIHelpers.h"
#include "ModelPath.h"
#include "SessionModel.h"
#include <iostream>

const QString DataItemView::T_CHILDREN = "data links";

DataItemView::DataItemView()
    : SessionItem(Constants::DataItemViewType)
{
    registerTag(T_CHILDREN, 0, -1, QStringList() << Constants::DataLinkType);
    setDefaultTag(T_CHILDREN);
}

bool DataItemView::addItem(DataItem* data_item)
{
    if (this->model() != data_item->model())
        return false;
    return insertItem(-1, new DataItemLink(data_item));
}

std::vector<DataItem*> DataItemView::dataItems()
{
    std::vector<DataItem*> result;
    for (auto item : getItems()) {
        auto link_item = dynamic_cast<DataItemLink*>(item);
        assert(link_item);
        result.push_back(link_item->dataItem());
    }
    return result;
}

DataItem* DataItemView::dataItem(size_t i) const
{
    auto link_item = dynamic_cast<DataItemLink*>(getItems()[static_cast<int>(i)]);
    assert(link_item);
    return link_item->dataItem();
}

const OutputData<double>* DataItemView::getOutputData(size_t i) const
{
    auto data_item = dataItem(i);
    assert(data_item);
    return data_item->getOutputData();
}

using DataItemLink = DataItemView::DataItemLink;

const QString DataItemLink::P_LINK = "data link";

DataItemLink::DataItemLink()
    : SessionItem(Constants::DataLinkType)
{
    addProperty(P_LINK, "");
}

DataItemLink::DataItemLink(DataItem* item)
    : SessionItem(Constants::DataLinkType)
{
    const QString& path = ModelPath::getPathFromIndex(item->index());
    addProperty(P_LINK, path);
}

DataItem* DataItemLink::dataItem()
{
    SessionModel* hosting_model = this->model();
    const QString& path = getItemValue(P_LINK).toString();
    auto item_index = ModelPath::getIndexFromPath(hosting_model, path);
    if (!item_index.isValid()) {
        std::stringstream os;
        os << "Error in DataItem1DView::DataItemImage::dataItem: index produced by path";
        os << path.toStdString() << " is invalid" << std::endl;
        throw GUIHelpers::Error(QString::fromStdString(os.str()));
    }
    auto item = hosting_model->itemForIndex(item_index);
    return dynamic_cast<DataItem*>(item);
}
