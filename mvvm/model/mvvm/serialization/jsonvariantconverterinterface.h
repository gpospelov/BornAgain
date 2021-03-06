//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonvariantconverterinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONVARIANTCONVERTERINTERFACE_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONVARIANTCONVERTERINTERFACE_H

#include "mvvm/core/variant.h"
#include "mvvm/model_export.h"

class QJsonObject;

namespace ModelView {

//! Base class for all supported converters of Variant to/from json object

class MVVM_MODEL_EXPORT JsonVariantConverterInterface {
public:
    virtual ~JsonVariantConverterInterface() = default;

    virtual QJsonObject get_json(const Variant&) = 0;

    virtual Variant get_variant(const QJsonObject&) = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONVARIANTCONVERTERINTERFACE_H
