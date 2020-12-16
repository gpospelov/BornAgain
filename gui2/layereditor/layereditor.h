// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_LAYEREDITOR_H
#define DAREFL_LAYEREDITOR_LAYEREDITOR_H

#include <QWidget>
#include "darefl_export.h"

namespace ModelView {
class AbstractViewModel;
}

namespace DaRefl {

class ApplicationModels;
class LayerEditorActions;
class LayerEditorToolBar;
class LayerEditorWidget;

//! Layer editor.

class DAREFLCORE_EXPORT LayerEditor : public QWidget {
    Q_OBJECT

public:
    LayerEditor(QWidget* parent = nullptr);
    ~LayerEditor();

    void setModels(ApplicationModels* models);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void selectionChanged();

private:
    LayerEditorActions* m_actions{nullptr};
    LayerEditorWidget* m_editorWidget{nullptr};
    LayerEditorToolBar* m_toolBar{nullptr};
};

} // namespace DaRefl

#endif // DAREFL_LAYEREDITOR_LAYEREDITOR_H
