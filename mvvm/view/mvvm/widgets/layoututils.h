//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/layoututils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_LAYOUTUTILS_H
#define BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_LAYOUTUTILS_H

#include "mvvm/view_export.h"

class QLayout;
class QGridLayout;
class QWidget;

//! @namespace LayoutUtils
//! @brief Utility functions to add/remove widgets to the layout on the fly.
//! Taken from https://stackoverflow.com/questions/5395266/removing-widgets-from-qgridlayout
//! Caveat: according to explanations given, grid layouts can only grow and never shrink.

namespace LayoutUtils {

//! Removes content from box layout.
MVVM_VIEW_EXPORT void clearLayout(QLayout* layout, bool deleteWidgets = true);

//! Removes row from grid layout (important: doesn't change row count).
MVVM_VIEW_EXPORT void removeRow(QGridLayout* layout, int row, bool deleteWidgets = true);

//! Removes column from grid layout.
MVVM_VIEW_EXPORT void removeColumn(QGridLayout* layout, int column, bool deleteWidgets = true);

//! Clear layout completely.
MVVM_VIEW_EXPORT void clearGridLayout(QGridLayout* layout, bool deleteWidgets = true);

//! Returns empty widget to occupy place in layout.
MVVM_VIEW_EXPORT QWidget* placeHolder();

} // namespace LayoutUtils

#endif // BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_LAYOUTUTILS_H
