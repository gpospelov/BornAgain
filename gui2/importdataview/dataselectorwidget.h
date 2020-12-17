//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/importdataview/dataselectorwidget.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_IMPORTDATAVIEW_DATASELECTORWIDGET_H
#define BORNAGAIN_GUI2_IMPORTDATAVIEW_DATASELECTORWIDGET_H

#include "darefl_export.h"
#include <QWidget>

class QTreeView;

namespace ModelView {
class PropertyTreeView;
class CollapsibleListWidget;
} // namespace ModelView

namespace gui2 {

class DataSelectionModel;
class DataViewModel;

//! Widget to select graphs and look at their properties.
//! Occupies the left part of ImportDataEditor.

class DAREFLCORE_EXPORT DataSelectorWidget : public QWidget {
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

} // namespace gui2

#endif // BORNAGAIN_GUI2_IMPORTDATAVIEW_DATASELECTORWIDGET_H
