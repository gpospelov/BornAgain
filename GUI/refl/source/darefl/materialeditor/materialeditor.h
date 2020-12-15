// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MATERIALEDITOR_MATERIALEDITOR_H
#define DAREFL_MATERIALEDITOR_MATERIALEDITOR_H

#include <QWidget>
#include <darefl/darefl_export.h>

namespace DaRefl {

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

} // namespace DaRefl

#endif // DAREFL_MATERIALEDITOR_MATERIALEDITOR_H
