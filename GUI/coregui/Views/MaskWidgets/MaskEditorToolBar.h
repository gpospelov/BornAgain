// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorToolBar.h
//! @brief     Defines class MaskEditorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORTOOLBAR_H
#define MASKEDITORTOOLBAR_H

#include "WinDllMacros.h"
#include <QToolBar>


//! Main class to draw masks on top of intensity data map

class BA_CORE_API_ MaskEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    MaskEditorToolBar(QWidget *parent = 0);

private:
    void add_selection_group();
};


#endif
