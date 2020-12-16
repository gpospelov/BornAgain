// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_IMPORTDATAVIEW_DATASELECTIONMODEL_H
#define BORNAGAIN_GUI2_IMPORTDATAVIEW_DATASELECTIONMODEL_H

#include "darefl_export.h"
#include <QItemSelectionModel>
#include <vector>

namespace ModelView {
class ViewModel;
class SessionItem;
class GraphItem;
} // namespace ModelView

namespace gui2 {

class CanvasItem;

//! Custom selection model for data view model (AbstractViewModel).

class DAREFLCORE_EXPORT DataSelectionModel : public QItemSelectionModel {
    Q_OBJECT

public:
    DataSelectionModel(ModelView::ViewModel* view_model, QObject* parent = nullptr);
    ~DataSelectionModel() = default;

    void selectItem(ModelView::SessionItem* item);
    void selectItems(std::vector<ModelView::SessionItem*> items);

    std::vector<ModelView::SessionItem*> selectedItems() const;

    const ModelView::ViewModel* viewModel() const;

    CanvasItem* activeCanvas() const;
    ModelView::GraphItem* selectedGraph() const;

    std::vector<CanvasItem*> selectedCanvas() const;

    std::vector<ModelView::GraphItem*> selectedGraphs() const;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_IMPORTDATAVIEW_DATASELECTIONMODEL_H
