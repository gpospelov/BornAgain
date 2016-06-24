// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapLabel.cpp
//! @brief     Implements class ColorMapLabel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ColorMapLabel.h"
#include "ColorMap.h"

ColorMapLabel::ColorMapLabel(ColorMap *colorMap, QWidget *parent)
    : StatusLabel(parent)
{
    addColorMap(colorMap);
}

void ColorMapLabel::addColorMap(ColorMap *colorMap)
{
    if(m_colorMaps.contains(colorMap))
        return;

    m_colorMaps.push_back(colorMap);

    setColorMapLabelEnabled(colorMap, true);
}

//! Enables/disables label. If disabled, all colorMaps are disconnected and label is hiding.

void ColorMapLabel::setLabelEnabled(bool flag)
{
    foreach(ColorMap *colorMap, m_colorMaps)
        setColorMapLabelEnabled(colorMap, flag);

    setEnabled(flag);
}

void ColorMapLabel::onColorMapStatusString(const QString &text)
{
    setText(text);
}

//! Enables/disables showing of label for given color map.

void ColorMapLabel::setColorMapLabelEnabled(ColorMap *colorMap, bool flag)
{
    colorMap->setMouseTrackingEnabled(flag);
    setConnected(colorMap, flag);
}

//! Connects with colorMap's status string signal.

void ColorMapLabel::setConnected(ColorMap *colorMap, bool flag)
{
    if(flag) {
        connect(colorMap, SIGNAL(statusString(const QString&)),
                this, SLOT(onColorMapStatusString(const QString&)), Qt::UniqueConnection);
    } else {
        disconnect(colorMap, SIGNAL(statusString(const QString&)),
                this, SLOT(onColorMapStatusString(const QString&)));
    }
}
