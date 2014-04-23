#include "FormFactorView.h"
#include "DesignerHelper.h"
#include "MaterialEditor.h"


FormFactorView::FormFactorView(QGraphicsItem *parent)
    : ConnectableView(parent)
    , m_weight(1.0)
{
    setName("FormFactorView");
    setColor(DesignerHelper::getDefaultFormFactorColor());
    setRectangle( QRect(0, 0, DesignerHelper::getDefaultFormFactorWidth(), DesignerHelper::getDefaultFormFactorHeight()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::FormFactor);
    addPort("transformation", NodeEditorPort::Input, NodeEditorPort::GeometryTransformation);
    m_roundpar = 5;
    setMaterialProperty(MaterialEditor::getDefaultMaterialProperty());
}
