// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALEDITORTOOLBAR_H
#define BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALEDITORTOOLBAR_H

#include "darefl_export.h"
#include <QToolBar>

namespace gui2 {

class MaterialEditorActions;

//! Material editor toolbar.

class DAREFLCORE_EXPORT MaterialEditorToolBar : public QToolBar {
    Q_OBJECT

public:
    MaterialEditorToolBar(MaterialEditorActions* actions, QWidget* parent = nullptr);
    ~MaterialEditorToolBar() = default;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALEDITORTOOLBAR_H
