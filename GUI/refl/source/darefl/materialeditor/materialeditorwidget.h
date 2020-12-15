// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MATERIALEDITOR_MATERIALEDITORWIDGET_H
#define DAREFL_MATERIALEDITOR_MATERIALEDITORWIDGET_H

#include <QWidget>
#include <darefl/darefl_export.h>
#include <memory>

namespace ModelView {
class ViewModel;
class ViewModelDelegate;
} // namespace ModelView

namespace DaRefl {

class ApplicationModels;
class MaterialModel;
class MaterialTableView;
class MaterialTreeView;
class MaterialSelectionModel;

//! Widget to hold material table (MaterialTreeView) and all corresponding models and delegates.
//! Belongs to MaterialEditor.

class DAREFLCORE_EXPORT MaterialEditorWidget : public QWidget {
    Q_OBJECT

public:
    MaterialEditorWidget(QWidget* parent = nullptr);
    ~MaterialEditorWidget();

    void setModels(ApplicationModels* models);

    MaterialSelectionModel* selectionModel() const;

private:
    MaterialModel* m_materialModel{nullptr};
    std::unique_ptr<ModelView::ViewModel> m_viewModel;
    MaterialSelectionModel* m_selectionModel{nullptr};
    MaterialTreeView* m_materialView{nullptr};
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

} // namespace DaRefl

#endif // DAREFL_MATERIALEDITOR_MATERIALEDITORWIDGET_H
