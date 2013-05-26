#include "FormFactorView.h"
#include "DesignerHelper.h"


FormFactorView::FormFactorView(QGraphicsItem *parent)
    : ISampleRectView(parent)
    , m_weight(1.0)
{
    setName("FormFactorView");
    setColor(DesignerHelper::getDefaultFormFactorColor());
    setRectangle( QRect(0, 0, DesignerHelper::getDefaultFormFactorWidth(), DesignerHelper::getDefaultFormFactorHeight()) );
    addPort("out", QNEPort::Output, QNEPort::FormFactor);
    addPort("transformation", QNEPort::Input, QNEPort::GeometryTransformation);
    m_roundpar = 5;
}
