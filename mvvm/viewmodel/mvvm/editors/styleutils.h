//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/editors/styleutils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_STYLEUTILS_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_STYLEUTILS_H

#include "mvvm/viewmodel_export.h"

namespace ModelView {

namespace Style {

//! Returns int value corresponding to pixmap in standard Qt table/tree decorations.
MVVM_VIEWMODEL_EXPORT int DefaultPixmapSize();

//! Returns default height of info bar
MVVM_VIEWMODEL_EXPORT int DefaultInfoBarHeight();

//! Returns default size of text on info bar.
MVVM_VIEWMODEL_EXPORT int DefaultInfoBarTextSize();

} // namespace Style

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_STYLEUTILS_H
