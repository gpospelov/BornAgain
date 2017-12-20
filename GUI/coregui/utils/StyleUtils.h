// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/StyleUtils.h
//! @brief     DefinesStyleUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef STYLEUTILS_H
#define STYLEUTILS_H

#include "WinDllMacros.h"
#include <QString>

class QTreeView;

namespace StyleUtils
{

//! Sets style for the tree to use in property editors.
BA_CORE_API_ void setPropertyStyle(QTreeView* tree);

//! Returns string representing the style of QTreeView intended for property editor.
BA_CORE_API_ QString propertyTreeStyle();

//! Returns string representing the style of QTreeView intended for real time view.
BA_CORE_API_ QString realtimeTreeStyle();

}

#endif
