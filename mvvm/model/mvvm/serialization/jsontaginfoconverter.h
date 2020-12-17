//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsontaginfoconverter.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONTAGINFOCONVERTER_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONTAGINFOCONVERTER_H

#include "mvvm/serialization/jsontaginfoconverterinterface.h"
#include <QString>

namespace ModelView {

//! Default converter between TagInfo and json object.

class MVVM_MODEL_EXPORT JsonTagInfoConverter : public JsonTagInfoConverterInterface {
public:
    static inline const QString nameKey = "name";
    static inline const QString minKey = "min";
    static inline const QString maxKey = "max";
    static inline const QString modelsKey = "models";

    QJsonObject to_json(const TagInfo& tag) override;

    TagInfo from_json(const QJsonObject& object) override;

    bool isTagInfo(const QJsonObject& object);
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONTAGINFOCONVERTER_H
