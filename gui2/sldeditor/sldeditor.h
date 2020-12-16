// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_SLDEDITOR_H
#define DAREFL_SLDEDITOR_SLDEDITOR_H

#include <QWidget>
#include "darefl_export.h"

namespace DaRefl {
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

} // namespace DaRefl

#endif // DAREFL_SLDEDITOR_SLDEDITOR_H
