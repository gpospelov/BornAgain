// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/Plot1DCanvas.cpp
//! @brief     Implements class Plot1DCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Plot1DCanvas.h"
#include "FontScalingEvent.h"
#include "PlotStatusLabel.h"
#include "SpecularPlot.h"
#include "SpecularDataItem.h"
#include <QVBoxLayout>

Plot1DCanvas::Plot1DCanvas(QWidget *parent)
    : SessionItemWidget(parent)
    , m_plot(new SpecularPlot)
    , m_canvasEvent(new FontScalingEvent(m_plot, this))
    , m_statusLabel(new PlotStatusLabel(m_plot, this))
{
    this->installEventFilter(m_canvasEvent);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_plot);
    layout->addWidget(m_statusLabel);

    setLayout(layout);

    setStatusLabelEnabled(false);
}

void Plot1DCanvas::setItem(SessionItem* specularDataItem)
{
    SessionItemWidget::setItem(specularDataItem);
    m_plot->setItem(dynamic_cast<SpecularDataItem*>(specularDataItem));
}

SpecularPlot* Plot1DCanvas::specularPlot()
{
    return m_plot;
}

QCustomPlot* Plot1DCanvas::customPlot()
{
    return m_plot->customPlot();
}

void Plot1DCanvas::setStatusLabelEnabled(bool flag)
{
    m_statusLabel->setLabelEnabled(flag);
    m_statusLabel->setHidden(!flag);
}

void Plot1DCanvas::onStatusString(const QString& name)
{
    m_statusLabel->setText(name);
}
