// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_SLDELEMENTMODEL_H
#define DAREFL_SLDEDITOR_SLDELEMENTMODEL_H

#include "darefl_export.h"
#include "mvvm/model/sessionmodel.h"
#include <vector>

namespace ModelView {
class ExternalProperty;
}

namespace gui2 {

class LayerElementItem;

//! The model of the sld layer visual representation
class DAREFLCORE_EXPORT SLDElementModel : public ModelView::SessionModel {
public:
    SLDElementModel();

    //! Add a layer item
    LayerElementItem* addLayer();
};

} // namespace gui2

#endif // DAREFL_SLDEDITOR_SLDELEMENTMODEL_H
