//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/layereditor/layerviewmodel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_LAYEREDITOR_LAYERVIEWMODEL_H
#define BORNAGAIN_GUI2_LAYEREDITOR_LAYERVIEWMODEL_H

#include "darefl_export.h"
#include "mvvm/viewmodel/viewmodel.h"

namespace ModelView {
class SessionModel;
} // namespace ModelView

namespace gui2 {

//! View model to display content of MultiLayerItem in table like views.

class DAREFLCORE_EXPORT LayerViewModel : public ModelView::ViewModel {
    Q_OBJECT

public:
    LayerViewModel(ModelView::SessionModel* model, QObject* parent = nullptr);
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_LAYEREDITOR_LAYERVIEWMODEL_H
