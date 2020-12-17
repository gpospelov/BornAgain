//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonitemdataconverterinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMDATACONVERTERINTERFACE_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMDATACONVERTERINTERFACE_H

#include "mvvm/model_export.h"
#include <memory>

class QJsonArray;

namespace ModelView {

class SessionItemData;

//! Base class for all converters of SessionItemData to/from JSON object.

class MVVM_MODEL_EXPORT JsonItemDataConverterInterface {
public:
    virtual ~JsonItemDataConverterInterface() = default;

    //! Converts SessionItemData to JSON;
    virtual QJsonArray to_json(const SessionItemData&) = 0;

    //! Converts SessionItemData from JSON;
    virtual void from_json(const QJsonArray& object, SessionItemData& data) = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMDATACONVERTERINTERFACE_H
