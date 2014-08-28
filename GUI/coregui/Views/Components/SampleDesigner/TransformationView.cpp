#include "TransformationView.h"
#include "DesignerHelper.h"
#include "item_constants.h"


TransformationView::TransformationView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::TransformationType);
    setLabel("Transformation");
    setColor(DesignerHelper::getDefaultTransformationColor());
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::GeometryTransformation);
    m_roundpar = 3;
}
