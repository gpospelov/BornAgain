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

template<class T>
std::vector<T*> DataItemView::propertyItems()
{
    std::vector<T*> result;
    auto items = getItems();
    std::transform(items.begin(), items.end(), std::back_inserter(result), [](SessionItem* item) {
        auto property_item = dynamic_cast<T*>(item);
        assert(property_item);
        return property_item;
    });
    return result;
}

template std::vector<DataPresentationProperties*> DataItemView::propertyItems();

template<class T>
T* DataItemView::propertyItem(size_t i) const
{
    auto property_item = dynamic_cast<DataPresentationProperties*>(getItems()[static_cast<int>(i)]);
    assert(property_item);
    return property_item;
}

template DataPresentationProperties* DataItemView::propertyItem(size_t) const;

DataItemView::DataItemView(const QString& model_type)
    : SessionItem(model_type)
{
    registerTag(T_CHILDREN, 0, -1, QStringList() << Constants::DataItem1DPropertiesType);
    setDefaultTag(T_CHILDREN);
}

std::vector<DataItem*> DataItemView::dataItems()
{
    std::vector<DataItem*> result;
    auto items = propertyItems();
    std::transform(items.begin(), items.end(), std::back_inserter(result), [](DataPresentationProperties* item) {
        auto data_item = item->dataItem();
        assert(data_item);
        return data_item;
    });
    return result;
}

DataItem* DataItemView::dataItem(size_t i) const
{
    return propertyItem(i)->dataItem();
}

const OutputData<double>* DataItemView::getOutputData(size_t i) const
{
    auto data_item = dataItem(i);
    assert(data_item);
    return data_item->getOutputData();
}

/*----------------------------------------------*/

const QString DataPresentationProperties::P_LINK = "data link";

DataPresentationProperties::DataPresentationProperties(const QString& model_type)
    : SessionItem(model_type)
{
    addProperty(P_LINK, "");
}

void DataPresentationProperties::setDataItem(DataItem* item)
{
    const QString& path = ModelPath::getPathFromIndex(item->index());
    setItemValue(P_LINK, path);
}

DataItem* DataPresentationProperties::dataItem()
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
