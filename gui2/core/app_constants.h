//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/core/app_constants.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_CORE_APP_CONSTANTS_H
#define BORNAGAIN_GUI2_CORE_APP_CONSTANTS_H

#include <QString>

namespace gui2::Constants {

//! Constants for QSettings.

const QString DataLoaderGroupKey = "dataloader";
const QString ParserPropertyGroupKey = "parserproperty";

//! Initial state of some widgets.

const inline bool live_simulation_default_on = false;

} // namespace gui2::Constants

#endif // BORNAGAIN_GUI2_CORE_APP_CONSTANTS_H
