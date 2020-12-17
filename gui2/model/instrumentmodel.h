//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/model/instrumentmodel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MODEL_INSTRUMENTMODEL_H
#define BORNAGAIN_GUI2_MODEL_INSTRUMENTMODEL_H

#include "darefl_export.h"
#include "mvvm/model/sessionmodel.h"

namespace gui2 {

//! Model to store specular instruments settings.

class DAREFLCORE_EXPORT InstrumentModel : public ModelView::SessionModel {
public:
    InstrumentModel(std::shared_ptr<ModelView::ItemPool> pool = {});
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MODEL_INSTRUMENTMODEL_H
