//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/editors/styleutils.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/editors/styleutils.h"

int ModelView::Style::DefaultPixmapSize() {
    const int default_pixmap_size = 16;
    return default_pixmap_size;
}

int ModelView::Style::DefaultInfoBarHeight() {
    const int default_info_bar_height = 24;
    return default_info_bar_height;
}

int ModelView::Style::DefaultInfoBarTextSize() {
    const int default_info_bar_text_saize = 8;
    return default_info_bar_text_saize;
}
