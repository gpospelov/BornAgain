//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonvariantconverter.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONVARIANTCONVERTER_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONVARIANTCONVERTER_H

#include "mvvm/core/variant.h"
#include "mvvm/serialization/jsonvariantconverterinterface.h"
#include <functional>
#include <map>
#include <string>

class QJsonObject;
class QJsonVariant;

namespace ModelView {

//! Default converter between supported variants and json objects.

class MVVM_MODEL_EXPORT JsonVariantConverter : public JsonVariantConverterInterface {
public:
    JsonVariantConverter();

    QJsonObject get_json(const Variant& variant) override;

    Variant get_variant(const QJsonObject& object) override;

    bool isVariant(const QJsonObject& object) const;

private:
    struct Converters {
        std::function<QJsonObject(const Variant& variant)> variant_to_json;
        std::function<Variant(const QJsonObject& json)> json_to_variant;
    };

    std::map<std::string, Converters> m_converters;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONVARIANTCONVERTER_H
