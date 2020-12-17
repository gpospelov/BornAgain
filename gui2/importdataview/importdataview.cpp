//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/importdataview/importdataview.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/importdataview/importdataview.h"
#include "gui2/importdataview/importdataeditor.h"
#include "gui2/model/applicationmodels.h"
#include <QVBoxLayout>

namespace gui2 {

ImportDataView::ImportDataView(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_models(models) {
    auto layout = new QVBoxLayout(this);
    layout->addWidget(new ImportDataEditor(models->experimentalDataModel()));
    layout->setContentsMargins(0, 0, 0, 0);
}

} // namespace gui2
