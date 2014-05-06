#include "ParaCrystalViews.h"
#include "DesignerHelper.h"

InterferenceFunction1DParaCrystalView::InterferenceFunction1DParaCrystalView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName("InterferenceFunction1DParaCrystal");
    setLabel("Interference \n1D paracrystal");
    setColor(QColor(255, 236, 139));
    setRectangle( QRect(0, 0, DesignerHelper::getDefaultInterferenceFunctionWidth(), DesignerHelper::getDefaultInterferenceFunctionHeight()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::Interference);
    m_roundpar = 3;
}
