// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_CORE_APP_CONSTANTS_H
#define DAREFL_CORE_APP_CONSTANTS_H

#include <QString>

namespace DaRefl::Constants
{

//! Constants for QSettings.

const QString DataLoaderGroupKey = "dataloader";
const QString ParserPropertyGroupKey = "parserproperty";

//! Initial state of some widgets.

const inline bool live_simulation_default_on = false;

} // namespace DaRefl::Constants

#endif // DAREFL_CORE_APP_CONSTANTS_H
