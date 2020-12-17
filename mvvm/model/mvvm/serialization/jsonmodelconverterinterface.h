//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonmodelconverterinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONMODELCONVERTERINTERFACE_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONMODELCONVERTERINTERFACE_H

#include "mvvm/model_export.h"

class QJsonObject;

namespace ModelView {

class SessionModel;

//! Base class for all converters of SessionModel to/from json object.

class MVVM_MODEL_EXPORT JsonModelConverterInterface {
public:
    virtual ~JsonModelConverterInterface() = default;

    virtual QJsonObject to_json(const SessionModel&) const = 0;

    virtual void from_json(const QJsonObject&, SessionModel&) const = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONMODELCONVERTERINTERFACE_H
