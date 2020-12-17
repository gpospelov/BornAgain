// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALEDITOR_H
#define BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALEDITOR_H

#include "darefl_export.h"
#include <QWidget>

namespace gui2 {

class ApplicationModels;
class MaterialEditorActions;
class MaterialEditorToolBar;
class MaterialEditorWidget;

//! Material editor.

class DAREFLCORE_EXPORT MaterialEditor : public QWidget {
    Q_OBJECT

public:
    MaterialEditor(QWidget* parent = nullptr);
    ~MaterialEditor();

    void setModels(ApplicationModels* models);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    MaterialEditorActions* m_actions{nullptr};
    MaterialEditorWidget* m_editorWidget{nullptr};
    MaterialEditorToolBar* m_toolBar{nullptr};
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALEDITOR_H
