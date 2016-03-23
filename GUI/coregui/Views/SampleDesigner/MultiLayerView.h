// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/MultiLayerView.h
//! @brief     Defines class MultiLayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MULTILAYERVIEW_H
#define MULTILAYERVIEW_H


#include "ILayerView.h"

class DesignerMimeData;
class QGraphicsSceneDragDropEvent;

//! Class representing view of MultiLayer.
//! Handles drop of other MultiLayer and Layer views on top of it
class BA_CORE_API_ MultiLayerView : public ILayerView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::MULTILAYER };

    MultiLayerView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addView(IView *childView, int row = 0);

    virtual void addNewLayer(ILayerView *layer, int row);
    virtual void removeLayer(ILayerView *layer);

    bool isInDropArea(QPointF pos);
    int getDropArea(QPointF pos);
    QRectF getDropAreaRectangle(int row);
    QLineF getInterfaceLine(int row);

public slots:
    void updateGeometry();
    void updateHeight();
    void updateWidth();
    void onLayerAboutToBeDeleted();

protected:
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QList<ILayerView *> m_layers;
    QList<QRectF> m_drop_areas;
    QList<QLineF> m_interfaces;
};


#endif // MULTILAYERVIEW_H
