//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/model/experimentaldatacontroller.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MODEL_EXPERIMENTALDATACONTROLLER_H
#define BORNAGAIN_GUI2_MODEL_EXPERIMENTALDATACONTROLLER_H

#include "darefl_export.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/signals/modellistener.h"

namespace gui2 {

class InstrumentModel;
class ExperimentalDataModel;

//! Listens for all changes in ExperimentalDataModel and updates properties in InstrumentModel.
//! Main task is to update links of ExperimentalScanItem to particular imported graph, when
//! ExperimentalDataModel is changing.

class DAREFLCORE_EXPORT ExperimentalDataController
    : public ModelView::ModelListener<ExperimentalDataModel> {
public:
    ExperimentalDataController(ExperimentalDataModel* data_model,
                               InstrumentModel* instrument_model);

private:
    void update_all();

    InstrumentModel* m_instrument_model{nullptr};
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MODEL_EXPERIMENTALDATACONTROLLER_H
