//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/sldeditor/sldeditor.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_SLDEDITOR_SLDEDITOR_H
#define BORNAGAIN_GUI2_SLDEDITOR_SLDEDITOR_H

#include "darefl_export.h"
#include <QWidget>

namespace gui2 {
class SLDEditorActions;
class SLDEditorToolBar;
class SLDViewWidget;
class ApplicationModels;

//! The SLD editor QWidget
class DAREFLCORE_EXPORT SLDEditor : public QWidget {
    Q_OBJECT

public:
    SLDEditor(QWidget* parent = nullptr);
    ~SLDEditor();

    void setModels(ApplicationModels* models);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    SLDEditorActions* m_editorActions{nullptr};
    SLDViewWidget* m_viewWidget{nullptr};
    SLDEditorToolBar* m_toolBar{nullptr};
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_SLDEDITOR_SLDEDITOR_H
