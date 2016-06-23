// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapCanvas.h
//! @brief     Declares class ColorMapCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COLORMAPCANVAS_H
#define COLORMAPCANVAS_H

#include "WinDllMacros.h"
#include <QWidget>

//! The ColorMapCanvas class contains ColorMap for intensity data presentation, and controls
//! size of fonds, depending from size of widget, status string appearance, set of definig actions
//! (reset view, save plot, show context menu).

class BA_CORE_API_ ColorMapCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit ColorMapCanvas(QWidget *parent = 0);

};

#endif

