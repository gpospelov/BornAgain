// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataPresentationProperties.cpp
//! @brief     Implements class DataPresentationProperties and its descendants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DataPresentationProperties.h"
#include "ComboProperty.h"
#include "DataItem.h"
#include "GUIHelpers.h"
#include "ModelPath.h"
#include "SessionModel.h"

namespace
{
ComboProperty colorCombo();
}

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

const QString Data1DPresentationProperties::P_COLOR = "Color";

Data1DPresentationProperties::Data1DPresentationProperties()
    : DataPresentationProperties(Constants::DataItem1DPropertiesType)
{
    addProperty(P_COLOR, colorCombo().variant());
}

namespace
{
ComboProperty colorCombo()
{
    ComboProperty result;
    result << "black"
           << "blue"
           << "orangered";
    result.setValue("black");
    return result;
}
}
