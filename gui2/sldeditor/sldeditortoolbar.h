// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_SLDEDITOR_SLDEDITORTOOLBAR_H
#define BORNAGAIN_GUI2_SLDEDITOR_SLDEDITORTOOLBAR_H

#include "darefl_export.h"
#include <QToolBar>

namespace gui2 {

class SLDEditorActions;

//! Material editor toolbar.

class DAREFLCORE_EXPORT SLDEditorToolBar : public QToolBar {
    Q_OBJECT

public:
    SLDEditorToolBar(SLDEditorActions* actions, QWidget* parent = nullptr);
    ~SLDEditorToolBar() = default;

signals:
    void resetViewport();
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_SLDEDITOR_SLDEDITORTOOLBAR_H
