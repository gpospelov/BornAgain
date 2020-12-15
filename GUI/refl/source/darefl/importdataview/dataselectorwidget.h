// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_DATASELECTORWIDGET_H
#define DAREFL_IMPORTDATAVIEW_DATASELECTORWIDGET_H

#include <QWidget>
#include <darefl/darefl_export.h>

class QTreeView;

namespace ModelView
{
class PropertyTreeView;
class CollapsibleListWidget;
} // namespace ModelView

namespace DaRefl
{

class DataSelectionModel;
class DataViewModel;

//! Widget to select graphs and look at their properties.
//! Occupies the left part of ImportDataEditor.

class DAREFLCORE_EXPORT DataSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    DataSelectorWidget(DataViewModel* view_model, QWidget* parent = nullptr);

    DataSelectionModel* selectionModel() const;

signals:
    void selectionChanged();

private slots:
    void onSelectionChanged();

private:
    DataViewModel* m_viewModel{nullptr};
    DataSelectionModel* m_selectionModel{nullptr};
    QTreeView* m_selectorTree{nullptr};
    ModelView::PropertyTreeView* m_canvasPropertyEditor{nullptr};
    ModelView::PropertyTreeView* m_graphPropertyEditor{nullptr};
    ModelView::CollapsibleListWidget* m_collapsibleWidget{nullptr};
};

} // namespace DaRefl

#endif // DAREFL_IMPORTDATAVIEW_DATASELECTORWIDGET_H
