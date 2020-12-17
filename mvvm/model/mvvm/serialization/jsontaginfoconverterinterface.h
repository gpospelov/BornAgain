//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsontaginfoconverterinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONTAGINFOCONVERTERINTERFACE_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONTAGINFOCONVERTERINTERFACE_H

#include "mvvm/model_export.h"

class QJsonObject;

namespace ModelView {

class TagInfo;

//! Base class for all converters of TagInfo to/from json object

class MVVM_MODEL_EXPORT JsonTagInfoConverterInterface {
public:
    virtual ~JsonTagInfoConverterInterface() = default;

    virtual QJsonObject to_json(const TagInfo&) = 0;

    virtual TagInfo from_json(const QJsonObject&) = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONTAGINFOCONVERTERINTERFACE_H
