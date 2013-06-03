#include "InterferenceFunctionView.h"
#include "DesignerHelper.h"
#include "Units.h"

InterferenceFunctionView::InterferenceFunctionView(QGraphicsItem *parent)
    : ISampleRectView(parent)
{
    setColor(QColor(255, 236, 139));
    setRectangle( QRect(0, 0, DesignerHelper::getDefaultInterferenceFunctionWidth(), DesignerHelper::getDefaultInterferenceFunctionHeight()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::Interference);    
    m_roundpar = 3;
}


InterferenceFunction1DParaCrystalView::InterferenceFunction1DParaCrystalView(QGraphicsItem *parent)
    : InterferenceFunctionView(parent)
    , m_peak_distance(20.0*Units::nanometer)
    , m_width(7.0*Units::nanometer)
    , m_corr_length(1e3)
{
    setName("InterferenceFunction1DParaCrystal");
    setLabel("Interference \n1D paracrystal");
}

