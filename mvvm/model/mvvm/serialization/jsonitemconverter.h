//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonitemconverter.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMCONVERTER_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMCONVERTER_H

#include "mvvm/serialization/jsonitemconverterinterface.h"

namespace ModelView {

class ItemFactoryInterface;
struct ConverterContext;

//! Converter between SessionItem and JSON object.

class MVVM_MODEL_EXPORT JsonItemConverter : public JsonItemConverterInterface {
public:
    JsonItemConverter(const ConverterContext& context);
    JsonItemConverter(const JsonItemConverter&) = delete;
    JsonItemConverter& operator=(const JsonItemConverter&) = delete;

    ~JsonItemConverter() override;

    QJsonObject to_json(const SessionItem* item) const override;

    std::unique_ptr<SessionItem> from_json(const QJsonObject& json) const override;

private:
    struct JsonItemConverterImpl;
    std::unique_ptr<JsonItemConverterImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMCONVERTER_H
