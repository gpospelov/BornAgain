//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/layereditor/layerviewmodel.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/layereditor/layerviewmodel.h"
#include "gui2/layereditor/layerviewmodelcontroller.h"

using namespace ModelView;

namespace gui2 {

LayerViewModel::LayerViewModel(SessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<LayerViewModelController>(model, this), parent)
{
}

} // namespace gui2
