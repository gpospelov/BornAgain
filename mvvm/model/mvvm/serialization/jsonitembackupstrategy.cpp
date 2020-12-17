//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonitembackupstrategy.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/serialization/jsonitembackupstrategy.h"
#include "mvvm/factories/itemconverterfactory.h"
#include "mvvm/model/sessionitem.h"
#include <QJsonObject>

using namespace ModelView;

struct JsonItemBackupStrategy::JsonItemBackupStrategyImpl {
    std::unique_ptr<JsonItemConverterInterface> m_converter;
    QJsonObject m_json;
};

JsonItemBackupStrategy::JsonItemBackupStrategy(const ItemFactoryInterface* item_factory)
    : p_impl(std::make_unique<JsonItemBackupStrategyImpl>()) {
    p_impl->m_converter = CreateItemCloneConverter(item_factory);
}

JsonItemBackupStrategy::~JsonItemBackupStrategy() = default;

std::unique_ptr<SessionItem> JsonItemBackupStrategy::restoreItem() const {
    return p_impl->m_converter->from_json(p_impl->m_json);
}

void JsonItemBackupStrategy::saveItem(const SessionItem* item) {
    p_impl->m_json = p_impl->m_converter->to_json(item);
}
