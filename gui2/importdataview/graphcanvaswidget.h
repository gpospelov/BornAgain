//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/importdataview/graphcanvaswidget.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_IMPORTDATAVIEW_GRAPHCANVASWIDGET_H
#define BORNAGAIN_GUI2_IMPORTDATAVIEW_GRAPHCANVASWIDGET_H

#include "darefl_export.h"
#include <QWidget>

namespace ModelView {
class GraphCanvas;
}

namespace gui2 {

class CanvasItem;

//! Widget to show canvas with graph collection.
//! Occupies the right part of ImportDataEditor.

class DAREFLCORE_EXPORT GraphCanvasWidget : public QWidget {
    Q_OBJECT

public:
    GraphCanvasWidget(QWidget* parent = nullptr);

    void setItem(CanvasItem* canvas_item);

    void updateViewport();

private:
    ModelView::GraphCanvas* m_graphCanvas{nullptr};
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_IMPORTDATAVIEW_GRAPHCANVASWIDGET_H
