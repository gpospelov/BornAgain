//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonitemconverterinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMCONVERTERINTERFACE_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMCONVERTERINTERFACE_H

#include "mvvm/model_export.h"
#include <memory>

class QJsonObject;

namespace ModelView {

class SessionItem;

//! Base class for all converters of SessionItem to/from JSON object.

class MVVM_MODEL_EXPORT JsonItemConverterInterface {
public:
    virtual ~JsonItemConverterInterface() = default;

    //! Converts item to JSON.
    virtual QJsonObject to_json(const SessionItem* item) const = 0;

    //! Creates item from JSON.
    virtual std::unique_ptr<SessionItem> from_json(const QJsonObject&) const = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMCONVERTERINTERFACE_H
