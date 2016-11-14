// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapCanvasEvent.h
//! @brief     Defines class ColorMapCanvasEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COLORMAPCANVASEVENT_H
#define COLORMAPCANVASEVENT_H

#include "WinDllMacros.h"
#include <QFont>
#include <QMap>
#include <QObject>

class ColorMapCanvas;
class QObject;
class QEvent;

//! The ColorMapCanvasEvent provide event filter for ColorMapCanvas. Its goal is to provide
//! font size adjustment on resize events.

class BA_CORE_API_ ColorMapCanvasEvent : public QObject
{
    Q_OBJECT

public:
    explicit ColorMapCanvasEvent(ColorMapCanvas *canvas);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void backupFonts();
    void restoreFonts();
    void scaleFonts(double factor);
    void setTickLabelFont(const QFont &font);

    ColorMapCanvas *m_canvas;
    QMap<QString, QFont> m_fonts;
};

#endif // COLORMAPCANVASEVENT_H
