// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskGraphicsProxy.h
//! @brief     Defines class MaskGraphicsProxy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MASKGRAPHICSPROXY_H
#define MASKGRAPHICSPROXY_H

#include "MaskEditorHelper.h"
#include <QGraphicsProxyWidget>

class SessionItem;
class ISceneAdaptor;
class ColorMapSceneAdaptor;
class ColorMap;
class IntensityDataItem;

//! Graphics proxy to place QWidget inside QGraphicsScene, used by MaskEditorCanvas.

class MaskGraphicsProxy : public QGraphicsProxyWidget
{
    Q_OBJECT

public:
    MaskGraphicsProxy();
    virtual ~MaskGraphicsProxy();

    int type() const { return MaskEditorHelper::MASKGRAPHICSPROXY; }

    void setIntensityItem(IntensityDataItem *item);
    void setSceneAdaptor(ISceneAdaptor *sceneAdaptor);
    void setInZoomMode(bool value);

    ColorMap *colorMap();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);

private:
    ColorMap *m_colorMap;
    ColorMapSceneAdaptor *m_sceneAdaptor;
    bool m_send_signals_to_colormap;
};

#endif // MASKGRAPHICSPROXY_H
