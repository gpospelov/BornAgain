//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/mainwindow/styleutils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MAINWINDOW_STYLEUTILS_H
#define BORNAGAIN_GUI2_MAINWINDOW_STYLEUTILS_H

#include "darefl_export.h"

class QSize;
class QFont;
class QToolBar;

namespace gui2 {

//! Namespace for central access to all theme styling.

namespace StyleUtils {

//! Size of tolbar icons for LayerEditor, MaterialEditor and similar.
DAREFLCORE_EXPORT QSize ToolBarIconSize();

//! Hint on size of docks on main reflectometry window.
DAREFLCORE_EXPORT QSize DockSizeHint();

//! Hint on minimum size of docks on main reflectometry window.
DAREFLCORE_EXPORT QSize DockMinimumSizeHint();

//! Set common style for a toolbar.
DAREFLCORE_EXPORT void SetToolBarStyleTextBesides(QToolBar* toolbar);

}; // namespace StyleUtils

} // namespace gui2

#endif // BORNAGAIN_GUI2_MAINWINDOW_STYLEUTILS_H
