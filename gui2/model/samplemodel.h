// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_SAMPLEMODEL_H
#define DAREFL_MODEL_SAMPLEMODEL_H

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

#endif // DAREFL_MODEL_SAMPLEMODEL_H
