#include "ParaCrystalViews.h"
#include "DesignerHelper.h"


InterferenceFunction1DParaCrystalView::InterferenceFunction1DParaCrystalView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName("InterferenceFunction1DParaCrystal");
    setLabel("Interference \n1D paracrystal");
    setColor(QColor(255, 236, 139));
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::Interference);
    m_roundpar = 3;
}


InterferenceFunction2DParaCrystalView::InterferenceFunction2DParaCrystalView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName("InterferenceFunction2DParaCrystal");
    setLabel("Interference \n2D paracrystal");
    setColor(QColor(255, 236, 139));
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::Interference);
    m_roundpar = 3;
}
