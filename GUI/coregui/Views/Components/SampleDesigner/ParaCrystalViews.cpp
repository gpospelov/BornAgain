#include "ParaCrystalViews.h"
#include "DesignerHelper.h"
#include "item_constants.h"


InterferenceFunction1DParaCrystalView::InterferenceFunction1DParaCrystalView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunction1DParaCrystalType);
    setLabel("Interference \n1D paracrystal");
    setColor(QColor(255, 236, 139));
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::Interference);
    m_roundpar = 3;
}


InterferenceFunction2DParaCrystalView::InterferenceFunction2DParaCrystalView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunction1DParaCrystalType);
    setLabel("Interference \n2D paracrystal");
    setColor(QColor(255, 236, 139));
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::Interference);
    m_roundpar = 3;
}
