//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonitemcontainerconverter.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMCONTAINERCONVERTER_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMCONTAINERCONVERTER_H

#include "mvvm/model_export.h"
#include <functional>
#include <memory>

class QJsonObject;

namespace ModelView {

class SessionItem;
class SessionItemContainer;
struct ConverterCallbacks;

//! Converter between SessionItemContainer and JSON object.

class MVVM_MODEL_EXPORT JsonItemContainerConverter {
public:
    JsonItemContainerConverter(ConverterCallbacks callbacks);
    ~JsonItemContainerConverter();

    QJsonObject to_json(const SessionItemContainer& container);

    void from_json(const QJsonObject& json, SessionItemContainer& container);

private:
    struct JsonItemContainerConverterImpl;
    std::unique_ptr<JsonItemContainerConverterImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMCONTAINERCONVERTER_H
