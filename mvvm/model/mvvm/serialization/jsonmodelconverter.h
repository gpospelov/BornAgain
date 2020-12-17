//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonmodelconverter.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONMODELCONVERTER_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONMODELCONVERTER_H

#include "mvvm/serialization/jsonmodelconverterinterface.h"

class QJsonObject;

namespace ModelView {

class SessionModel;
enum class ConverterMode;

//! Converter of SessionModel to/from json object with posibility to select one of convertion modes.

class MVVM_MODEL_EXPORT JsonModelConverter : public JsonModelConverterInterface {
public:
    JsonModelConverter(ConverterMode mode);
    ~JsonModelConverter() override;

    //! Writes content of model into json.
    QJsonObject to_json(const SessionModel& model) const override;

    //! Reads json object and build the model.
    void from_json(const QJsonObject& json, SessionModel& model) const override;

private:
    ConverterMode m_mode;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONMODELCONVERTER_H
