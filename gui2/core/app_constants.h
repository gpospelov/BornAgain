// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

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
