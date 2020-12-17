//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/importdataview/importdataeditortoolbal.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

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
