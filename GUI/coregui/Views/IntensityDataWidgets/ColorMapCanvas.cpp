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

#include "ColorMap.h"
#include "ColorMapCanvasEvent.h"
#include "ColorMapLabel.h"
#include "IntensityDataItem.h"
#include "StatusLabel.h"
#include "ColorMapCanvas.h"
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>


ColorMapCanvas::ColorMapCanvas(QWidget *parent)
    : QWidget(parent)
//    , m_titleLabel(new StatusLabel)
    , m_colorMap(new ColorMap)
    , m_canvasEvent(new ColorMapCanvasEvent(this))
    , m_statusLabel(new ColorMapLabel(m_colorMap, this))
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

//    m_titleLabel->setAlignment(Qt::AlignBottom| Qt::AlignHCenter);
//    layout->addWidget(m_titleLabel);

    layout->addWidget(m_colorMap);
    layout->addWidget(m_statusLabel);

    setLayout(layout);

    setStatusLabelEnabled(false);
}


void ColorMapCanvas::setItem(IntensityDataItem *intensityDataItem)
{
    m_colorMap->setItem(intensityDataItem);

//    intensityDataItem->mapper()->setOnPropertyChange(
//                [this, intensityDataItem](const QString &name)
//    {
//        if(name == IntensityDataItem::P_TITLE) {
//            onTitleChanged(intensityDataItem->getItemValue(IntensityDataItem::P_TITLE).toString());
//        }
//    }, this);

//    onTitleChanged(intensityDataItem->getItemValue(IntensityDataItem::P_TITLE).toString());
//    ("Monospace", default_text_size, QFont::Normal, false)
    QFont font = m_colorMap->customPlot()->xAxis->labelFont();
    qDebug() << "FFFFF" << font;
//    m_colorMap->customPlot()->xAxis->setLabelFont();
}

ColorMap *ColorMapCanvas::colorMap()
{
    return m_colorMap;
}

QCustomPlot *ColorMapCanvas::customPlot() {
    return m_colorMap->customPlot();
}

void ColorMapCanvas::setStatusLabelEnabled(bool flag)
{
    m_statusLabel->setLabelEnabled(flag);
    m_statusLabel->setHidden(!flag);
}

//QLabel *ColorMapCanvas::statusLabel()
//{
//    return m_statusLabel;
//}

void ColorMapCanvas::onStatusString(const QString &name)
{
    m_statusLabel->setText(name);
}

//void ColorMapCanvas::onTitleChanged(const QString &title)
//{
//    if(title.isEmpty()) {
//        m_titleLabel->hide();
//    } else {
//        m_titleLabel->show();
//        m_titleLabel->setText(title);
//    }
//}


