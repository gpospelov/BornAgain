// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapLabel.h
//! @brief     Declares class ColorMapLabel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COLORMAPLABEL_H
#define COLORMAPLABEL_H

#include "StatusLabel.h"
#include <QList>

class ColorMap;
class ColorMapCanvas;
class QResizeEvent;

//! The ColorMapLabel class shows status string as reported by ColorMap in a frame.
//! Can work with more than one ColorMap. Provides automatic adjustment of font size,
//! depending on available space in parent layout. Also doesn't trigger layout resize,
//! beeing happy with place it has.

class BA_CORE_API_ ColorMapLabel : public StatusLabel
{
    Q_OBJECT
public:
    ColorMapLabel(ColorMap *colorMap, QWidget *parent = 0);

    void addColorMap(ColorMap *colorMap);
    void addColorMap(ColorMapCanvas *colorMapCanvas);

    void setLabelEnabled(bool flag);

    void reset();

public slots:
    void onColorMapStatusString(const QString &text);

//protected:
//    void resizeEvent(QResizeEvent *event);

private:
    void setColorMapLabelEnabled(ColorMap *colorMap, bool flag);
    void setConnected(ColorMap *colorMap, bool flag);

    QList<ColorMap *> m_colorMaps;
};

#endif

