// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/FontScalingEvent.h
//! @brief     Defines class FontScalingEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FONTSCALINGEVENT_H
#define FONTSCALINGEVENT_H

#include "WinDllMacros.h"
#include <QFont>
#include <QMap>
#include <QObject>

class ColorMapCanvas;
class QObject;
class QEvent;

//! Provides event filter for ScientificPlot. Its goal is to make font size adjustments
//! on resize events.

class BA_CORE_API_ FontScalingEvent : public QObject
{
    Q_OBJECT

public:
    explicit FontScalingEvent(ColorMapCanvas* canvas);

protected:
    bool eventFilter(QObject* obj, QEvent* event);

private:
    void backupFonts();
    void restoreFonts();
    void scaleFonts(double factor);
    void setTickLabelFont(const QFont& font);

    ColorMapCanvas* m_canvas;
    QMap<QString, QFont> m_fonts;
};

#endif // FONTSCALINGEVENT_H
