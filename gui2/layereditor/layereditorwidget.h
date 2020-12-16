// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_LAYEREDITORWIDGET_H
#define DAREFL_LAYEREDITOR_LAYEREDITORWIDGET_H

#include <QWidget>
#include "darefl_export.h"
#include <memory>

namespace ModelView {
class ViewModelDelegate;
} // namespace ModelView

namespace DaRefl {

class ApplicationModels;
class LayerTreeView;
class LayerSelectionModel;
class LayerViewModel;

//! Widget to hold layer tree (LayerTreeView) and all corresponding models and delegates.
//! Belongs to LayerEditor.

class DAREFLCORE_EXPORT LayerEditorWidget : public QWidget {
    Q_OBJECT

public:
    LayerEditorWidget(QWidget* parent = nullptr);
    ~LayerEditorWidget();

    void setModels(ApplicationModels* models);

    LayerSelectionModel* selectionModel() const;

private:
    std::unique_ptr<LayerViewModel> m_viewModel;
    LayerSelectionModel* m_selectionModel{nullptr};
    LayerTreeView* m_layerView{nullptr};
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

} // namespace DaRefl

#endif // DAREFL_LAYEREDITOR_LAYEREDITORWIDGET_H
