// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskGraphicsProxy.cpp
//! @brief     Implements class MaskGraphicsProxy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskGraphicsProxy.h"
#include <QGraphicsSceneMouseEvent>
#include "ColorMapPlot.h"
#include "ColorMapSceneAdaptor.h"
#include "IntensityDataItem.h"
#include <QDebug>

MaskGraphicsProxy::MaskGraphicsProxy()
    : m_colorMap(new ColorMapPlot)
    , m_sceneAdaptor(0)
    , m_send_signals_to_colormap(false)
{
    resize(1200, 1000);
    setAcceptedMouseButtons(Qt::NoButton);
}

MaskGraphicsProxy::~MaskGraphicsProxy()
{
    // no need to delete m_colorMap, base QGraphicsProxyWidget will take care about it
    if(m_sceneAdaptor) {
        m_sceneAdaptor->setColorMapPlot(0);
    }
}

void MaskGraphicsProxy::setIntensityItem(IntensityDataItem *intensityDataItem)
{
    m_colorMap->setItem(intensityDataItem);
    if(widget() != m_colorMap) setWidget(m_colorMap);
}

void MaskGraphicsProxy::setSceneAdaptor(ISceneAdaptor *sceneAdaptor)
{
    m_sceneAdaptor = dynamic_cast<ColorMapSceneAdaptor *>(sceneAdaptor);
    Q_ASSERT(m_sceneAdaptor);
    m_sceneAdaptor->setColorMapPlot(m_colorMap);
}

//! Sets widget to zoom mode, when signals (zoom wheel, mouse clicks) are send down to
//! ColorMap plot. In non-zoom mode, widget doesn't react on clicks.
void MaskGraphicsProxy::setInZoomMode(bool value)
{
    m_send_signals_to_colormap = value;
    if(value) {
        setAcceptedMouseButtons(Qt::LeftButton);
    } else {
        setAcceptedMouseButtons(Qt::NoButton);
    }
}

void MaskGraphicsProxy::resetView()
{
    Q_ASSERT(m_colorMap);
    m_colorMap->resetView();
}

void MaskGraphicsProxy::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_send_signals_to_colormap) return;
    QGraphicsProxyWidget::mousePressEvent(event);
    event->accept();
}

void MaskGraphicsProxy::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_send_signals_to_colormap) return;
    QGraphicsProxyWidget::mouseReleaseEvent(event);
}

void MaskGraphicsProxy::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(!m_send_signals_to_colormap) return;
    QGraphicsProxyWidget::wheelEvent(event);
}

void MaskGraphicsProxy::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MaskGraphicsProxy::mouseMoveEvent(QGraphicsSceneMouseEvent *event)";
    if(!m_send_signals_to_colormap) return;
        qDebug() << "aaa";
    QGraphicsProxyWidget::mouseMoveEvent(event);
}
