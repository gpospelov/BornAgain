// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORTOOLBAL_H
#define DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORTOOLBAL_H

#include "darefl_export.h"
#include <QToolBar>

namespace DaRefl {

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

} // namespace DaRefl

#endif // DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORTOOLBAL_H
