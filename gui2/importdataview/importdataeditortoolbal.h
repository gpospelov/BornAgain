// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_IMPORTDATAVIEW_IMPORTDATAEDITORTOOLBAL_H
#define BORNAGAIN_GUI2_IMPORTDATAVIEW_IMPORTDATAEDITORTOOLBAL_H

#include "darefl_export.h"
#include <QToolBar>

namespace gui2 {

class ImportDataEditorActions;

//! Toolbar for ImportDataEditor.

class DAREFLCORE_EXPORT ImportDataEditorToolBar : public QToolBar {
    Q_OBJECT

public:
    ImportDataEditorToolBar(ImportDataEditorActions* editorActions, QWidget* parent = nullptr);

signals:
    void updateViewportRequest();

private:
    ImportDataEditorActions* m_editorActions{nullptr};
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_IMPORTDATAVIEW_IMPORTDATAEDITORTOOLBAL_H
