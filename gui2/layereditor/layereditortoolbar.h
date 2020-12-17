//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/layereditor/layereditortoolbar.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_LAYEREDITOR_LAYEREDITORTOOLBAR_H
#define BORNAGAIN_GUI2_LAYEREDITOR_LAYEREDITORTOOLBAR_H

#include "darefl_export.h"
#include <QToolBar>
#include <QWidget>
#include <map>
#include <string>

namespace gui2 {

class LayerEditorActions;

//! Layer editor toolbar.

class DAREFLCORE_EXPORT LayerEditorToolBar : public QToolBar {
    Q_OBJECT

public:
    LayerEditorToolBar(LayerEditorActions* actions, QWidget* parent = nullptr);
    ~LayerEditorToolBar() = default;

    void updateToolButtonStates(bool first_present, bool last_present);

private:
    QMenu* create_layer_menu(LayerEditorActions* editor_actions);
    std::map<std::string, QWidget*> m_toolbarWidgets;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_LAYEREDITOR_LAYEREDITORTOOLBAR_H
