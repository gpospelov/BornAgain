// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_GRAPHCANVASWIDGET_H
#define DAREFL_IMPORTDATAVIEW_GRAPHCANVASWIDGET_H

#include <QWidget>
#include <darefl/darefl_export.h>

namespace ModelView
{
class GraphCanvas;
}

namespace DaRefl
{

class CanvasItem;

//! Widget to show canvas with graph collection.
//! Occupies the right part of ImportDataEditor.

class DAREFLCORE_EXPORT GraphCanvasWidget : public QWidget
{
    Q_OBJECT

public:
    GraphCanvasWidget(QWidget* parent = nullptr);

    void setItem(CanvasItem* canvas_item);

    void updateViewport();

private:
    ModelView::GraphCanvas* m_graphCanvas{nullptr};
};

} // namespace DaRefl

#endif // DAREFL_IMPORTDATAVIEW_GRAPHCANVASWIDGET_H
