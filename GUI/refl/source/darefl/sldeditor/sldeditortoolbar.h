// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_SLDEDITORTOOLBAR_H
#define DAREFL_SLDEDITOR_SLDEDITORTOOLBAR_H

#include <QToolBar>
#include <darefl/darefl_export.h>

namespace DaRefl {

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

} // namespace DaRefl

#endif // DAREFL_SLDEDITOR_SLDEDITORTOOLBAR_H
