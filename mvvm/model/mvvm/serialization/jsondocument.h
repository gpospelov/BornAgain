//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsondocument.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONDOCUMENT_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONDOCUMENT_H

#include "mvvm/interfaces/modeldocumentinterface.h"
#include <memory>
#include <vector>

namespace ModelView {

class SessionModel;

//! Saves and restores list of SessionModel's to/from disk using json format.
//! Single JsonDocument corresponds to a single file on disk.

class MVVM_MODEL_EXPORT JsonDocument : public ModelDocumentInterface {
public:
    JsonDocument(const std::vector<SessionModel*>& models);
    ~JsonDocument() override;

    void save(const std::string& file_name) const override;
    void load(const std::string& file_name) override;

private:
    struct JsonDocumentImpl;
    std::unique_ptr<JsonDocumentImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONDOCUMENT_H
