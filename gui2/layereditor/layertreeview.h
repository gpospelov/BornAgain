//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/layereditor/layertreeview.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_LAYEREDITOR_LAYERTREEVIEW_H
#define BORNAGAIN_GUI2_LAYEREDITOR_LAYERTREEVIEW_H

#include "darefl_export.h"
#include <QTreeView>

namespace gui2 {

//! Extension of QTreeView for layer editing.

class DAREFLCORE_EXPORT LayerTreeView : public QTreeView {
public:
    using QTreeView::QTreeView;

    explicit LayerTreeView(QWidget* parent = nullptr);
    ~LayerTreeView() override;

    void setModel(QAbstractItemModel* model) override;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_LAYEREDITOR_LAYERTREEVIEW_H
