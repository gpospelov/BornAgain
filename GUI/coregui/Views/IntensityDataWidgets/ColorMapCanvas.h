// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapCanvas.h
//! @brief     Defines class ColorMapCanvas
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

#include "SessionItemWidget.h"

class ColorMap;
class QCustomPlot;
class ColorMapCanvasEvent;
class IntensityDataItem;
class ColorMapLabel;

//! The ColorMapCanvas class contains ColorMap for intensity data presentation, and provide
//! control of font size, status string appearance, defines common actions
//! (reset view, save plot, show context menu).

class BA_CORE_API_ ColorMapCanvas : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit ColorMapCanvas(QWidget* parent = 0);

    void setItem(SessionItem* intensityDataItem);

    ColorMap* colorMap();
    QCustomPlot* customPlot();

    void setStatusLabelEnabled(bool flag);

public slots:
    void onStatusString(const QString& name);

private:
    ColorMap* m_colorMap;
    ColorMapCanvasEvent* m_canvasEvent;
    ColorMapLabel* m_statusLabel;
};

#endif // COLORMAPCANVAS_H

