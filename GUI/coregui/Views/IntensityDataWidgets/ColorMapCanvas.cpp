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

#include "ColorMapCanvas.h"
#include "ColorMap.h"
#include "ColorMapCanvasEvent.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

namespace {
const int initial_label_width = 100;
}

ColorMapCanvas::ColorMapCanvas(QWidget *parent)
    : QWidget(parent)
    , m_colorMap(new ColorMap)
    , m_canvasEvent(new ColorMapCanvasEvent(this))
    , m_statusLabel(new QLabel)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    m_statusLabel->setAlignment(Qt::AlignVCenter| Qt::AlignLeft);
    m_statusLabel->setStyleSheet("background-color:white;");
    m_statusLabel->setMargin(3);

    layout->addWidget(m_colorMap);
    layout->addWidget(m_statusLabel);

    setLayout(layout);

    setStatusLabelEnabled(true);
}


void ColorMapCanvas::setItem(IntensityDataItem *intensityDataItem)
{
    m_colorMap->setItem(intensityDataItem);
}

QLabel *ColorMapCanvas::statusLabel()
{
    return m_statusLabel;
}

void ColorMapCanvas::onStatusString(const QString &name)
{
    m_statusLabel->setText(name);
}


//! Enables/disables status label with bins/amplitudes at the bottom of widget.

void ColorMapCanvas::setStatusLabelEnabled(bool flag)
{
    m_colorMap->setMouseTrackingEnabled(true);
    setStatusLabelConnected(flag);
    m_statusLabel->setVisible(flag);

}

//! Connects/disconnects signals for status label.

void ColorMapCanvas::setStatusLabelConnected(bool flag)
{
    if(flag) {
        connect(m_colorMap, SIGNAL(statusString(const QString&)),
                this, SLOT(onStatusString(const QString&)), Qt::UniqueConnection);
    } else {
        disconnect(m_colorMap, SIGNAL(statusString(const QString&)),
                this, SLOT(onStatusString(const QString&)));
    }
}
