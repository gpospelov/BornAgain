// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_STYLEUTILS_H
#define DAREFL_MAINWINDOW_STYLEUTILS_H

#include <darefl/darefl_export.h>

class QSize;
class QFont;
class QToolBar;

namespace DaRefl {

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

} // namespace DaRefl

#endif // DAREFL_MAINWINDOW_STYLEUTILS_H
