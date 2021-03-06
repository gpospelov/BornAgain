//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonitemdataconverter.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMDATACONVERTER_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMDATACONVERTER_H

#include "mvvm/serialization/jsonitemdataconverterinterface.h"
#include <QString>
#include <functional>
#include <memory>

class QJsonObject;

namespace ModelView {

class JsonVariantConverterInterface;

//! Default converter of SessionItemData to/from json object.

class MVVM_MODEL_EXPORT JsonItemDataConverter : public JsonItemDataConverterInterface {
public:
    using accept_strategy_t = std::function<bool(int)>;

    JsonItemDataConverter(accept_strategy_t to_json_accept = {},
                          accept_strategy_t from_json_accept = {});

    ~JsonItemDataConverter() override;

    QJsonArray to_json(const SessionItemData& data) override;

    void from_json(const QJsonArray& object, SessionItemData& data) override;

    static std::unique_ptr<JsonItemDataConverterInterface> createCopyConverter();

    static std::unique_ptr<JsonItemDataConverterInterface> createProjectConverter();

private:
    bool isRoleToJson(int role) const;
    bool isRoleFromJson(int role) const;

    accept_strategy_t m_to_json_accept;   //!< callback to find whether to write role to json
    accept_strategy_t m_from_json_accept; //!< callback to find whether to read role from json
    std::unique_ptr<JsonVariantConverterInterface> m_variant_converter;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMDATACONVERTER_H
