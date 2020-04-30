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
#include <QFont>
#include <QString>

class QTreeView;
class QWidget;
class QLayout;

namespace StyleUtils
{

//! Sets style for the tree to use in property editors.
BA_CORE_API_ void setPropertyStyle(QTreeView* tree);

//! Returns string representing the style of QTreeView intended for property editor.
BA_CORE_API_ QString propertyTreeStyle();

//! Returns string representing the style of QTreeView intended for real time view.
BA_CORE_API_ QString realtimeTreeStyle();

//! Returns font for sections.
BA_CORE_API_ QFont sectionFont(bool bold = false);

//! Returns font for labels.
BA_CORE_API_ QFont labelFont(bool bold = false);

//! Make modal dialog resizable.
BA_CORE_API_ void setResizable(QDialog* dialog);

//! Creates details widget holding user content inside.
BA_CORE_API_ QWidget* createDetailsWidget(QWidget* content, const QString& name,
                                          bool expanded = true);

//! Creates details widget holding user layout inside.
BA_CORE_API_ QWidget* createDetailsWidget(QLayout* content, const QString& name,
                                          bool expanded = true);

} // namespace StyleUtils

#endif
