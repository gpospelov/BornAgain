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
{

}

MaskGraphicsProxy::~MaskGraphicsProxy()
{
    qDebug() << "MaskGraphicsProxy::~MaskGraphicsProxy()";
    if(m_sceneAdaptor) {
        m_sceneAdaptor->setColorMapPlot(0);
    }
}

void MaskGraphicsProxy::setItem(IntensityDataItem *intensityDataItem)
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

void MaskGraphicsProxy::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsProxyWidget::mousePressEvent(event);
    event->accept();
}

void MaskGraphicsProxy::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsProxyWidget::mouseReleaseEvent(event);
}


void MaskGraphicsProxy::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsProxyWidget::mouseMoveEvent(event);
    qDebug() << "MaskGraphicsProxy::mouseMoveEvent()" << event->pos();
}
