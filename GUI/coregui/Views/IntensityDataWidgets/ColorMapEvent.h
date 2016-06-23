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
#include <QObject>

class ColorMap;
class QMouseEvent;

//! The ColorMapEvent class helps ColorMap to handle mouse events by playing a role of
//! event filter. Particularly, it constructs a valid status string.

class BA_CORE_API_ ColorMapEvent : public QObject {
    Q_OBJECT

public:
    explicit ColorMapEvent(ColorMap *colorMap);

    void setMouseTracking(bool enable);

public slots:
    void onCustomMouseMove(QMouseEvent *event);


protected:
//  bool eventFilter( QObject *dist, QEvent *event );

private:
    ColorMap *m_colorMap;
};

#endif
