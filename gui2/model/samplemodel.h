//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/model/samplemodel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MODEL_SAMPLEMODEL_H
#define BORNAGAIN_GUI2_MODEL_SAMPLEMODEL_H

#include "darefl_export.h"
#include "mvvm/model/sessionmodel.h"

namespace gui2 {

//! Model to hold layers and multi-layers.
class DAREFLCORE_EXPORT SampleModel : public ModelView::SessionModel {
public:
    SampleModel(std::shared_ptr<ModelView::ItemPool> pool = {});

    void create_default_multilayer();
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MODEL_SAMPLEMODEL_H
