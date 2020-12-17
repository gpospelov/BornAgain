//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/sldeditor/sldelementmodel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_SLDEDITOR_SLDELEMENTMODEL_H
#define BORNAGAIN_GUI2_SLDEDITOR_SLDELEMENTMODEL_H

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

#endif // BORNAGAIN_GUI2_SLDEDITOR_SLDELEMENTMODEL_H
