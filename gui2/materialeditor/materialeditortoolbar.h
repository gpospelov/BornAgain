//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/materialeditor/materialeditortoolbar.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALEDITORTOOLBAR_H
#define BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALEDITORTOOLBAR_H

#include "darefl_export.h"
#include <QToolBar>

namespace gui2 {

class MaterialEditorActions;

//! Material editor toolbar.

class DAREFLCORE_EXPORT MaterialEditorToolBar : public QToolBar {
    Q_OBJECT

public:
    MaterialEditorToolBar(MaterialEditorActions* actions, QWidget* parent = nullptr);
    ~MaterialEditorToolBar() = default;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MATERIALEDITOR_MATERIALEDITORTOOLBAR_H
