// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapEvent.h
//! @brief     Declares class ColorMapEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COLORMAPEVENT_H
#define COLORMAPEVENT_H

#include "WinDllMacros.h"
#include "ColorMapBin.h"
#include <QObject>

class ColorMap;
class QMouseEvent;
class QCustomPlot;

//! The ColorMapEvent class helps ColorMap to handle mouse events. Particularly,
//! it constructs a valid status string. Can be extended to play a role of event filter.

class BA_CORE_API_ ColorMapEvent : public QObject {
    Q_OBJECT

public:
    explicit ColorMapEvent(ColorMap *colorMap);

    void setMouseTrackingEnabled(bool enable);

public slots:
    void onCustomMouseMove(QMouseEvent *event);

private:
    ColorMap *colorMap();
    const ColorMap *colorMap() const;
    QCustomPlot *customPlot();
    ColorMapBin currentColorMapBin(QMouseEvent *event) const;

    ColorMap *m_colorMap;
    ColorMapBin m_prevPos;
};

#endif // COLORMAPEVENT_H
