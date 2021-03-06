//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/layereditor/layereditorwidget.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_LAYEREDITOR_LAYEREDITORWIDGET_H
#define BORNAGAIN_GUI2_LAYEREDITOR_LAYEREDITORWIDGET_H

#include "darefl_export.h"
#include <QWidget>
#include <memory>

namespace ModelView {
class ViewModelDelegate;
} // namespace ModelView

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_LAYEREDITOR_LAYEREDITORWIDGET_H
